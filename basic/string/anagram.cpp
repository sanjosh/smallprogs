
/*
 facebook-interview-questions @ careercup
0
of 0 votes
28
Answers

Given an array of words, write a method that determines whether there are any words in this array that are anagrams of each other.

Sample #1: @[@"bag", @"bat", @"tab"]; // output TRUE

Sample #2: @[@"gab", @"bat", @"laf"]; // output FALSE

Build hash func ; bit shifted

compute func f(word) ; 

X[0] = (w[0] + w[n-1])/2  - this is for palindromes
X[n-1] = (w[0] - w[n-1])/2 

compute func 

poly (x-w1)(x-w2)(x-w3) may have unique coeffiencets w1.w2.w3

are digits drawn from finite set ? - use bitmap


*/

#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define TONUM(ch) (ch - 'A')

uint64_t ElemSymmetricPoly(const string& s, int k)
{
    const size_t size = s.size();    
    size_t n = s.size();    
    if (n==k) n = 1;

    uint64_t sum = 0;

    for (size_t i = 0; i < n; i++)
    {
        uint64_t prod = TONUM(s[i]);
        for (size_t j = 1; j < k; j++)
        {
            prod *= TONUM(s[(i+j) % size]);
        }
        cout << "adding prod=" << prod << " to sum=" << sum << endl;
        sum += prod;
    }
    cout << "string=" << s << ":sum=" << sum << endl;
    return sum;
}

int main(int argc, char* argv[])
{
    if (argc != 3) exit(1);

    string input(argv[1]);
    string rearr(argv[2]);

    size_t k = 0;
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;

    for (size_t k = 1; k < input.size(); k ++)
    {
        sum1 = ElemSymmetricPoly(input, k);
        sum2 = ElemSymmetricPoly(rearr, k);

        if (sum1 != sum2)
        {
            cout << "fail on " << k << "-th symmetric poly " << endl;
            break;
        } 
    }
}
