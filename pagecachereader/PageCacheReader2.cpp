#include <unistd.h> // mincore
#include <sys/mman.h> // mincore
#include <fcntl.h> // open
#include <sys/stat.h> // fchmod, fstat
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "Common.h"
#include "SVConfig.h"
#include "PageCacheReader.h"
#include "VDisk.h"
#include "SignalHandler.h"

// #define MAX_BATCH_READS 100                 // number of reads after which the file permission is toggled

void PageCacheReader::preHandler(off_t desiredOff)
{
    // if nothing mapped or desired offset beyond current map

    if ((mapAddr == MAP_FAILED) || (desiredOff != curMapOffset))
    {
        // unmap any previously mapped pages

        if (mapAddr != MAP_FAILED)
        {
            munmap(mapAddr, curMapSize);
            svout << "new off=" << desiredOff << " unmapping " << curMapOffset << ":" << curMapSize << endl;
            mapAddr = MAP_FAILED;
        }

        curMapOffset = desiredOff;
        curMapSize = pageSize;
    }
}

void PageCacheReader::postHandler()
{
    svout << "unmapping " << curMapOffset << ":" << curMapSize << endl;
    int err = munmap(mapAddr, curMapSize);

    if (err != 0)
    {
        disabled = 1;
        LOG(WARNING) << "munmap failed with errno=" << errno << ":" << strerror(errno) << endl;
    }

    mapAddr = MAP_FAILED;
}

// =====================
#if 0

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
        LOG(WARNING) << "Failed to open lower fd=" << lower_fd << " errno=" << errno << endl;
        return -errno;
    }

    struct stat statBuf;

    if (fstat(lower_fd, &statBuf) != 0)
    {
        LOG(WARNING) << "Failed to stat lower fd=" << lower_fd << " errno=" << errno << endl;
        return -errno;
    }
    
    fileSize = statBuf.st_size;
    return 0;
}

void PermissionStrategy::preHandler()
{
    if ((numReads == 0) && (lower_fd != INVALID_FD) && (!writesEnabled))
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
    numReads++;

/*
    numReads ++;
    // turn on write perm after every MAX_BATCH_READS reads
    if (numReads == MAX_BATCH_READS)
    {
        enableWrites();
        // and let some NFS writes proceed
        usleep(100);
        numReads = 0;
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
    // reset permissions on the file

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
#endif

// =====================

PageCacheReader::PageCacheReader(VDisk& in_vDisk, const size_t in_pageSize) : vDisk(in_vDisk), pageSize(in_pageSize)
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

int PageCacheReader::open(const string& nfsShareName, const string& nfsShareLowerFS, const string& in_vDiskName)
{
    vDiskName = in_vDiskName; 
    string name = nfsShareName + vDiskName;
    string lowerName = nfsShareLowerFS + vDiskName;
    
    // name here is /svfuse/win6-flat.vmdk (e.g.)
    fd = ::open(name.c_str(),  O_RDONLY);
    int fd_errno = (fd < 0) ? -errno : 0; // save it bfor its lost
    lower_fd = ::open(name.c_str(), O_RDONLY);
    int lowerfd_errno = -errno; // save it bfor its lost

    if ((fd < 0) || (lower_fd < 0))
    {
        // you get ENOENT error in system shutdown when /svfuse is being unmounted
        if ((fd_errno != ENOENT) && (lowerfd_errno != ENOENT))
        {
            LOG(ERROR) << "unable to open pagecache reader for file=" << name 
            << ":err=" << fd_errno 
            << ":err=" << lowerfd_errno << endl;
        }
        // Note that you may get ENOENT error while system is in shutdown when /svfuse is being unmounted

        LOG(WARNING) << "unable to open pagecache reader for file=" << name << ":fd=" << fd << ":lower_fd=" << lower_fd << ":fd_errno=" 
                    << fd_errno << ":lowerfd_errno=" << lowerfd_errno << endl;

        disabled = 1;
        close(lower_fd);
        lower_fd = INVALID_FD;
        close(fd);
        fd = INVALID_FD;
        return -1;
    }
    else
    {
        sv_assert(fd >= 0);
        //sv_assert(perm.lower_fd >= 0);
    }

    struct stat statBuf;

    if (fstat(lower_fd, &statBuf) != 0)
    {
        LOG(WARNING) << "Failed to stat lower fd=" << lower_fd << " errno=" << errno << endl;
        disabled = 1;
        close(lower_fd);
        lower_fd = INVALID_FD;
        close(fd);
        fd = INVALID_FD;
        return -1;
    }
    
    fileSize = statBuf.st_size;
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
            // perm.enableWrites();
            LOG(INFO) << "pagecache reader is disabled for " << vDiskName << endl;
            disabled = 2; // no need to print error msg again
        }

        disabled = 2; // no need to print error msg again
        return -1;
    }

    // perm.preHandler();
    int retcode = -1;
    off_t desiredOff = cacheBlockId * pageSize;

    if (desiredOff + pageSize > fileSize)
    {
        LOG(WARNING) << "out of bounds offset = " << desiredOff << " filesize = " << fileSize << endl;
        return -1;
    }

    pthread_mutex_lock (&vDisk.flushData.vDiskWriteMutex);

    if (vDisk.flushData.curOffsetInWrite && (cacheBlockId == vDisk.flushData.curWriteOffset))
    {
        pthread_mutex_unlock (&vDisk.flushData.vDiskWriteMutex);
        LOG(WARNING) << "vdisk write in progress off=" << desiredOff << ":size=" << fileSize << endl;  
        return -1;
    }  

    pthread_mutex_unlock (&vDisk.flushData.vDiskWriteMutex);
    preHandler(desiredOff);
    sv_assert(curMapSize);
    vDisk.flushData.faultOffset = cacheBlockId;
    vDisk.flushData.faultState = VDisk::Flush::FAULT_SET;

    // mmap flags explained :
    // use MAP_LOCKED because we must lock the page to prevent it from being paged out between the call to mincore and subsequent memcpy below.
    // i.e. mincore succeeds
    //             --- page written out by kernel
    //      next memcpy triggers a VDisk::read -- OOPS!

    // use PROT_NONE because PROT_READ causes a page fault which triggers a FUSE read that percolates to SV VDisk::read 
    // - that we dont want to happen


    mapAddr = mmap((void*) 0, curMapSize, PROT_NONE, MAP_SHARED, fd, curMapOffset);
    
    if (mapAddr == MAP_FAILED)
    {
        if (errno != EAGAIN) 
        {
            // disable if failure is not temporary

            disabled = 1;
            LOG(WARNING) << "mmap fd=" << fd << ":off=" << curMapOffset << ":size=" << curMapSize << " failed with errno=" 
                        << errno << ":" << strerror(errno) << endl;
        }
        
        return returnFromRead (MAP_FAILED, -1);
    }

    svout << "mmaped off=" << desiredOff << " mapping " << curMapOffset << ":" << curMapSize << endl;
    int err = 0;
    unsigned char mincoreRet = 0;
    sv_assert(desiredOff == curMapOffset);

    // check if the page is in RAM

    err = mincore((char*) mapAddr, pageSize, &mincoreRet);

    if (err != 0)
    {
        disabled = 1;
        LOG(WARNING) << "mincore failed with errno=" << errno << ":string=" << strerror(errno) << ":off=" << desiredOff
            << ":mapOff=" << curMapOffset << ":mapSize=" << curMapSize << endl;
        munmap(mapAddr, curMapSize);
        mapAddr = MAP_FAILED;
        return returnFromRead (MAP_FAILED, -1);
    }

    if (!(mincoreRet & 0x01))
    {
        return returnFromRead (MAP_FAILED, -1);
    }

    // if page is in cache, mmap again using PROT_READ to copy it
    // the previous mmap with PROT_NONE cant be used because it disallows memcpy

    void* copyAddr = mmap((void*) 0, pageSize, PROT_READ, MAP_SHARED, fd, desiredOff);

    if (copyAddr == MAP_FAILED)
    {
        return returnFromRead (MAP_FAILED, -1);
    }
        
    // prevent the call to mmap(*vmdk) from triggering a readahead. we advise the kernel that the map is used for random access.

    int mret = madvise(copyAddr, pageSize, MADV_RANDOM);

    if (mret != 0)
    {
        LOG(WARNING) << "madvise failed with errno=" << errno << ":mapaddr=" << (void*) copyAddr << ":mapSize=" << pageSize << endl;
        return returnFromRead (copyAddr, -1);
    }

    // map fails silently if it failed to mlock hence we call mlock after mmap also MAP_LOCKED doesnt work with PROT_NONE 
    // therefore we have to call mlock on the page mapped with PROT_READ

    int mlockRet = mlock(copyAddr, pageSize);

    if (mlockRet != 0)
    {
        LOG(WARNING) << "mlock " << desiredOff << " failed with errno=" << errno << ":string=" << strerror(errno) << endl;
        return returnFromRead (copyAddr, -1);
    }

    // check again whether the address is in RAM since now it is guaranteed to be locked

    err = mincore((char*)copyAddr, pageSize, &mincoreRet);

    if (err != 0)
    {
        disabled = 1;
        LOG(WARNING) << "mincore failed with errno=" << errno << ":string=" << strerror(errno) << ":off=" << desiredOff
                        << ":mapOff=" << curMapOffset << ":mapSize=" << curMapSize << endl;
        return returnFromRead (copyAddr, -1);
    }

    if (!(mincoreRet & 0x01))
    {
        LOG(INFO) << "page no longer in mem " << cacheBlockId << endl;
        return returnFromRead (copyAddr, -1);
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
    // if page is not in RAM, its going to be read from SSD
    // which will take time
    // in which case, lets turn on NFS writes
    //perm.enableWrites();

    return returnFromRead (copyAddr, retcode);
}

int PageCacheReader::returnFromRead(void *copyAddr, int retCode)
{
    // we may have to unmap the page

    if (copyAddr != MAP_FAILED)
    {
        munmap(copyAddr, pageSize);
    }

    // reset variables

    sigbusRecvd = false;
    vDisk.flushData.faultState = VDisk::Flush::FAULT_NONE;
    vDisk.flushData.faultOffset = 0;
    postHandler();
    // perm.postHandler();
    return retCode;
}
