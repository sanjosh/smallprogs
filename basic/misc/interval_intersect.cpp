#include <utility>
#include <iostream>
using namespace std;

typedef std::pair<int, int> Interval;

bool func(const Interval& a, const Interval& b)
{
    return (a.first < b.second) && (b.first < a.second);
}

int main()
{
    Interval a(3, 6);
    Interval b(1, 7);
    Interval c(5, 7);
    Interval d(1, 4);

    cout << "overlap " << func(a, b) << endl;
    cout << "intersect " << func(a, c) << endl;
    cout << "intersect " << func(a, d) << endl;
    cout << "no overlap " << func(c, d) << endl;
}
