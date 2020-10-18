
/* given set of intervals, find max subset in which none overlaps
*/

#include <map>
#include <iostream>
#include <list>
using namespace std;

// start, end
struct Interval
{
    int start;
    int end;
    
    Interval(int s, int e) { start = s; end = e;} 

    bool intersect(const Interval& other) const
    {
        if ((other.start > end) || (start > other.end)) return false;
        return true;
    }

    friend ostream& operator << (ostream& ostr, const Interval& me)
    {
        ostr << me.start << ":" << me.end;
        return ostr;
    }
};

typedef multimap<int, Interval> IntervalSet;
IntervalSet set;

int findNext(const Interval& cur, IntervalSet::const_iterator index, list<Interval>& path)
{
    if (index == set.end()) return 1;

    IntervalSet::const_iterator iter;

    int maxdepth = 1;
    int curdepth = 0;

    list<Interval> childpath;

    for (iter = index; iter != set.end(); ++iter)
    {
        if (cur.intersect(iter->second) == false)
        {
            list<Interval> pospath;
            curdepth = findNext(iter->second, iter, pospath) + 1;
            if (curdepth > maxdepth)
            {
                maxdepth = curdepth;
                childpath = pospath;
            }
        }
    }

    path.push_back(cur);
    path.insert(path.end(), childpath.begin(), childpath.end());
    //cout << "returning node=" << cur << ":depth=" << maxdepth << endl;

    return maxdepth;
}

int main(int argc, char* argv[])
{
    Interval a[] = 
    {
        {3, 10},
        {4, 11},
        {15, 27},
        {12, 30},
        {15, 40},
        {32, 42},
        {44, 52},
        {45, 60},
        {55, 70},
    };

    for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++)
    {
        set.insert(make_pair(a[i].start, a[i]));
    }

    IntervalSet::const_iterator iter = set.begin();

    iter ++;
    iter ++;
    iter ++;

    for (int i = 0; i < 3; i++)
    {
        list<Interval> path;
        int d = findNext(a[i], iter, path);
        cout << d << endl;
     
        list<Interval>::const_iterator listIter;
        for (listIter =path.begin(); listIter != path.end(); ++listIter)
        {
            cout << *listIter << endl;
        }
        cout << "----------" << endl;
    }
}
