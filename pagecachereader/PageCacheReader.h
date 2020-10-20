#ifndef PAGECACHEREADER_H
#define PAGECACHEREADER_H

using namespace std;


// =====================

// how should map/unmap of pages be done by pageCacheReader?
// SeqStrategy optimizes on number of mmaps in case sequential access
// RandomStrategy just maps & unmaps every offset requested
class Strategy
{
protected:
    PageCacheReader& reader;

public:
    Strategy(PageCacheReader& in_reader) : reader(in_reader) {}

    // calculate if page has to be mapped
    virtual void preHandler(off_t desiredOff) = 0;

    // how to handle failure of mmap
    virtual void failureHandler() = 0;

    // does page have to be unmapped?
    virtual void postHandler() = 0;
};

class SeqStrategy : public Strategy
{
    size_t sequentialMapSize; 
    static size_t defaultMapSize;  // starts at 1MB but is reduced

public:
    SeqStrategy(PageCacheReader& in_reader) : Strategy(in_reader)
    {
        sequentialMapSize = defaultMapSize; 
    }

    void preHandler(off_t desiredOff);

    void failureHandler();

    void postHandler();

};

class RandomStrategy: public Strategy
{
public:
    RandomStrategy(PageCacheReader& in_reader) : Strategy(in_reader)
    {
    }

    void preHandler(off_t desiredOff);

    void failureHandler();

    void postHandler();
};

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


// this standalone class allows you to read a page
// from the Linux kernel cache

class PageCacheReader
{
    VDisk& vDisk;
    string vDiskName;
    size_t fileSize; 

    int disabled; // flag set when pagecache reader fails
    // after that all reads are failed

    bool sigbusRecvd;

    int fd;
    int lower_fd;

    Strategy* mappingStrategy;
    SeqStrategy seqStrategy;
    RandomStrategy randomStrategy;
    friend class SeqStrategy;
    friend class RandomStrategy;

    PermissionStrategy perm;

    void* mapAddr;
    const size_t pageSize;
    off_t curMapOffset; // within file
    size_t curMapSize; // within file

    public:

    PageCacheReader(VDisk& in_vDisk, const size_t in_pageSize);

    ~PageCacheReader();

    int open(const string& nfsShareName, const string& nfsShareLowerFS, const string& vDiskName, bool in_sequentialAccess);
        
    // read a specified offset
    int read(vdiskoffset_t cacheBlockId, char* data);
};
    
#endif
