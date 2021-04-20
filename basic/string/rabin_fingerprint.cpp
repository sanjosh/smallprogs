/*

A(t) = 
P(t) = x^4 + x^3 + 1 is irred over Z2

text t = t[i...i+M-1]
number x(i) = t[i] * b^M-1 + t[i+1] * b^M-2 + ... + t[i+M-1]
numb x(i+1) = t[i+1] * b^M-1 + t[i+2] * b^M-2 + ... + t[i+M]

*/

/*

Given string A = (a1...am)
define poly A(t) = a1.t^m-1 + .. + am
Let P(t) be irred poly of degree k in Z2
Fingerprint f(A) = A(t) mod P(t)

Probab of 2 strings mapping to same fingerprint : f(A) = f(B)/

Q = Product 

irred poly is related to number of irred poly

Fingerprint is distributive over addition in Z2 : f(A+B) =f(A) + f(B)
concatenation : f(concat(A, B)) = f(concat(f(A), B))

*/

/*
From rsync thesis of Trigdell

k= off, L=block len, M+2^16

r1(k, L) = Sum(i=0, L-1) ( a_i+k) mod M
r2(k, L) = Sum(i=0, L-1) ( (L-i) a_i+k) mod M
r(k, L) = r1(k, L) + M.r2(k, L)

r1(k+1, L) = (r1(k, L) - a_k + a_k+L ) mod M
r2(k+1, L) = (r2(k, L) - L.a_k + r1(k+1,L) ) mod M
r(k+1, L) = r1(k+1, L) + M.r2(k+1, L)



*/

/*
Moving a level above the naive approach to string matching can be done by making use of the comparisons being done during each iteration and using it for the next iteration . In the brute force approach , say we compare T[a...b] with the Pattern P in an iteration and in the next iteration we compare T[a+1....b+1] . So, we are comparing the same characters again and again , which leads to in-efficiency .

The Rabin Karp Algorithm makes a better attempt in solving the above problem . Before giving the implementation we can define a few steps to easily comprehend the Algorithm implementation .

1 . Let us first define the string as a collection of numbers only , say Set Q = {0…9} from which the pattern and text are generated . Then , we will take forward the idea to characters. So, now there are 10 characters over which the set Q is defined .
2. Let p denote the decimal value of P[1....m] where m is the length of the pattern . For Example if the pattern is “32145″ the corresponding decimal value is 32,145.
Let t(s) denote the decimal value of Text txt[s+1...s+m] where s is the shift value.

3. We can compute p in time O(m) using HORNERS RULE .
p = P[m]+ 10 (P[m-1] + 10(P[m-2]+……10(P[2] + 10 P[1]….))) —-> The 10 is the number of characters

Similary when shift value is s=0 we can calculate txt[1....m] as t(0) in O(m) time .
t(1) is txt[2....m+1] which can again be calculated in O(m) time .

But, by induction we can say that ,

t (s+1) = 10 (t(s) – 10^(m-1) T[s+1]) + T[s+m+1]

This is nothing but removal of first digit and addition of the new last digit . Subtracting 10^(m-1) T[s+1] removes the higher order digit and adding T[s+m+1] brings in the appropriate lower digit.
Hence, we observe that we can calculate t(s+1) from t(s) in constant time provided we calculate t(0) in O(m) time .
We can precompute the constant 10 ^ (m-1) in O(logm) time as given in my implementation .

But, a major problem which we will face is that the decimal values may be too large leading to overflow . Hence , we compute p & t(s) values modulo a suitable prime number in O(n-m+1) .

Also, if we extend the decimal value concept to characters (the 256 possible characters ) , this actually leads up to finding the hash value of a pattern and comparing with a required pattern .
But, the matching of the hash value of t(s) with p does not necessarily imply that both the patterns are the same. Hence, if the two values are equal then we proceed further to check the equality of characters present in them . If the two hash values are equal but the characters are not the same it is called a SPURIOUS HIT .

Example of calculating t(s+1)%mod from t(s)%mod where mod denotes any prime number :

Precompute : 100000 % 97 = 9
Previous Hash : 41592 % 97 = 76
Next Hash : 15926 % 97 = ??

OBSERVATION : 15926 % 97 = (41592 % 97 – ((4 % 97) * (100000 % 97 )) ) * (10 % 97 ) + (6 %97)
= 76 – ( 4 * 9 ) * 10 + 6
= 406 % 97
= 18

The worst case complexity is again O(m(n-m+1)) which again makes it in-efficient but its best and average case is O(n+m) which makes it better than naive approach . It is extremely useful in 2d processing
So, here’s the final implementation in C++ 

Rabin Karp Fingerprint Algorithm:
The average and best case running time of the Rabin-Karp algorithm is O(n+m)
Worst-case time is O(nm).

*/
 
#include<iostream>
#include<cstring>
#include<cstdio>
#define d 256                  // The dictionary of 256 characters
using namespace std;

void search(char *txt , char *pat , int q)
{
    int m=strlen(pat);
    int n=strlen(txt);
     
    int i,j;
    int p=0;                       // hash value for pattern
    int t=0;               // hash value for text
    int h=1;                       // d^(m-1) value
     
    // Compute the value of d^(m-1) --> Pre-processing in linear time
    for(i=0;i<m-1;i++)
    {
        h=(d*h)%q;
    }
     
    // Multiply each character by its place value and obtain the hash value
    // Initial Hash values of current sliding text window and the pattern is being calculated
     
    for(i=0;i<m;i++)
    {
        p=(d*p+pat[i])%q;
        t=(d*t+txt[i])%q;
    }
     
    for(i=0;i<=n-m;i++)
    {
     
    // Check if the current sliding window of text and pattern have same hash values
     
        if(t==p)
        {
    // Check if all characters are same or it's a SPURIOUS HIT !
     
            for(j=0;j<m;j++)
            {
                if(txt[i+j]!=pat[j]) 
                {
                    break;
                }
            }
            if(j==m) cout<<"Pattern matched at index "<<i<<endl;
        }
 
// Now compute the next sliding window for the text using previous value..
 
        if(i<n-m)
        {
            t = (d*(t - txt[i]*h) + txt[i+m])%q;
     
    // We might get negative value of t, converting it to positive
     
            if(t < 0) t = (t + q);
        }
    }
}
 
int main()
{
    char a[500],b[500];
    cout<<"Enter the string"<<endl;
    gets(a);
    cout<<"Enter the sub-string you wish to search for"<<endl;
    gets(b);
    int q=7;    // Let the prime number for computation be 7
    search(a,b,q); 
    return 0;
}

