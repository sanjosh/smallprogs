

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

#define NUM 16

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

void mylist_print(MList mylist[], int i)
{
    MIter it;
    std::cout << "mylist=" << i << ":size=" << mylist[i].size() << ":" ;
    for (it=mylist[i].begin(); it!=mylist[i].end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void mylist_assert(MList mylist[], int i)
{
    MIter it;
    bool first = true;
    MIter prev;
    int pos = 0;
    for (it=mylist[i].begin(); it!=mylist[i].end(); ++it, pos++)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            if (*it < *prev)
            {
                cout << "FAILED list=" << i     
                    << ":pos=" << pos 
                    << ":me=" << *it
                    << ":prev=" << *prev
                    << endl;
                mylist_print(mylist, i);
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

void mmerge(MList mylist[], int off, int len, int incr)
{
    if (incr > 1)
    {
        mmerge(mylist, off, len/2, incr/2);
        mmerge(mylist, off+incr, len/2, incr/2);
    }
    for (int i = off; i < off + len; i+=2*incr)
    {
         mylist[i].merge(mylist[i+incr]);
         cout << "merging list " << i << " with " << i+incr << endl;
    }
}

/*
Make it iterative

Make it threaded

Make it work for non-powers of two
    0-1, 2-3, 4-5, 6-7, 8-9
    0-2, 4-6, 8
    0-4

Make it read from files
*/

int main ()
{
    MList mylist[NUM];

    srand(76);
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
        mylist_print(mylist, i);
    }
    cout << "========SORTING===============" << endl;

    for (int i = 0; i < NUM; i++)
    {
        mylist[i].sort();
    }
    cout << "========MERGE===============" << endl;

    mmerge(mylist, 0, NUM, NUM/2);

    mylist_assert(mylist, 0);
    mylist_print(mylist, 0);

    return 0;
}
