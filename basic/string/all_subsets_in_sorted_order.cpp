
/*
Question 2: Given a string. Print all Possible permutations of different lengths in sorted order. 

for "abc"

a
ab
ac
abc
b
bc
c
*/

//sort the string - O(n.logn)
//
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    string str(argv[1]);

    // O(n logn)
    std::sort(str.begin(), str.end());

    //O(n^2)
    size_t len = str.size();
    for (size_t start = 0; start < len; start++)
    {
        for (size_t total = 1; total <= len - start; total ++) 
        {
            cout << str.substr(start, total) << endl;
        }
    }
}
