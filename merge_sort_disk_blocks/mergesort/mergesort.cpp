#include "mergesort.h"

#include <queue>

size_t CACHESIZE=4096;
size_t CHUNKSIZE=2*1024*1024;// same as staging block size

#define MAXFILENAME 256
#define DIRSTR "/hdd/merge%d/"
#define FILESTR DIRSTR "/sfile_p%d_f%d_c%d"

SFile::SFile(int in_fileNum, int in_pass) : fileNum(in_fileNum), pass(in_pass)
{
    numChunks = 1;
}


SFile::~SFile()
{
    char name[MAXFILENAME];
    for (int curChunk = 0; curChunk < numChunks; curChunk ++)
    {
        buildName(name, pass, fileNum, curChunk);
        ::remove(name);
    }
}


int SFile::createDir()
{
    char dirname[MAXFILENAME];
    sprintf(dirname, DIRSTR, getpid());
    int mkret = mkdir(dirname, S_IRWXU | S_IRWXO | S_IRWXG);
    assert(mkret == 0);
    return 0;
}

int SFile::removeDir()
{
    cout << "TODO : implement remove dir" << endl;
    return 0;
}

int SFile::open(int mode, int curChunk)
{
    int fd = -1;
    char name[MAXFILENAME];
    buildName(name, pass, fileNum, curChunk);

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
    char newname[MAXFILENAME];

    for (int curChunk = 0; curChunk < numChunks; curChunk ++)
    {
        buildName(oldname, pass, fileNum, curChunk);
        buildName(newname, pass+1, newFileNum, curChunk);
        int ret = ::rename(oldname, newname);
        if (ret != 0)
        {
            cerr << "failed rename " << oldname << ":" << newname << ":" << errno << endl;
            exit(1);
        }
        cout << "renamed " << oldname << ":" << newname << endl;
    }
    
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

void SFile::checkIndex() const
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

int SFile::buildName(char* name, int pass, int fileNum, int chunkNum)
{
    sprintf(name, FILESTR, getpid(), pass, fileNum, chunkNum);
    return 0;
}

// ============================================


SFileIter::SFileIter(SFile& in_file, int in_mode) : sfile(in_file), mode(in_mode)
{
    nextOffset = 0; 
    wasWritten = false;
    dataBufferLen = CHUNKSIZE;
    dataBuffer = (char*) malloc(dataBufferLen);
    curChunk = 0;
    fd = sfile.open(mode, curChunk);
    assert(fd >= 0);
    indexIter = sfile.index.begin();
}

SFileIter::~SFileIter()
{
    if (wasWritten)
    {
        // sync last buffer to disk
        ssize_t writeSize = write(fd, dataBuffer, dataBufferLen);
        assert(writeSize == dataBufferLen);
    }
    close(fd); 
    free(dataBuffer); 
}

const char* SFileIter::getNextBlock(DiskBlk& retBlk)
{
    assert(mode == O_RDONLY);

    if (nextOffset == 0)
    {
        ssize_t ioret = read(fd, dataBuffer, dataBufferLen);    
        assert(ioret == dataBufferLen);
    }
    const char* retbuf = (const char*)(dataBuffer + nextOffset);
    retBlk = *indexIter;

    retBlk.validate(retbuf);

    nextOffset += CACHESIZE;
    if (nextOffset == dataBufferLen)
    {
        nextOffset = 0;
        // here move to next chunk
        close(fd);
        curChunk ++;
        if (curChunk < sfile.numChunks)
            fd = sfile.open(mode, curChunk);
        else    
            fd = -1;
    }
    indexIter ++;
    // assert if indexIter is eof, then fd == -1
    return retbuf;
}

void SFileIter::writeNextBlock(const char* buf, DiskBlk& retBlk)
{
    assert(mode == O_WRONLY);
    
    if (nextOffset == dataBufferLen)
    {
        ssize_t ioret = write(fd, dataBuffer, dataBufferLen);    
        assert(ioret == dataBufferLen);
        nextOffset = 0;
        // here move to next chunk
        close(fd);
        curChunk = sfile.nextChunk();
        fd = sfile.open(mode, curChunk);
    }
    retBlk.offset = nextOffset;
    retBlk.fileNum = sfile.fileNum;

    memcpy(dataBuffer + nextOffset, buf, CACHESIZE);

    retBlk.validate(buf);

    sfile.index.push_back(retBlk);

    nextOffset += CACHESIZE;
    wasWritten = true;
}


// ===================================================

typedef std::priority_queue<SFileIter*, std::vector<SFileIter*>, SFileIterCmp> SFileIterMinHeap;

void Smerge_nway(SFile* file[], int numFiles, SFile& outFile)
{
    SFileIterMinHeap minheap;   

    cout << "merge of " << numFiles;

    SFileIter **inIter = (SFileIter**)malloc(sizeof(SFileIter*) * numFiles);

    for (int i = 0; i < numFiles; i++)
    {
        cout << " :" << file[i]->fileNum;
        inIter[i] = new SFileIter(*file[i], O_RDONLY);
        assert (!inIter[i]->eof());
        minheap.push(inIter[i]);
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
    free(inIter);
}


void Smerge(PassFileList& inList, PassFileList& outList, int numMerge, int pass)
{
    int mergenum = numMerge;

    do
    {
        while (inList.size() >= mergenum)
        {
            SFile** file = (SFile**)malloc(sizeof(SFile*) * numMerge);
    
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
        
            delete file;
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

