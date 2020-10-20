#ifndef PAGECACHEREADER_H
#define PAGECACHEREADER_H

using namespace std;

#if 0
<<<<<<< HEAD
>>>>>>> d61fb70d9be14d14a164c7d6699539425e89ecd0
=======
>>>>>>> 4da231c0c4abb267346f457f52259311d6b99b41
// if you want to safely read pages related to *flat-vmdk file
// from linux page cache, you have to block out NFS writes
// NFS calls getattr to check for permissions
// this class periodically turns off and on the write permissions 
// /svfuse_lower/*flat-vmdk file to block out NFS

struct PermissionStrategy
{
    bool writesEnabled;
    int numReads;
    int lower_fd;
    string name;


    PermissionStrategy() : writesEnabled(true), numReads(0), lower_fd(INVALID_FD) {}

    int open(const string& in_name, size_t& fileSize);

    void close();

    void enableWrites();
        
    void preHandler();

    void postHandler();

    ~PermissionStrategy();
};
#endif

// this standalone class allows you to read a page
// from the Linux kernel cache

class PageCacheReader
{
    VDisk& vDisk;
    string vDiskName;
    size_t fileSize;
    bool sigbusRecvd;
    int fd; 
    int lower_fd; 
    int disabled;
    // PermissionStrategy perm;

    void* mapAddr;
    const size_t pageSize;
    off_t curMapOffset; // within file
    size_t curMapSize; // within file

    void preHandler(off_t desiredOff);
    void postHandler();

public:
    PageCacheReader(VDisk& in_vDisk, const size_t in_pageSize);

    ~PageCacheReader();

    int open(const string& nfsShareName, const string& nfsShareLowerFS, const string& vDiskName);
        
    // read a specified offset

    int read(vdiskoffset_t cacheBlockId, char* data);

    int returnFromRead(void *copyAddr, int retCode);
};
    
#endif
