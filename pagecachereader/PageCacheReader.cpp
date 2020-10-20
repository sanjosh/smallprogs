#include <unistd.h> // mincore
#include <sys/mman.h> // mincore
#include <fcntl.h> // open
#include <sys/stat.h> // fchmod, fstat

#include "Common.h"
#include "SVConfig.h"
#include "PageCacheReader.h"
#include "VDisk.h"
#include "SignalHandler.h"

#define MAX_BATCH_READS 100                 // number of reads after which the file permission is toggled

size_t SeqStrategy::defaultMapSize = 1048576;  

void SeqStrategy::preHandler(off_t desiredOff)
{
    // if nothing mapped or desired offset beyond current map
    if ((reader.mapAddr == MAP_FAILED) || (desiredOff >= reader.curMapOffset + reader.curMapSize))
    {
        // unmap any previously mapped pages
        if (reader.mapAddr != MAP_FAILED)
        {
            int munmapRet = munmap(reader.mapAddr, reader.curMapSize);
            if (munmapRet == 0)
            {
                LOG(INFO) << "new off=" << desiredOff << " unmapping " << reader.curMapOffset << ":" << reader.curMapSize << endl;
            }
            else
            {
                reader.disabled = 1;
                LOG(ERROR) << "failed to unmap addr=" << (void*)reader.mapAddr << ":size=" << reader.curMapSize << ":errno=" << errno << endl;
            }
            reader.mapAddr = MAP_FAILED;
        }

        reader.curMapOffset = desiredOff;
        reader.curMapSize = sequentialMapSize;
    }
}

void SeqStrategy::failureHandler()
{
    // use progressively smaller sizes until mmap succeeds
    do
    {
        if (reader.curMapSize > reader.pageSize)
        {
            reader.curMapSize /= 2;

            if (reader.curMapSize < reader.pageSize) 
            {
                reader.curMapSize = reader.pageSize;
                break;
            }
        }

        reader.mapAddr = mmap((void*) 0, reader.curMapSize, PROT_NONE, MAP_SHARED, reader.fd, reader.curMapOffset);

        // if mmap succeeded or we reached pagesize, break
        if ((reader.mapAddr != MAP_FAILED) ||   
            (reader.curMapSize == reader.pageSize))
        {
            break;
        }
    } while (1);

    // if mmap succeeded, record the mapsize acceptable to system
    if (reader.mapAddr != MAP_FAILED)
    {
        defaultMapSize = reader.curMapSize;
    }
}

void SeqStrategy::postHandler()
{
    // do not unmap - the next call to preHandler should unmap
    // the PageCacheReader dtor will unmap whatever remains
}


// =====================

void RandomStrategy::preHandler(off_t desiredOff)
{
    reader.mapAddr = MAP_FAILED;
    reader.curMapOffset = desiredOff;
    reader.curMapSize = reader.pageSize;
}

void RandomStrategy::failureHandler()
{
}

void RandomStrategy::postHandler()
{
    svout << "unmapping off=" << reader.curMapOffset << ":size=" << reader.curMapSize << endl;
    int err = munmap(reader.mapAddr, reader.curMapSize);

    if (err != 0)
    {
        reader.disabled = 1;
        LOG(ERROR) << "munmap failed with errno=" << errno << ":" << strerror(errno) << endl;
    }
    reader.mapAddr = MAP_FAILED;
}

// =====================


int PermissionStrategy::open(const string& in_name, size_t& fileSize)
{
    name = in_name;
    lower_fd = ::open(name.c_str(), O_RDONLY);

    if (lower_fd < 0)   
    {
        LOG(ERROR) << "Failed to open lower fd=" << lower_fd
            << " errno=" << errno << endl;
        return -errno;
    }

    // retrieve the current filesize
    struct stat statBuf;
    if (fstat(lower_fd, &statBuf) != 0)
    {
        LOG(ERROR) << "Failed to stat lower fd=" << lower_fd
            << " errno=" << errno << endl;
        close();
        return -errno;
    }
    fileSize = statBuf.st_size;

    return 0;
/*
    timerfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timerfd == -1)
    {
        return -errno;
    }
    if (timerfd_settime(timerfd, 0, &newvalue, NULL) == -1)
    {
        return -errno;
    }
*/
}

void PermissionStrategy::preHandler()
{
    return; // currently disabled
/*
    if ((numReads == 0) && (lower_fd != INVALID_FD) && (writesEnabled))
    {
        // disable writes

        int ret = fchmod(lower_fd, S_IRUSR|S_IRGRP|S_IROTH);

        if (ret == 0)
        {
            writesEnabled = false;
            LOG(INFO) << "Disabling writes for " << name << endl;
        }
        // TODO handle race condition for already open files
    }
*/
}


void PermissionStrategy::postHandler()
{
    return; // currently disabled

/*
    numReads ++;
    // turn on write perm after every MAX_BATCH_READS reads
    if (numReads == MAX_BATCH_READS)
    {
        enableWrites();
        // and let some NFS writes proceed
        usleep(100);
    }
*/
}

void PermissionStrategy::enableWrites()
{
    return; // currently disabled
/*
    if ((!writesEnabled) && (lower_fd != INVALID_FD))
    {
        fchmod(lower_fd, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
        numReads = 0;
        writesEnabled = true;
        LOG(INFO) << "Enabling writes for " << name << endl;
    }
*/
}

void PermissionStrategy::close()
{
    if (lower_fd >=0) 
    {
        // reset permissions on the file
        //fchmod(lower_fd, S_IWUSR|S_IRUSR|S_IRGRP|S_IROTH);
        ::close(lower_fd);
        lower_fd = INVALID_FD; 
    }
}

PermissionStrategy::~PermissionStrategy()
{
    close();
}


// =====================

PageCacheReader::PageCacheReader(VDisk& in_vDisk, const size_t in_pageSize) : vDisk(in_vDisk), seqStrategy(*this), randomStrategy(*this), pageSize(in_pageSize)
{
    fd = INVALID_FD;
    disabled = 1;

    mapAddr = MAP_FAILED;
    curMapOffset = 0;
    curMapSize = 0;
}

PageCacheReader::~PageCacheReader()
{
    // unmap whatever remains
    if (mapAddr != MAP_FAILED) 
    {
        int munmapRet = munmap(mapAddr, curMapSize);
        if (munmapRet != 0)
        {
            LOG(ERROR) << "failed to unmap addr=" << (void*)mapAddr << ":size=" << curMapSize << ":errno=" << errno << endl;
        }
    }

    if (fd >= 0) 
    {
        ::close(fd);
        fd = INVALID_FD;
    }
}

int PageCacheReader::open(const string& nfsShareName, const string& nfsShareLowerFS, const string& in_vDiskName, bool in_sequentialAccess)
{
    vDiskName = in_vDiskName; 
    string name = nfsShareName + vDiskName;
    string lowerName = nfsShareLowerFS + vDiskName;
    
    // name here is /svfuse/win6-flat.vmdk (e.g.)
    fd = ::open(name.c_str(),  O_RDONLY);
    int fd_errno = (fd < 0) ? -errno : 0; // save it bfor its lost
    int lowerfd_errno = perm.open(lowerName, fileSize);

    if ((fd_errno < 0) || (lowerfd_errno < 0))
    {
        // you get ENOENT error in system shutdown when /svfuse is being unmounted
        if ((fd_errno != ENOENT) && (lowerfd_errno != ENOENT))
        {
            LOG(ERROR) << "unable to open pagecache reader for file=" << name 
            << ":err=" << fd_errno 
            << ":err=" << lowerfd_errno << endl;
        }

        disabled = 1;
        perm.close();
        close(fd);
        fd = INVALID_FD;
        return -1;
    }
    else
    {
        sv_assert(fd >= 0);
        //sv_assert(perm.lower_fd >= 0);
    }

    // if access is sequential, we can optimize on mmap calls. map more at a time if access is sequential
    if (in_sequentialAccess)
    {
        mappingStrategy = &seqStrategy;
    }
    else
    {
        mappingStrategy = &randomStrategy;
    }

    sigbusRecvd = false;
    SignalHandler::setSigBusKey(&sigbusRecvd);

    curMapSize = 0;
    curMapOffset = 0;
    mapAddr = MAP_FAILED;

    disabled = 0;
    return 0;
} 

int PageCacheReader::read(vdiskoffset_t cacheBlockId, char* data)
{
    // for debugging - temporarily change the thread name 
    // so we can see in the /proc/<pid>/task/<lwpid>/status
    // which offset the thread was accessing when it hangs
#ifdef SVDEBUG
    char buf[100];
    sprintf(buf, "pcr_%d_%u", vDisk.Id(), cacheBlockId);
    Thread::getCurrent()->setName(buf);
#endif

    if (disabled)
    {
        if (disabled == 1) 
        {
            // enable writes again
            perm.enableWrites();
            LOG(INFO) << "pagecache reader is disabled for " << vDiskName << endl;
            disabled = 2; // no need to print error msg again
        }
        return -1;
    }

    int retcode = -1;
    off_t desiredOff = cacheBlockId * pageSize;

    if (desiredOff + pageSize > fileSize)
    {
        LOG(WARNING) << "access disallowed. out of bounds off=" << desiredOff << ":size=" << fileSize << endl;
        return -1;
    }
    
    if (vDisk.flushData.curWriteOffsetValid && (cacheBlockId == vDisk.flushData.curWriteOffset))
    {
        LOG(ERROR) << "write in progress off=" << desiredOff << ":size=" << fileSize << endl;
        return -1;
    }

    vDisk.flushData.faultOffset = cacheBlockId;
    vDisk.flushData.faultState = VDisk::Flush::FAULT_SET;
    sigbusRecvd = false;
    void* copyAddr = MAP_FAILED;

    do 
    {
        perm.preHandler();

        mappingStrategy->preHandler(desiredOff);
        sv_assert(curMapSize);

    // mmap flags explained :
    // use MAP_LOCKED because we must lock the page to prevent it from being paged out between the call to mincore and subsequent memcpy below.
    // i.e. mincore succeeds
    //             --- page written out by kernel
    //      next memcpy triggers a VDisk::read -- OOPS!

    // use PROT_NONE because PROT_READ causes a page fault which triggers a FUSE read that percolates to SV VDisk::read 
    // - that we dont want to happen


        if (mapAddr == MAP_FAILED)
        {
            mapAddr = mmap((void*) 0, curMapSize, PROT_NONE, MAP_SHARED, fd, curMapOffset);
        
            if (mapAddr == MAP_FAILED)
            {
                mappingStrategy->failureHandler();
            }
            
            if (mapAddr == MAP_FAILED)
            {
                if (errno != EAGAIN) 
                {
                    // disable if failure is not temporary

                    disabled = 1;
                    LOG(ERROR) << "mmap fd=" << fd << ":off=" << curMapOffset << ":size=" << curMapSize << " failed with errno=" 
                                << errno << ":" << strerror(errno) << endl;
                }

                break;
            }
            else
            {
                LOG(INFO) << "requested off=" << desiredOff << " mapping " << curMapOffset << ":" << curMapSize << endl;
                if (curMapSize == pageSize)
                {   
                    // if pagesize is being used, turn off sequential access
                    mappingStrategy = &randomStrategy;
                }
            }
        }

        int err = 0;

        unsigned char mincoreRet = 0;

        sv_assert(desiredOff >= curMapOffset);
        sv_assert(desiredOff < curMapOffset + curMapSize);

        err = mincore((char*)mapAddr + (desiredOff - curMapOffset), pageSize, &mincoreRet);

        if (err != 0)
        {
            disabled = 1;
            LOG(ERROR) << "mincore failed with errno=" << errno << ":string=" << strerror(errno) << ":off=" << desiredOff
                        << ":mapOff=" << curMapOffset << ":mapSize=" << curMapSize << endl;
            break;
        }

        if (!(mincoreRet & 0x01))
        {   
            break;
        }
        // if page is in cache, mmap again using PROT_READ to copy it
        // the previous mmap with PROT_NONE cant be used because it disallows memcpy
        copyAddr = mmap((void*) 0, pageSize, PROT_READ, MAP_SHARED, fd, desiredOff);

        if (copyAddr == MAP_FAILED)
        {
            break;
        }

        // map fails silently if it failed to mlock
        // hence we call mlock after mmap
        // also MAP_LOCKED doesnt work with PROT_NONE 
        // therefore we have to call mlock on the page mapped with PROT_READ
        int mlockRet = mlock(copyAddr, pageSize);
        if (mlockRet != 0)
        {
            LOG(ERROR) << "mlock " << desiredOff << " failed with errno=" << errno << ":string=" << strerror(errno) << endl;
            break;
        }

#ifndef DISABLE_READAHEAD
        // this is the alternate scheme to prevent
        // the call to mmap(*vmdk) from triggering a readahead
        // we advise the kernel that the map is used for random access
        int mret = madvise(copyAddr, pageSize, MADV_RANDOM);
        if (mret != 0)
        {
            LOG(WARNING) << "madvise failed with errno=" << errno 
                    << ":mapaddr=" << (void*) copyAddr
                    << ":mapSize=" << pageSize
                    << endl;
        }
#endif
        // check again
        err = mincore((char*)copyAddr, pageSize, &mincoreRet);

        if (err != 0)
        {
            disabled = 1;
            LOG(ERROR) << "mincore failed with errno=" << errno << ":string=" << strerror(errno) << ":off=" << desiredOff
                        << ":mapOff=" << curMapOffset << ":mapSize=" << curMapSize << endl;
            break;
        }

        if (!(mincoreRet & 0x01))
        {
            LOG(INFO) << "page no longer in mem " << cacheBlockId << endl;
            break;
        }

        sv_assert(sigbusRecvd == false);
        memcpy(data, copyAddr, pageSize); // triggers pagefault

        if (sigbusRecvd == true)
        {
            LOG(WARNING) << "signal recvd at " << cacheBlockId << endl;
            retcode = -1;
        }
        else if (vDisk.flushData.faultState == VDisk::Flush::FAULT_TRAPPED)
        {
            // deadlock averted 
            /*
                filemap_fault called
                  fuse kernel component 
                    fuse user component 
                      svfuse_read 
                        VDisk::read
            */
            LOG(WARNING) << "deadlock averted vdisk=" << vDisk.Id() << ":cacheblock=" << cacheBlockId << endl;
            retcode = -1;
        }
        else
        {
            // successful read from page cache
            retcode = 0;
        }

    } while (0); // do this only once - allows use of "break"

    if (copyAddr != MAP_FAILED)
    {
        int munmapRet = munmap(copyAddr, pageSize);
    }
    // if page is not in RAM, its going to be read from SSD
    // which will take time
    // in which case, lets turn on NFS writes
    perm.enableWrites();

    // reset variables
    sigbusRecvd = false;
    vDisk.flushData.faultState = VDisk::Flush::FAULT_NONE;
    vDisk.flushData.faultOffset = 0;

    // we may have to unmap the page
    mappingStrategy->postHandler();
    perm.postHandler();
    return retcode;
}


