
http://www.geeksforgeeks.org/merging-intervals/

Given a set of time intervals in any order, merge all overlapping intervals into one and output the result which should have only mutually exclusive intervals. Let the intervals be represented as pairs of integers for simplicity.
For example, let the given set of intervals be {{1,3}, {2,4}, {5,7}, {6,8} }. The intervals {1,3} and {2,4} overlap with each other, so they should be merged and become {1, 4}. Similarly {5, 7} and {6, 8} should be merged and become {5, 8}

Write a function which produces the set of merged intervals for the given set of intervals.

A simple approach is to start from the first interval and compare it with all other intervals for overlapping, if it overlaps with any other interval, then remove the other interval from list and merge the other into the first interval. Repeat the same steps for remaining intervals after first. This approach cannot be implemented in better than O(n^2) time.

An efficient approach is to first sort the intervals according to starting time. Once we have the sorted intervals, we can combine all intervals in a linear traversal. The idea is, in sorted array of intervals, if interval[i] doesn’t overlap with interval[i-1], then interval[i+1] cannot overlap with interval[i-1] because starting time of interval[i+1] must be greater than or equal to interval[i]. Following is the detailed step by step algorithm.

1. Sort the intervals based on increasing order of starting time.
2. Push the first interval on to a stack.
3. For each interval do the following
……..a. If the current interval does not overlap with the stack top, push it.
……..b. If the current interval overlaps with stack top and ending time of current interval is more than that of stack top, update stack top with the ending time of current interval.
4. At the end stack contains the merged intervals.

Below is a C++ implementation of the above approach.
// A C++ program for merging overlapping intervals
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
 
// An interval has start time and end time
struct Interval
{
    int start;
    int end;
};
 
// Compares two intervals according to their staring time.
// This is needed for sorting the intervals using library
// function std::sort(). See http://goo.gl/iGspV
bool compareInterval(Interval i1, Interval i2)
{  return (i1.start < i2.start)? true: false; }
 
// The main function that takes a set of intervals, merges
// overlapping intervals and prints the result
void mergeIntervals(vector<Interval>& intervals)
{
    // Test if the given set has at least one interval
    if (intervals.size() <= 0)
        return;
 
    // Create an empty stack of intervals
    stack<Interval> s;
 
    // sort the intervals based on start time
    sort(intervals.begin(), intervals.end(), compareInterval);
 
    // push the first interval to stack
    s.push(intervals[0]);
 
    // Start from the next interval and merge if necessary
    for (int i = 1 ; i < intervals.size(); i++)
    {
        // get interval from stack top
        Interval top = s.top();
 
        // if current interval is not overlapping with stack top,
        // push it to the stack
        if (top.end < intervals[i].start)
        {
            s.push( intervals[i] );
        }
        // Otherwise update the ending time of top if ending of current
        // interval is more
        else if (top.end < intervals[i].end)
        {
            top.end = intervals[i].end;
            s.pop();
            s.push(top);
        }
    }
 
    // Print contents of stack
    cout << "\n The Merged Intervals are: ";
    while (!s.empty())
    {
        Interval t = s.top();
        cout << "[" << t.start << "," << t.end << "]" << " ";
        s.pop();
    }
 
    return;
}
 
// Functions to run test cases
void TestCase1()
{
    // Create a set of intervals
    Interval intvls[] = { {6,8}, {1,9}, {2,4}, {4,7} };
    vector<Interval> intervals(intvls, intvls+4);
 
    // Merge overlapping inervals and print result
    mergeIntervals(intervals);
}
void TestCase2()
{
    // Create a set of intervals
    Interval intvls[] = { {6,8},{1,3},{2,4},{4,7} };
    vector<Interval> intervals(intvls, intvls+4);
 
    // Merge overlapping inervals and print result
    mergeIntervals(intervals);
}
void TestCase3()
{
    // Create a set of intervals
    Interval intvls[] = { {1,3},{7,9},{4,6},{10,13} };
    vector<Interval> intervals(intvls, intvls+4);
 
    // Merge overlapping inervals and print result
    mergeIntervals(intervals);
}
 
// Driver program to test above functions
int main()
{
    TestCase1();
    TestCase2();
    TestCase3();
    return 0;
}

Output:


 The Merged Intervals are: [1,9]
 The Merged Intervals are: [1,8]
 The Merged Intervals are: [10,13] [7,9] [4,6] [1,3]

Time complexity of the method is O(nLogn) which is for sorting. Once the array of intervals is sorted, merging takes linear time.
