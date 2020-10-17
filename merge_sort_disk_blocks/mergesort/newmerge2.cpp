
// list::sort
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <cctype>

#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

#include "MyTimeSpec.h"


int mypid = -1;
#define CACHESIZE 4096

using namespace std;

struct DiskBlk
{
    int cacheblock;
    int fileNum;
    int offset;
    string bytePattern;

    public:
    DiskBlk() { cacheblock = -1; fileNum = -1; offset = -1;}

    bool operator < (const DiskBlk& other) const
    {
        return (cacheblock < other.cacheblock);
    }
    bool operator > (const DiskBlk& other) const
    {
        return other.operator < (*this);
    }

    friend ostream& operator <<(ostream& ostr, const DiskBlk& me)
    {
        ostr << "cache=" << me.cacheblock 
            << ":file=" << me.fileNum 
            << ":offset=" << me.offset 
            << ":pattern=" << me.bytePattern << endl;
        return ostr;
    }
};

struct DiskBlkComp
{
    bool operator () (const DiskBlk& lhs, const DiskBlk& rhs)
    {
        return lhs.operator > (rhs);
    }
};

typedef std::list<DiskBlk> DiskBlkList;
typedef DiskBlkList::iterator DiskBlkIter;
typedef DiskBlkList::const_iterator DiskBlkConstIter;
typedef std::priority_queue<DiskBlk, std::vector<DiskBlk>, DiskBlkComp> DiskBlkMinHeap;

// ================================
#define DIRSTR "/tmp/run%d/"
#define FILESTR DIRSTR "/sfile_pass%d_%d"
    
class SFile
{
    public:

    DiskBlkList index;
    int fileNum;
    int pass;

    friend class SFileIter;

    SFile(int in_fileNum, int in_pass);
    ~SFile();

    int open(int mode);
    void remove();
    void rename(int newFileNum);
    //void sort() { index.sort(); }
    void check() const ;
    void print() const ;

    private:
    SFile(const SFile& other);
    SFile& operator =(const SFile& other);

};

SFile::SFile(int in_fileNum, int in_pass) : fileNum(in_fileNum), pass(in_pass)
{
}

SFile::~SFile()
{
    char name[256];
    sprintf(name, FILESTR, mypid, pass, fileNum);
    ::remove(name);
}


int SFile::open(int mode)
{
    int fd = -1;
    char name[256];
    sprintf(name, FILESTR, mypid, pass, fileNum);

    if (mode == O_RDONLY)
    {
        fd = ::open(name, mode);
    }
    else
    {
        fd = ::open(name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    }
    return fd;
}

void SFile::rename(int newFileNum) 
{
    char oldname[256];
    sprintf(oldname, FILESTR, mypid, pass, fileNum);
    char newname[256];
    sprintf(newname, FILESTR, mypid, pass+1, newFileNum);
    int ret = ::rename(oldname, newname);
    if (ret != 0)
    {
        cerr << "failed rename " << oldname << ":" << newname << ":" << errno << endl;
        exit(1);
    }
    cout << "renamed " << oldname << ":" << newname << endl;

    DiskBlkIter it;
    for (it=index.begin(); it!=index.end(); ++it)
    {
        it->fileNum = newFileNum;
    }
    pass ++;

    fileNum = newFileNum;
}

void SFile::print() const
{
    std::cout << "ptr=" << this << ":file=" << fileNum << ":pass=" << pass << ":size=" << index.size() << endl;
    DiskBlkConstIter it;
    for (it=index.begin(); it!=index.end(); ++it)
    {
        std::cout << *it;
    }
    std::cout << endl;

}

void SFile::check() const
{
    DiskBlkConstIter it;
    bool first = true;
    DiskBlkConstIter prev;
    int pos = 0;
    for (it=index.begin(); it!=index.end(); ++it, pos++)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            if (*it < *prev)
            {
                cout << "FAILED "
                    << ":pos=" << pos 
                    << ":me=" << *it
                    << ":prev=" << *prev
                    << endl;
                print();
                assert(0);
            }
        }
        prev = it;
    }
}

// ==================================

class SFileIter
{
    SFile& sfile;
    int fd;
    int mode;

    bool wasWritten;
    off_t nextOffset;

    char* tmpbuf;
    size_t tmpbuflen; 

    DiskBlkConstIter it; // for verification

    public:

    SFileIter(SFile& in_file, int in_mode); // 4K block size as param?
    const char* getNextBlock();
    void writeNextBlock(const char* buf, DiskBlk& retBlk);
    ~SFileIter();
};

SFileIter::SFileIter(SFile& in_file, int in_mode) : sfile(in_file), mode(in_mode)
{
    nextOffset = 0; 
    wasWritten = false;
    tmpbuflen = 2 * 1024 * 1024;
    tmpbuf = (char*) malloc(tmpbuflen);
    fd = sfile.open(mode);
    assert(fd >= 0);
    it = sfile.index.begin();
}

SFileIter::~SFileIter()
{
    if (wasWritten)
    {
        // sync last buffer to disk
        ssize_t writeSize = write(fd, tmpbuf, tmpbuflen);
        assert(writeSize == tmpbuflen);
    }
    close(fd); 
    free(tmpbuf); 
}

static int bufcmp(const char* buf, char byte, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (buf[i] != byte) return -i;
    }
    return 0;
}

const char* SFileIter::getNextBlock()
{
    assert(mode == O_RDONLY);

    if (nextOffset == 0)
    {
        ssize_t ioret = read(fd, tmpbuf, tmpbuflen);    
        assert(ioret == tmpbuflen);
    }
    const char* retbuf = (const char*)(tmpbuf + nextOffset);
    int memret = memcmp(retbuf, it->bytePattern.c_str(), it->bytePattern.size());
    assert(memret == 0);

    nextOffset += CACHESIZE;
    if (nextOffset == tmpbuflen)
    {
        nextOffset = 0;
    }
    it ++;
    return retbuf;
}

void SFileIter::writeNextBlock(const char* buf, DiskBlk& retBlk)
{
    assert(mode == O_WRONLY);
    
    if (nextOffset == tmpbuflen)
    {
        ssize_t ioret = write(fd, tmpbuf, tmpbuflen);    
        assert(ioret == tmpbuflen);
        nextOffset = 0;
    }
    retBlk.offset = nextOffset;
    retBlk.fileNum = sfile.fileNum;

    memcpy(tmpbuf + nextOffset, buf, CACHESIZE);

    int memret = memcmp(buf, retBlk.bytePattern.c_str(), retBlk.bytePattern.size());
    assert(memret == 0);

    sfile.index.push_back(retBlk);

    nextOffset += CACHESIZE;
    wasWritten = true;
}

// =================


void Smerge_2way(SFile& file1, SFile& file2, SFile& outFile)
{
    DiskBlkList tmpindex = file1.index;
    DiskBlkList tmpfile2index = file2.index;
    tmpindex.merge(tmpfile2index);
       
    cout << "merging ptr=" << &file1 << ":" << file1.fileNum << ":" << file1.index.size() << " with ptr=" << &file2 << ":" << file2.fileNum << ":" << file2.index.size() << endl;

    // in next version, do this only once at end
    // open multiple iters indexed by fileNum
    // and read as appropriate
    SFileIter inIter1 (file1, O_RDONLY);
    SFileIter inIter2(file2, O_RDONLY);
    SFileIter outIter(outFile, O_WRONLY);
    
    DiskBlkConstIter blkIter = tmpindex.begin();
    while (blkIter != tmpindex.end())
    {
        const DiskBlk& inblk = *blkIter;         
        const char* inbuf = NULL;
        //cout << "inblock=" << inblk;

        if (inblk.fileNum == file1.fileNum)
        {
            inbuf = inIter1.getNextBlock();
        }
        else if (inblk.fileNum == file2.fileNum)
        {
            inbuf = inIter2.getNextBlock();
        }
        else
        {
            assert("not" == 0);
        }
        DiskBlk retBlk = inblk; 
        outIter.writeNextBlock(inbuf, retBlk) ;
        blkIter ++;
    }
}

void Smerge_3way(SFile& file1, SFile& file2, SFile& file3, SFile& outFile)
{
    DiskBlkMinHeap minheap;   
    cout << "merging ptr=" << &file1 << ":" << file1.fileNum << ":" << file1.index.size() 
        << " with ptr=" << &file2 << ":" << file2.fileNum << ":" << file2.index.size() 
        << " with ptr=" << &file3 << ":" << file3.fileNum << ":" << file3.index.size() << endl;

    // in next version, do this only once at end
    // open multiple iters indexed by fileNum
    // and read as appropriate
    SFileIter inIter1 (file1, O_RDONLY);
    SFileIter inIter2(file2, O_RDONLY);
    SFileIter inIter3(file3, O_RDONLY);

    SFileIter outIter(outFile, O_WRONLY);
    
    DiskBlkConstIter indexIter1 = file1.index.begin();
    DiskBlkConstIter indexIter2 = file2.index.begin();
    DiskBlkConstIter indexIter3 = file3.index.begin();

    DiskBlkConstIter end1 = file1.index.end();
    DiskBlkConstIter end2 = file2.index.end();
    DiskBlkConstIter end3 = file3.index.end();

    if (indexIter1 != end1)  
    {
        minheap.push(*indexIter1);
    }
    if (indexIter2 != end2)  
    {
        minheap.push(*indexIter2);
    }
    if (indexIter3 != end3)  
    {
        minheap.push(*indexIter3);
    }

    do
    {
        DiskBlk inblk = minheap.top();
        minheap.pop();

        const char* inbuf = NULL;
        if (inblk.fileNum == file1.fileNum)
        {
            inbuf = inIter1.getNextBlock();
            indexIter1++;
            if (indexIter1 != end1) minheap.push(*indexIter1);
        }
        else if (inblk.fileNum == file2.fileNum)
        {
            inbuf = inIter2.getNextBlock();
            indexIter2++;
            if (indexIter2 != end2) minheap.push(*indexIter2);
        }
        else if (inblk.fileNum == file3.fileNum)
        {
            inbuf = inIter3.getNextBlock();
            indexIter3++;
            if (indexIter3 != end3) minheap.push(*indexIter3);
        }
        else
        {
            assert("not" == 0);
        }

        DiskBlk retBlk = inblk; 
        outIter.writeNextBlock(inbuf, retBlk) ;

    } while (minheap.size());
}

typedef list<SFile*> PassFileList;

void Smerge(PassFileList& inList, PassFileList& outList, int pass)
{
    while (inList.size() >= 3)
    {
        SFile* file1 = inList.front();
        assert(file1->pass == pass);
        inList.pop_front();

        SFile* file2 = inList.front();
        assert(file2->pass == pass);
        inList.pop_front();

        SFile* file3 = inList.front();
        assert(file3->pass == pass);
        inList.pop_front();

        SFile* outFile = new SFile(outList.size(), pass + 1);
        Smerge_3way(*file1, *file2, *file3, *outFile);

        outList.push_back(outFile);
        delete file1;
        delete file2;
        delete file3;

        //outFile->//print();
    }

    // do 2-way merge if inList = 2
    if (inList.size() == 2)
    {
        SFile* file1 = inList.front();
        assert(file1->pass == pass);
        inList.pop_front();

        SFile* file2 = inList.front();
        assert(file2->pass == pass);
        inList.pop_front();

        SFile* outFile = new SFile(outList.size(), pass + 1);
        Smerge_2way(*file1, *file2, *outFile);

        outList.push_back(outFile);
        delete file1;
        delete file2;
    }

    if (inList.size() == 1)
    {
        SFile* lastFile = inList.front(); 
        lastFile->rename(outList.size());
        inList.pop_front();
        outList.push_back(lastFile);
    }
    assert(inList.size() == 0);

    cout << "END OF PASS=" << pass 
        << ":inlist=" <<  inList.size() 
        << ":outlist=" << outList.size() << endl;
    cout << "=============================" << endl;
}


// ===================================

int FILENUM=4;
int BLOCKNUM=512;

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        FILENUM = atoi(argv[1]);
    }
    if (argc > 2)
    {
        BLOCKNUM = atoi(argv[2]);
    }
    mypid = getpid();
    char dirname[256];
    sprintf(dirname, DIRSTR, mypid);
    int mkret = mkdir(dirname, S_IRWXU | S_IRWXO | S_IRWXG);
    assert(mkret == 0);

    SFile *mylist[FILENUM];
    int pass = 0;

    srand(76);
    char* buf = (char*)malloc(CACHESIZE);
    for (int i = 0; i < FILENUM; i++)
    {
        mylist[i] = new SFile(i, pass);
        SFileIter iter(*mylist[i], O_WRONLY);
        for (int j = 0; j < BLOCKNUM; j++)
        {
            DiskBlk newblk;
            newblk.cacheblock = (j*FILENUM) + i;
            //newblk.bytePattern = 'a' + (i % 26);
            //memset(buf, newblk.bytePattern, CACHESIZE);
            sprintf(buf, "file%d_off%u_blk%u", i, j, newblk.cacheblock);
            newblk.bytePattern = buf;

            iter.writeNextBlock(buf, newblk);
        }
        mylist[i]->check(); // if its sorted
    }
    free(buf);

    list<SFile*> inList;
    list<SFile*> outList;

    for (int i = 0; i < FILENUM; i++)
    {
        inList.push_back(mylist[i]);
        //mylist[i]->print();
    }

    cout << "========MERGE===============" << endl;
    MyTimeSpec a1;
    a1.getCurrentTime();

    while (inList.size() > 1)
    {
        Smerge(inList, outList, pass++);
        inList = outList;
        outList.clear();
    }

    MyTimeSpec a2;
    a2.getCurrentTime();

    MyTimeSpec diff = a2- a1;
    cout << "time taken=" << diff << endl;
    cout << "waiting for input" << endl;

    SFile* file = inList.front();
    file->check();
    
    getchar();
    file->print();

    return 0;
}
