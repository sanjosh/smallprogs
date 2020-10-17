
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

#include <stdint.h>
#include <stdlib.h>

using namespace std;

class WriteCacheEntry
{
    public:
    uint32_t diskOffset; 
    uint32_t cacheBlockId; 

    friend ostream& operator << (ostream& ostr, const WriteCacheEntry& me)
    {
        ostr << me.cacheBlockId << ":" << me.diskOffset << endl;
        return ostr;
    }
};

class WCSortOp
{
    public:
    bool operator() (const WriteCacheEntry& lhs, const WriteCacheEntry rhs) const
    {
        return (lhs.cacheBlockId < rhs.cacheBlockId);
    }
};

typedef set<WriteCacheEntry, WCSortOp> WCSet;
typedef WCSet::iterator WCIter;

main()
{
    WCSet coll;
    srand(73);
    
    WriteCacheEntry a;
    for (int i = 0; i < 100; i++)
    {
        a.cacheBlockId = 1;
        a.diskOffset = i;
        std::pair<WCIter,bool> pos = coll.insert(a);
        if (!pos.second)
        {
            WriteCacheEntry* e = *pos.first;
            cout << e << endl;
            //e->diskOffset = i * 2;
        }
    }

    WCIter iter;
    for (iter = coll.begin(); iter != coll.end(); ++iter)
    {
        cout << *iter;
    }
}
