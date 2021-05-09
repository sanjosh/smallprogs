
/*
Question 2. There is a string whose characters can only be either ‘a’, ‘b’ or ‘_’ 

(there can be only one ‘_’ in the string). 

At each step, we can modify the string as follows:

1. ‘_’ can be swapped with its adjacent character, example “a_ba” can be changed to either “_aba” or “ab_a”.

2. Two characters adjacent to ‘_’ (both on the same side of ‘_’) can be reversed along with the ‘_’ 
if both characters are different, 
example, “aa_ba” can be changed to “aaab_” but not to “_aaba” because both characters are ‘a’.

You are given two strings, the initial state and the final state (lengths will be same), 

you have to output the minimum number of steps required to change the string in initial state 
to the string in the final state.

example:

input: a_b ab_
output: 1

input: abaa_a b_aaaa
output: 4

reason for example 2:- abaa_a -> aba_aa -> ab_aaa -> _baaaa -> b_aaaa

Hint: Use Breadth first search

https://stackoverflow.com/questions/26347134/transform-one-string-to-another-string-using-bfs

-----------

my notes:
modified edit distance
https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance

move _ towards its final location (only one in string)

reverse char if the final order is different

find distance between final and original underscore

two transformations
1. swap underscore (either one left, one right)
2. reverse triple (moves underscore two pos and reverse char)


transformString(string& actual)
{
    if (actual == desired) 
        return 0;
    diff = under_pos(actual) - under_pos(desired);
    if (diff != 0)
    {
        swapUnderpos(actual, -1 if diff < 0 else + 1)
        x = 1 + transformString(actual);
    }
    if (differentCharNearUnderscore()
    {
        reverseTriple(actual);
        y = 1 + transformString(actual);
    }
    return min( x  + y)
}


*/

#include <string>
#include <iostream>
#include <cassert>
#include <set>
#include <climits>

using namespace std;

std::string desired = "b_aaaa";

std::set<string> visited;

int posOfUnderscore(const string& s)
{
    for (int idx = 0; idx < s.size(); idx ++)
    {
        if (s[idx] == '_') return idx;
    }
    cout << s << endl;
    assert("cannot happen" == 0);
}

bool isDistinct(const string& s, int direction, int pos)
{
    if ((pos + direction >= 0) && (pos + direction + 1 < s.size())) {
        return s[pos + direction] != s[pos + (2 * direction)];
    }
    return false;
}

string reverseTriple(string s, int direction, int pos)
{
    char tmp = s[pos];
    s[pos] = s[pos + direction + 1];
    s[pos + direction + 1] = tmp;
    posOfUnderscore(s);
    return s;
}

string SwapUnderscore(string actual, int direction, int pos)
{
    char tmp = actual[pos];
    actual[pos] = actual[pos + direction];
    actual[pos + direction] = tmp;
    posOfUnderscore(actual);
    return actual;
}

int DFSTransformString(string actual)
{
    visited.insert(actual);

    if (actual == desired)
    {
        return 0;
    }

    int actualPos = posOfUnderscore(actual);
    int desiredPos = posOfUnderscore(desired);
    int x = INT_MAX;
    int y = INT_MAX;
    int p = INT_MAX;
    int q = INT_MAX;
    if (actualPos != desiredPos) 
    {
        if (actualPos - 1 >= 0) {
            string next = SwapUnderscore(actual, -1, actualPos);
            if (visited.find(next) == visited.end()) {
                x = 1 + DFSTransformString(next);
            }
        }
        if (actualPos + 1 < actual.size()) {
            string next = SwapUnderscore(actual, 1, actualPos);
            if (visited.find(next) == visited.end()) {
                y = 1 + DFSTransformString(next);
            }
        }
    }
    if (isDistinct(actual, 1, actualPos))
    {
        // can have infinite loop in reverse triple transformation
        // add visited
            string next = reverseTriple(actual, 1, actualPos);
            if (visited.find(next) == visited.end()) {
                p = 1 + DFSTransformString(next);
            }
    }
    if (isDistinct(actual, -1, actualPos))
    {
            string next = reverseTriple(actual, -1, actualPos);
            if (visited.find(next) == visited.end()) {
                q = 1 + DFSTransformString(next);
            }
    }
    return std::min(std::min(p, q), std::min(x, y));
}


int main()
{
    string actual = "abaa_a";
    desired = "b_aaaa";

    int x = DFSTransformString(actual);
    for (auto x : visited) {
        cout << x << endl;
    }
    cout << x << endl;
}
