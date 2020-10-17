

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

// comparison, not case sensitive.
bool compare_nocase (const std::string& first, const std::string& second)
{
  unsigned int i=0;
  while ( (i<first.length()) && (i<second.length()) )
  {
    if (tolower(first[i])<tolower(second[i])) return true;
    else if (tolower(first[i])>tolower(second[i])) return false;
    ++i;
  }
  return ( first.length() < second.length() );
}

#define NUM 8

// len=16 - m 0,8
// len=8 - m 0,4 & m 8,12
// len=4 - m 0,2 & 4,6 & 8,10 & 12,14
// len=2 - m 0,1  2,3 4,5, 6,7 ... 15,16
using namespace std;

void mylist_print(std::list<std::string> mylist[], int i)
{
    std::list<std::string>::iterator it;
    std::cout << "mylist=" << i << "size=" << mylist[i].size() << ":" ;
    for (it=mylist[i].begin(); it!=mylist[i].end(); ++it)
    {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

void split(std::list<std::string> mylist[], int off, int len, int incr)
{
    //cout << off << " to " << off + len << " incr of " << incr << endl;
    if (incr > 1)
    {
        split(mylist, off, len/2, incr/2);
        split(mylist, off+incr, len/2, incr/2);
    }
    for (int i = off; i < off + len; i+=2*incr)
    {
        cout << "merge " << i << ":" << i+incr << endl;
        mylist[i].merge(mylist[i+incr], compare_nocase);
        mylist_print(mylist, i);
    }
}

char name[10];

int main ()
{
   std::list<std::string> mylist[NUM];

  for (int i = 0; i < NUM; i++)
  {
    sprintf(name, "%d", i+4);
    name[3] = '\0';
    std::string str (name, 4);
    mylist[i].push_back ("two" + str);
    mylist[i].push_back ("Three" + str);
    mylist[i].push_back ("one" + str);
     mylist_print(mylist, i);
  }

  for (int i = 0; i < NUM; i++)
  {
     mylist[i].sort(compare_nocase);
     mylist_print(mylist, i);
  }

  split(mylist, 0, NUM, NUM/2);



  return 0;
}
