

/*
    cacheid, offset, dataptr
    0
    1
    2

    sort
    
    save()
    {
        for (i = list)
            write(fd, data + (list[i].offset*4096), 4096);
    }

    load()
    {
        data = alloc 2MB buffer
        for (i in list)
            read(fd, data + (list[i].offset*4096), 4096);
    }
*/

// list::sort
#include <iostream>
#include <list>
#include <string>
#include <cctype>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>


int mypid = -1;

using namespace std;

struct DiskBlk
{
    int cacheblock;
    int offset;

    public:
    DiskBlk() { cacheblock = 0;}
    DiskBlk(int in, int o) { cacheblock = in; offset=o;}
    DiskBlk(const DiskBlk& other) { cacheblock = other.cacheblock; offset=other.offset;}
    int& operator *() {return cacheblock;}
    DiskBlk& operator += (const DiskBlk& val) { cacheblock+=val.cacheblock; return *this;}

    bool operator < (const DiskBlk& other) const
    {
        return (cacheblock < other.cacheblock);
    }

    friend ostream& operator <<(ostream& ostr, const DiskBlk& me)
    {
        ostr << me.cacheblock; return ostr;
    }
};


typedef std::list<DiskBlk> MList;
typedef MList::iterator MIter;
typedef MList::const_iterator MConstIter;


class BMList
{
    public:

    MList mlist;
    int num;
    size_t size;
    
    BMList(int in_num) :num(in_num) {}

    ~BMList() { cout << "deleted " << num << endl; }
    
    void print() const;
    void sort() { mlist.sort();}
    void check() const;
    void save(int pass);
    void load(int pass);

#define MLISTSTR "/tmp/merge_%d_%d_%d"

    void remove(int pass);
    void rename(int pass)
    {
        char oldname[256];
        sprintf(oldname, MLISTSTR, mypid, pass, num);
        char newname[256];
        sprintf(newname, MLISTSTR, mypid, pass+1, num);
        int ret = ::rename(oldname, newname);
        cout << "renamed " << oldname << ":" << newname << endl;
        assert(ret == 0);
    }
    void merge(BMList& other)
    {
        mlist.merge(other.mlist);
    }
};

void BMList::save(int pass)
{
    // instead of one, save into multiple files of fixed size
    // and change load accordingly

    char name[256];
    sprintf(name, MLISTSTR, mypid, pass, num);
    int fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXO | S_IRWXG);
    assert(fd >= 0);

    size = mlist.size();

    MConstIter it;
    DiskBlk diskblk;
    for (it=mlist.begin(); it != mlist.end(); ++it)
    {
        diskblk = *it;
        ssize_t ret = write(fd, &diskblk, sizeof(DiskBlk));
        assert(ret == sizeof(DiskBlk));
    }
    close(fd);
    cout << "saved " << name << endl;
    mlist.clear(); 
}

void BMList::remove(int pass)
{
    char name[256];
    sprintf(name, MLISTSTR, mypid, pass, num);
    ::remove(name);
    cout << "removing " << name << endl;
}

void BMList::load(int pass)
{
    mlist.clear(); 

    char name[256];
    sprintf(name, MLISTSTR, mypid, pass, num);
    int fd = open(name, O_RDONLY);
    assert(fd >= 0);

    size_t num = size;

    DiskBlk diskblk;
    while (num--)
    {
        ssize_t ret = read(fd, &diskblk, sizeof(diskblk));
        assert(ret == sizeof(diskblk));
        mlist.push_back(diskblk);
    }
    close(fd);
    cout << "loaded " << name << ":" << mlist.size() 
        << endl;
}


void BMList::print() const
{
    std::cout << "mylist=" << num << ":size=" << mlist.size() << ":" ;
    MConstIter it;
    for (it=mlist.begin(); it!=mlist.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void BMList::check() const
{
    MConstIter it;
    bool first = true;
    MConstIter prev;
    int pos = 0;
    for (it=mlist.begin(); it!=mlist.end(); ++it, pos++)
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

void merge_2way(BMList& l1, BMList& l2, int pass)
{
    l1.load(pass);
    l2.load(pass);
    l1.merge(l2);
    l1.save(pass + 1);
    l1.remove(pass);
    l2.remove(pass);

/*
    merge cacheblocks in RAM
    then read both files 2MB at a time
    and create new file (maybe multiple)
*/
}


void mmerge(list<BMList*>& inList, list<BMList*>& outList, int pass)
{
    int pos = 0;
    while (inList.size() >= 2)
    {
        BMList* list1 = inList.front();
        inList.pop_front();
        BMList* list2 = inList.front();
        inList.pop_front();
        merge_2way(*list1, *list2, pass);
        cout << "merging " << pos << " with next " << endl;
        outList.push_back(list1);
        delete list2;
        //outList.push_back(list2);
        pos +=2;
    }
    if (inList.size())
    {
        BMList* list = inList.front(); 
        list->rename(pass);
        inList.pop_front();
        outList.push_back(list);
    }
    cout << "PASS=" << pass 
        << ":inlist=" <<  inList.size() 
        << ":outlist=" << outList.size() << endl;
    cout << "=============================" << endl;
}


/*

Make it threaded

*/

int NUM = 753;

int main (int argc, char* argv[])
{
    
    if (argc > 1)
    {
        NUM = atoi(argv[1]);
    }
    mypid = getpid();

    BMList *mylist[NUM];

    srand(76);
    for (int i = 0; i < NUM; i++)
    {
        mylist[i] = new BMList(i);
        for (int j = 0; j < 10; j++)
        {
            int d = rand();
            int o = j;
            DiskBlk newblk(d, o);
            mylist[i]->mlist.push_back (newblk);
        }
        mylist[i]->print();
    }
    cout << "========SORTING===============" << endl;

    list<BMList*> inList;
    list<BMList*> outList;
    for (int i = 0; i < NUM; i++)
    {
        mylist[i]->sort();
        mylist[i]->save(0);
        inList.push_back(mylist[i]);
    }
    cout << "========MERGE===============" << endl;

    int pass = 0;
    while (inList.size() > 1)
    {
        mmerge(inList, outList, pass++);
        inList = outList;
        outList.clear();
    }

    BMList* mlist = inList.front();
    mlist->load(pass);
    mlist->check();
    mlist->print();

    return 0;
}
