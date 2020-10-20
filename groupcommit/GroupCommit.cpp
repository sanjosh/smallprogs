#include "GroupCommit.h"
#include "SVConfig.h"

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdio.h> // sprintf
#include <sys/stat.h>
#include <stdint.h>

// normalWakeup + oldGenWakeup + timeoutSameGen + numNormalSyncs = sleepingThreads = total number of ops
// totalSyncs = numNormalSyncs + syncsAfterTimeout < total number of ops
// spuriousWakeup should be 0

//#define SYNCAFTER_LIST

// ============================
GroupCommit::Statistics::Statistics()
{
    Statistics::init();
}

void GroupCommit::Statistics::init()
{
    normalWakeup = 0;
    spuriousWakeup = 0;
    oldGenWakeup = 0;
    timeoutSameGen = 0;
    sleepingThreads  = 0;
    numNormalSyncs = 0;
    syncAfterTimeout = 0;
    totalSyncs  = 0;
    syncAfterList.clear();
}

ostream& operator << (ostream& ostr, GroupCommit::Statistics& me)
{
    ostr << ":normalWakeup=" << me.normalWakeup
                << ":oldGenWakeup=" << me.oldGenWakeup
                << ":timeoutSameGen=" << me.timeoutSameGen
                << ":numNormalSyncs=" << me.numNormalSyncs
                << ":sleepingThreads=" << me.sleepingThreads
                << ":syncAfterTimeout=" << me.syncAfterTimeout 
                << ":totalSyncs=" << me.totalSyncs
                << ":spuriousWakeup=" << me.spuriousWakeup << endl;
    return ostr;

}
// ============================

void GroupCommit::print(ostream& ostr, int isVerbose) 
{
    ostr << "GroupCommit";

    ostr << ":isSingleThread=" << isSingleThread 
	<< ":adaptive=" << boolalpha << (isAdaptive==1) << noboolalpha
        << ":fixed timeout=" << timeOutValue;

    ostr << stats << ":syncAfter=" << syncAfter 
            << endl;

#ifdef SYNCAFTER_LIST
	if (isVerbose)
	{
    	std::list<uint32_t>::iterator pos;
    	ostr << "printing syncAfter values" << endl;
    	int i = 0;

    	int prev = 0;
    	unsigned prevCount = 0;
    	for (pos = stats.syncAfterList.begin(); pos != stats.syncAfterList.end(); ++pos)
    	{
    		if (*pos != prev) 
    		{
        		ostr << prev << "(" << prevCount << " times):";
        		i++;
        		if (i == 40) {ostr << endl; i = 0;}
        		prev = *pos;
            	prevCount = 1;
    		}
    		else
    		{
        		prevCount ++;
    		}
    	}
    	ostr << prev << "(" << prevCount << " times):" << endl;
	}
#endif

    // we accumulate in 'prev' and print all counters of same value
}


void GroupCommit::clearStats() 
{
    stats.init();
}

void GroupCommit::setDynamicTimeout()
{
    isAdaptive = true;
}

void GroupCommit::setFixedTimeout(unsigned long newTimeout) 
{
    timeOutValue = newTimeout;
    isAdaptive = false;
}

void GroupCommit::setThreads(bool isThreaded) 
{
     isSingleThread = (!isThreaded);
}

void GroupCommit::init(RecoveryLog<WriteCacheLogRecord> *in_recLog, RawDeviceBlockStore *in_writeCacheData, 
        uint32_t in_syncAfter, unsigned long defaultNanoSecs )
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condvar, NULL);
    writeCacheRecoveryLog = in_recLog; 
    writeCacheData = in_writeCacheData;
    counter = 0;
    syncAfter = in_syncAfter;
    //timeDiff.setZero();
    defaultNano = defaultNanoSecs;
    average.a = defaultNanoSecs;
    averageCount = 1;
    generation = 0;

    stats.normalWakeup = 0;
    stats.spuriousWakeup = 0;
    stats.oldGenWakeup = 0;
    stats.syncAfterTimeout = 0;
    stats.timeoutSameGen = 0;
    stats.sleepingThreads  = 0;
    stats.numNormalSyncs = 0;
    stats.totalSyncs  = 0;

    fsid = 0;
    isSingleThread = true;
    isAdaptive = false;
    timeOutValue = TIMEOUT_VALUE;
}

GroupCommit::~GroupCommit()
{

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condvar);

}

// in order to determine if FUSE is sending us more than one requests,
// we read the file called "/sys/fs/fuse/connections/*/waiting"

void getNumOfRequestsInFuse(dev_t& fsid, bool& isSingleThread)
{
    if (fsid == 0)
    {
        struct stat statbuf;
        int ret = ::stat(SVConfig::Instance().nfsShareName.c_str(),  &statbuf);
        if (ret < 0)
        {
             LOG(ERROR) << "stat failed with errno=" << errno << endl;
        }
        fsid = statbuf.st_dev;
    }

    char name[PATH_MAX];
    sprintf(name, "/sys/fs/fuse/connections/%ld/waiting", fsid);
    int fd = open(name, O_RDONLY);
    if (fd < 0)
    {
        LOG(ERROR) << "open failed with errno=" << errno << endl;
        fd = INVALID_FD;
        return;
    }

    char buf[sizeof(uint64_t)];
    ssize_t readSz = read(fd, buf, sizeof(buf));
    if (readSz > 0)
    {
        buf[readSz] = '\0';
        long int num = strtol(buf, NULL, 10);
        if ((num != LONG_MIN) || (num != LONG_MAX))
        {
            isSingleThread = (num == 1);
        }
        else
        {
            LOG(ERROR) << "strtol error:" << errno << ":readSz=" << readSz << ":buf=" << buf << endl;
        }
    }
    else
    {
        LOG(ERROR) << "read failed fd=" << fd << " errno=" << errno << " size=" << readSz << endl;
    }

    close(fd);
}

Status GroupCommit::realSync(off_t logOffset)
{
    writeCacheRecoveryLog->commit(logOffset);
    
    writeCacheData->_bitmap->commit();

    // generation is increased after every sync

    svout<< "sync at logOffset=" << logOffset << ":number waiting thr=" << counter << ":gen=" << generation << endl;

    generation ++;
    stats.sleepingThreads += counter;
    stats.totalSyncs ++;

    if (counter > 20)
    {
        syncAfter = counter;
    }

#ifdef SYNCAFTER_LIST
    stats.syncAfterList.push_back(counter);
#endif
    counter = 0;
    return Status_OK;
}

Status GroupCommit::sync(off_t logOffset)
{
    pthread_mutex_lock(&mutex);

    // getNumOfRequestsInFuse(fsid, isSingleThread);

    counter ++;
    uint64_t localGen = generation;

    if (counter == syncAfter)
    {
        realSync(logOffset);
        stats.numNormalSyncs ++;
        pthread_cond_broadcast(&condvar);
        pthread_mutex_unlock(&mutex);

    	if (isAdaptive) 
        {
            getNumOfRequestsInFuse(fsid, isSingleThread);
        }
    }
    else
    {
        // skip the wait if its single threaded mode
        if (!isSingleThread)
        {
            MyTimeSpec* timeptr = timeDiff.getTimer(defaultNano);

            if (isAdaptive)
            {

                average.a = ((average.a * averageCount) + timeptr->a)/(averageCount + 1);

                averageCount ++;
                *timeptr = average;
    
                if (averageCount > 10000)
                {
                    // decrease the weight of the average
                    //svout << "reset nsecs=" << average.a << endl;
                    averageCount = 1;
                }    
            }
            else
            {
                *timeptr = timeOutValue;
            }

            MyTimeSpec curTime;
            curTime.getCurrentTime();

            // add abstime to timeptr
            curTime += (*timeptr);
            timespec abstime;
            curTime.getTimeSpec(&abstime);

            int err = pthread_cond_timedwait(&condvar, &mutex, &abstime);

            if (err == 0)
            {
                // if we were awakened, someone must have flushed
                svout << "thread woken up by flusher. gen=" << generation
                    << ":localgen=" << localGen
                    << ":counter=" << counter;
                if (localGen > generation)
                {        
                    // not possible
                    LOG(ERROR) << "sv_assert1: localGen=" << localGen
                        << ":gen=" << generation << endl;
                    pthread_mutex_unlock(&mutex);
		            askForGDBConnect();
                }
                // spurious wakeups possible
                else if (localGen == generation)
                {
                    stats.spuriousWakeup ++;

                    if (counter) 
                    {
                        realSync(logOffset);
                    }
                }
                else
                {
                    stats.normalWakeup ++;
                }
            }
            else if (err == ETIMEDOUT)
            {
                svout << "timedout after sleep nsec=" << timeptr->a << ":gen=" << generation << ":localgen=" << localGen << 
                            ":counter=" << counter << endl;
            
                // if we are in same generation 

                if (localGen == generation)
                {
                    // if no one has flushed, do it
                    stats.timeoutSameGen ++;
        
                    // if no one else around while we were sleeping, 
                    // decrease time to sleep
                    // and do not flush
                    //if (counter == 1)
                    //{
                        //timeDiff.decreaseTimeToSleep(timeptr);
                        //counter = 0;
                    //}
                    //else
                    {
                        timeDiff.adjustTimeToSleep(timeptr);
                        stats.syncAfterTimeout ++;
                        realSync(logOffset);
                    }
            
                }
                else if (localGen > generation)
                {
                    // not possible
                    LOG(ERROR) << "sv_assert2: localGen=" << localGen
                        << ":gen=" << generation << endl;
                    pthread_mutex_unlock(&mutex);
        		    askForGDBConnect();
                }
                // if we are old generation do nothing
                else if (localGen < generation)
                {
                    stats.oldGenWakeup ++;
                    svout << "old thread woke up. gen=" << generation << ":localgen=" << localGen << ":counter=" << counter << endl;
                }
            }
            else
            {
                LOG(ERROR) << "sv_assert3: err=" << err << ":errno=" << errno << endl;
                pthread_mutex_unlock(&mutex);
		        askForGDBConnect();
            }
        }

        pthread_mutex_unlock(&mutex);
    }

    return Status_OK;
};
