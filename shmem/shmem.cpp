#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;


#define myassert(cond, mesg) \
    if (!(cond)) { \
        printf(mesg); \
        exit(1); \
    }

class ShmemAlloc
{
    int fd;
    off_t size;

    void* mmapAddr;
    off_t mmapSize;

    // if nextFree > nextAlloc - its a rollover
    off_t nextAlloc;
    off_t allocSize;
    off_t nextFree;

    public:

    ShmemAlloc(const char* name, off_t size) : size(size), mmapSize(size), nextAlloc(0), nextFree(0), allocSize(0)
    {
        const int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        const int perm = O_RDWR | O_CREAT | O_TRUNC;
        const int mmapPerm = PROT_READ | PROT_WRITE;

        fd = ::open(name, perm, mode);
        myassert(fd >= 0, "failed to open fd");

        int res = ftruncate(fd, size);
        myassert(res >= 0, "failed to increase file size");

        mmapAddr = ::mmap(0, mmapSize, mmapPerm, MAP_SHARED, fd, 0);
        myassert(mmapAddr != MAP_FAILED, "failed to mmap");
    }

    ~ShmemAlloc()
    {
        if (mmapAddr != MAP_FAILED) {
            munmap(mmapAddr, mmapSize);
        }
        close(fd);
    }

    off_t freeSize() const
    {
        return mmapSize - allocSize;
    }

    off_t ptrToOffset(void* addr)
    {
        return ((char*)addr - (char*)mmapAddr);
    }

    void* alloc(size_t requestSize)
    {
        if (allocSize + requestSize > size)
        {
            return nullptr;
        }
        if (mmapSize - nextAlloc < requestSize)
        {       
            // allocate last remaining portion of file
            allocSize += (mmapSize - nextAlloc);
            nextAlloc = 0;
        }
        void* retPtr = (char*)mmapAddr + nextAlloc;
        nextAlloc += requestSize;
        allocSize += requestSize;
        
        return retPtr;
    }

    int freeTill(void* freeAddr)
    {
        // ptr must lie within nextFree- nextAlloc range
        off_t relativeOffset = (char*)freeAddr - (char*)mmapAddr;

        if ((relativeOffset < 0) || (relativeOffset >= mmapSize))
        {
            assert("failed" == 0);
        }

        if (nextFree >= nextAlloc) // rollover - also check equal
        {
            if (relativeOffset >= nextFree) 
            {
                // ok
                allocSize -= (relativeOffset - nextFree);
                assert(allocSize > nextAlloc);
                nextFree = relativeOffset;
            }
            else if (relativeOffset < nextAlloc)
            {
                // ok
                allocSize = (nextAlloc - relativeOffset);
                nextFree = relativeOffset;
            }
            else
            {
                assert("invalid ptr" == 0);
            }
        }        
        else
        {
            if ((relativeOffset >= nextFree) && (relativeOffset < nextAlloc))
            {
                // ok
                allocSize -= (relativeOffset - nextFree);
                nextFree = relativeOffset;
            }
            else
            {
                assert("invalid ptr" == 0);
            }
        }
        assert(allocSize <= mmapSize);
        assert(allocSize >= 0);
        return 0;
    }
};

int main()
{
    ShmemAlloc alloc("/tmp/name", 1ULL << 15);

    do
    {
        vector<void*> vec;
        int i;
        while (1)
        {
            void* ptr = alloc.alloc(623);
            if (ptr == nullptr) break;
            if (++i % 2 == 0) vec.push_back(ptr);
            cout << "alloc ptr=" << alloc.ptrToOffset(ptr) << endl;
        }

        for (auto& v : vec)
        {
            void* ptr = v;
            alloc.freeTill(ptr);
            cout << "free size=" << alloc.freeSize() << endl;
        }

   } while (1);
}

