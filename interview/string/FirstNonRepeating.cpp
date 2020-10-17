/*

Find first non repeating character in stream of char

*/
#include <list>
#include <string.h>
#include <map>
#include <iostream>

using namespace std;

typedef list<char> LIST;

struct Counter
{
    int count;
    LIST::iterator iter;

    Counter() { count = 0; }
};

typedef map<char, Counter> MAP;

int main(int argc, char* argv[])
{
    if (argc != 2) exit(1);

    LIST list;
    MAP map;

    char* input = argv[1];
    for (int i = 0; i < strlen(input); i++)
    {
        char c = input[i];

        MAP::iterator iter = map.find(c);
        
        if (iter == map.end())
        {
            list.push_back(c);

            Counter ctr;
            ctr.count = 1; 
            ctr.iter = (++list.rbegin()).base();
            // store the iter in the map so we can erase faster from list later

            map.insert(make_pair(c, ctr));
        }
        else
        {
            Counter& ctr = iter->second;

            if (ctr.count == 1)
            {
                list.erase(ctr.iter);
                // but do not erase from the map
            }

            ctr.count ++;
        }
    }

    if (list.size())
    {
        cout << "first = " << list.front() << endl;
    }
    else
    {
        cout << "all repeat " << endl;
    }
}
