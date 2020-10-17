#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include <list>
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

using namespace std;


extern size_t CACHESIZE;
extern size_t CHUNKSIZE;

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
#ifdef MERGE_DBG
        int memret = memcmp(buf, bytePattern.c_str(), bytePattern.size());
        assert(memret == 0);
#endif
        return true;
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
    
class SFile
{
    public:

    DiskBlkList index;
    int fileNum;
    int pass;
    int numChunks;

    friend class SFileIter;

    SFile(int in_fileNum, int in_pass);
    ~SFile();

    static int createDir();
    static int removeDir(); // later

    int open(int mode, int curChunk);
    int nextChunk() { int ret= numChunks++; return ret;}
    void remove();
    void rename(int newFileNum);
    void checkIndex() const ;
    void print() const ;

    static int buildName(char* name, int pass, int fileNum, int chunkNum);

    private:
    SFile(const SFile& other);
    SFile& operator =(const SFile& other);

};

// ==================================

class SFileIter
{
    SFile& sfile;
    int fd;
    int mode;
    int curChunk;

    bool wasWritten;
    off_t nextOffset;

    char* dataBuffer;
    size_t dataBufferLen; 

    public:

    DiskBlkConstIter indexIter; // index iter used when mode= O_RDONLY 

    SFileIter(SFile& in_file, int in_mode); // 4K block size as param?
    const char* getNextBlock(DiskBlk& retBlk); // read mode
    void writeNextBlock(const char* buf, DiskBlk& retBlk); // write mode
    ~SFileIter();
    bool eof() const
    {
        return (indexIter == sfile.index.end());
    }
};


// =================

struct SFileIterCmp
{
    bool operator () (SFileIter* lhs, SFileIter* rhs)
    {
        const DiskBlk& b1 = *lhs->indexIter;
        const DiskBlk& b2 = *rhs->indexIter;
        return b1.operator >(b2);
    }
};


typedef list<SFile*> PassFileList;

void Smerge(PassFileList& inList, PassFileList& outList, int numMerge, int pass);

void Smerge_nway(SFile* file[], int numFiles, SFile& outFile);

#endif
