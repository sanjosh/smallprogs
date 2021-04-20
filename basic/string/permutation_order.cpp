
// given n, find next permutation

/*
Lehmer code
Rothe diagram
inversion table
*/

#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>

//  023 < 032 < 203 < 230 < 302 < 320
//  223 < 232 < 322 
//  123 < 132 < 213 < 231 < 312 < 321

//  sorted < t(23) < t(12) < t(23) < t(13)

using namespace std;

int todigit(char c)
{
    return c - '0';
}

#if YES
#define DBG cout
#else
#define DBG ostream(0).flush()
#endif

// TODO next-lowest

char* next_highest(char* number)
{
    // start from right, find first plae where left digit is less than right digit    
    // 43215876 : 5
    // find smallest digit from right which is larger than this number 
    // "6"
    // swap both chars
    // 4321+6+78+5
    // sort the rightmost digits
    // 4321+6+578

    int len = strlen(number);

    int frompos = -1;
    for (int i = len-2; i >= 0; i --)
    {
        if (todigit(number[i]) < todigit(number[i+1]))
        {
            frompos = i;
            break;
        }
    }
    if (frompos == -1) return NULL;

    int val_at_from = todigit(number[frompos]);
    DBG << "found pos=" << frompos << " val=" << val_at_from << endl; 

    int max = 10;
    int pos_of_max = -1;
    for (int i = len -1 ; i > frompos; i--)
    {
        int val = todigit(number[i]);
        if ((val >  val_at_from) && (val < max))
        {
            max = val; 
            pos_of_max = i;
        }
    }

    DBG << "swapping with " << max << " at pos=" << pos_of_max << endl;
    char* newnum = strdup(number);
    char tmp = newnum[pos_of_max];
    newnum[pos_of_max] = newnum[frompos];
    newnum[frompos] = tmp;

    DBG << "newnum= " << newnum << endl;

    list<int> alist;
    for (int i = frompos + 1; i < len; i++)
    {
        alist.push_back(todigit(newnum[i]));
        DBG << "pushing " << i << endl;
    }
    alist.sort();

    list<int>::iterator iter;
    int curpos = frompos + 1;
    for (iter = alist.begin(); iter != alist.end(); ++iter)
    {
        DBG << "inserting " << *iter << " at pos=" << curpos << endl;
        newnum[curpos] = '0' + *iter;
        curpos ++;
    }

    return newnum;
}

int main(int argc, char* argv[])
{
    char* ans = argv[1];
    do
    {
        ans = next_highest(ans);
        if (ans)
        {
            cout << "RES is " << ans << endl;
        }
    } while (ans);
}


