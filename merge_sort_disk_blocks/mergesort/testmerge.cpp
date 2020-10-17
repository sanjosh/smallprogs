
#include "mergesort.h"

#include "MyTimeSpec.h"

int FILENUM=4;
int BLOCKNUM=512;
int numMerge = 13; // default

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
    if (argc > 3)
    {
        numMerge = atoi(argv[3]);
    }
/*
    if (argc > 4)
    {
        CHUNKSIZE = atoi(argv[4]);
    }
*/

    SFile::createDir();

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
        mylist[i]->checkIndex(); // if its sorted
    }
    free(buf);

    list<SFile*> inList;
    list<SFile*> outList;

    for (int i = 0; i < FILENUM; i++)
    {
        inList.push_back(mylist[i]);
        //mylist[i]->print();
    }

    cout << "========MERGE BEGINS==============" << endl;
    MyTimeSpec a1;
    a1.getCurrentTime();

    while (inList.size() > 1)
    {
        Smerge(inList, outList, numMerge, pass++);
        inList = outList;
        outList.clear();
    }

    MyTimeSpec a2;
    a2.getCurrentTime();

    MyTimeSpec diff = a2- a1;
    cout << "time taken=" << diff << endl;
    cout << "waiting for input" << endl;

    SFile* file = inList.front();
    file->checkIndex();
    
    getchar();
    file->print();

    SFile::removeDir();

    return 0;
}

/*
int convertStagingFile(int cur)
{
    StagingFile sfile(vDiskId, snapId, cur);
    
    StagingFileHeader* header;
    char* datablocks;
    StagingFile::allocBuffer(header, datablocks);

    int ret = sfile.open();
    ret = sfile.readFile(header);

    map<vdiskoffset_t, int> stagMap;
    for (int i = 0; i < header->numBlocks; i++)
    {
        vdiskoffset_t cacheBlockId = header->cacheBlockId[i];
        stagMap.insert(make_pair(cacheBlockId, datablocks + (i * cacheBlockSize)));
    }

    mylist[i] = new SFile(i, pass);
    SFileIter newIter(*mylist[i], O_WRONLY);

    map<vdiskoffset_t, char*>::iterator stagMapIter;
    for (stagMapIter iter = stagMap.begin(); iter != stagMap.end(); ++iter)
    {
        DiskBlk newblk;
        newblk.cacheblock = iter->first;

        newIter.writeNextBlock(iter->second, newblk);
    }

    free(header);
}
*/
