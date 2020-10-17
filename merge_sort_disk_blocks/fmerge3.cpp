

/*
list::merge(list& source)
list::merge(list& source, CompFunc op)

where op(elem, sourceElem)
*/

// list::sort
#include <iostream>
#include <list>
#include <string>
#include <cctype>

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NUM 43

using namespace std;

struct diskblk
{
    int a;
    int file;
    int offset;

    public:
    diskblk() { a = 0;}
    diskblk(int in, int f, int o) { a = in; file=f; offset=o;}
    diskblk(const diskblk& other) { a = other.a; file=other.file; offset=other.offset;}
    int& operator *() {return a;}
    diskblk& operator += (const diskblk& val) { a+=val.a; return *this;}

    bool operator < (const diskblk& other) const
    {
        return (a < other.a);
    }
    bool operator > (const diskblk& other) const
    {
        return other.operator < (*this);
    }
    bool operator <= (const diskblk& other) const
    {
        return (a <= other.a);
    }

    friend ostream& operator <<(ostream& ostr, const diskblk& me)
    {
        ostr << me.a; return ostr;
    }
};


typedef std::list<diskblk> MList;
typedef MList::iterator MIter;

void mlist_print(MList& mlist)
{
    MIter it;
    std::cout << "mylist" << ":size=" << mlist.size() << ":" ;
    for (it=mlist.begin(); it!=mlist.end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void mlist_assert(MList& mlist)
{
    MIter it;
    bool first = true;
    MIter prev;
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
                mlist_print(mlist);
                assert(0);
            }
        }
        prev = it;
    }
}


template <class ForwardIterator, class T>
void iota(ForwardIterator first, ForwardIterator last, T value, T increment)
{
    while (first != last) 
    {
        *first ++ = value; 
        value += increment;
    }
}

void mmerge2(list<MList>& inList, list<MList>& outList)
{
    int pos = 0;
    while (inList.size() >= 2)
    {
        MList list1 = inList.front();
        inList.pop_front();
        MList list2 = inList.front();
        inList.pop_front();
        list1.merge(list2);
        cout << "merging " << pos << " with next " << endl;
        //mlist_print(list1);
        outList.push_back(list1);
        pos +=2;
    }
    if (inList.size())
    {
        MList list = inList.front(); 
        inList.pop_front();
        outList.push_back(list);
    }
    cout << "PASS:" << inList.size() << ":" << outList.size() << endl;
}

/*

Make it threaded

Make it read from files
*/

int main ()
{
    MList mylist[NUM];

    srand(77);
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int d = rand();
            int f = j;
            int o = f + 3;
            diskblk newblk(d, f, o);
            mylist[i].push_back (newblk);
        }
        mlist_print(mylist[i]);
    }
    cout << "========SORTING===============" << endl;

    list<MList> inList;
    list<MList> outList;
    for (int i = 0; i < NUM; i++)
    {
        mylist[i].sort();
        inList.push_back(mylist[i]);
    }
    cout << "========MERGE===============" << endl;

    //mmerge(mylist, 0, NUM, NUM/2);

    while (inList.size() > 1)
    {
        mmerge2(inList, outList);
        inList = outList;
        outList.clear();
    }

    MList& mlist = inList.front();
    mlist_assert(mlist);
    mlist_print(mlist);

    return 0;
}
