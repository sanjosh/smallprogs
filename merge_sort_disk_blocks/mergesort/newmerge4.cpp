
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

// TODO : writeNextBlock shud create new file once old is over

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
    bool validate(const char* buf) const
    {
        int memret = memcmp(buf, bytePattern.c_str(), bytePattern.size());
        assert(memret == 0);
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
    void check() const ;
    void print() const ;

    private:
    SFile(const SFile& other);
    SFile& operator =(const SFile& other);

};

SFile::SFile(int in_fileNum, int in_pass) : fileNum(in_fileNum), pass(in_pass)
{
}

#define MAXFILENAME 256

SFile::~SFile()
{
    char name[MAXFILENAME];
    sprintf(name, FILESTR, mypid, pass, fileNum);
    ::remove(name);
}


int SFile::open(int mode)
{
    int fd = -1;
    char name[MAXFILENAME];
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
    char oldname[MAXFILENAME];
    sprintf(oldname, FILESTR, mypid, pass, fileNum);
    char newname[MAXFILENAME];
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

    public:

    DiskBlkConstIter it; // index iter for read access

    SFileIter(SFile& in_file, int in_mode); // 4K block size as param?
    const char* getNextBlock(DiskBlk& retBlk);
    void writeNextBlock(const char* buf, DiskBlk& retBlk);
    ~SFileIter();
    bool eof() const
    {
        return (it == sfile.index.end());
    }
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

const char* SFileIter::getNextBlock(DiskBlk& retBlk)
{
    assert(mode == O_RDONLY);

    if (nextOffset == 0)
    {
        ssize_t ioret = read(fd, tmpbuf, tmpbuflen);    
        assert(ioret == tmpbuflen);
    }
    const char* retbuf = (const char*)(tmpbuf + nextOffset);

    it->validate(retbuf);

    nextOffset += CACHESIZE;
    if (nextOffset == tmpbuflen)
    {
        nextOffset = 0;
        // here move to next chunk
    }
    retBlk = *it;
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
        // here move to next chunk
    }
    retBlk.offset = nextOffset;
    retBlk.fileNum = sfile.fileNum;

    memcpy(tmpbuf + nextOffset, buf, CACHESIZE);

    retBlk.validate(buf);

    sfile.index.push_back(retBlk);

    nextOffset += CACHESIZE;
    wasWritten = true;
}

// =================

struct SFileIterCmp
{
    bool operator () (SFileIter* lhs, SFileIter* rhs)
    {
        const DiskBlk& b1 = *lhs->it;
        const DiskBlk& b2 = *rhs->it;
        return b1.operator >(b2);
    }
};

typedef std::priority_queue<SFileIter*, std::vector<SFileIter*>, SFileIterCmp> SFileIterMinHeap;

// =================

#define MAXMERGE 13

void Smerge_nway(SFile* file[], int numFiles, SFile& outFile)
{
    SFileIterMinHeap minheap;   

    cout << "merge of " << numFiles;

    SFileIter *inIter[MAXMERGE];
    for (int i = 0; i < numFiles; i++)
    {
        cout << " :" << file[i]->fileNum;
        inIter[i] = new SFileIter(*file[i], O_RDONLY);
        if (!inIter[i]->eof())
        {
            minheap.push(inIter[i]);
        }
    }
    cout << endl;

    SFileIter outIter(outFile, O_WRONLY);
    
    do
    {
        SFileIter* iter = minheap.top();
        minheap.pop();

        DiskBlk retBlk;
        const char* inbuf = iter->getNextBlock(retBlk);
        assert(inbuf);
        //cout << "in block=" << retBlk;

        outIter.writeNextBlock(inbuf, retBlk) ;

        if (!iter->eof()) minheap.push(iter);

    } while (minheap.size());

    for (int i = 0; i < numFiles; i++)
    {
        assert (inIter[i]->eof());
        delete inIter[i];
    }
}

typedef list<SFile*> PassFileList;


void Smerge(PassFileList& inList, PassFileList& outList, int pass)
{
    int mergenum = MAXMERGE;

    do
    {
        while (inList.size() >= mergenum)
        {
            SFile* file[MAXMERGE];
    
            for (int i = 0; i < mergenum; i++)
            {
                file[i] = inList.front();
                assert(file[i]->pass == pass);
                inList.pop_front();
            }
    
            SFile* outFile = new SFile(outList.size(), pass + 1);
            Smerge_nway(file, mergenum, *outFile);
    
            outList.push_back(outFile);
    
            for (int i = 0; i < mergenum; i++)
            {
                delete file[i];
            }

            //outFile->print();
        }
        
        mergenum = inList.size();

    } while (inList.size() > 1);

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
    char dirname[MAXFILENAME];
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
