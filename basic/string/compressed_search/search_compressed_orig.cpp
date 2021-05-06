/*

Question 1. There is a compressed string eg. ”ab2c3”, the string has lowercase characters and numbers. We can uncompress the given string as follows: whenever we get a number “n” in the string, the portion of the string before the number will repeat “n” times. So in the above example, we get a 2, so string will become “ababc3”, now we get a 3, so final string will be “ababcababcababc”.

Given a compressed string and a number k, you have to output the k’th character in the uncompressed string.

1 <= length of string <= 1500
1 <= n <= 1000
1 <= k < 2^31
example:
input: ab2c3 10
output: c

http://www.geeksforgeeks.org/directi-interview-set-6-campus-internship/

SOLUTION : 

From the compressed pattern, create a linked list of nodes 

For example, if input = "ab2c3d4", then we create 3 nodes which are in reverse order of parsing

HEAD OF LIST = ("d", totalLen=5*3 + 1, numRepeats=4) --> ("c", totalLen=2*2 + 1, numRepeats=3) --> ("ab", totalLen=2, numRepeats=2) 

each Node stores information as follows:

struct Node
{
    string pattern;
    size_t totalLen = (prevNode.numRepeats * prevNode.totalLen) + pattern.size()
    size_t numRepeats = number of times pattern repeats from here
}

Then search modulo the position in this linked list

*/

#include <string>
#include <list>
#include <iostream>
#include <ctype.h>
#include <cassert>
#include <cstdlib>

using namespace std;

struct CompressedPattern
{
    struct Node
    {
        string pattern;
        size_t totalLen;  // total length of pattern seen till now, including previous nodes
        size_t numRepeats; // number of times total pattern repeats
    };

    list<Node> patList; // stores the total compressed pattern

    size_t totalStringLen() const
    {
        if (patList.size())
        {
            list<Node>::const_iterator iter = patList.begin();
            return iter->totalLen * iter->numRepeats;
        }
        return 0;
    }

    void printAllNodes(ostream& ostr) const
    {
        if (patList.size())
        {
            list<Node>::const_iterator iter = patList.begin();
     
            do
            {
                ostr << "string=" << iter->pattern << ":totalLen=" << iter->totalLen << ":repeats=" << iter->numRepeats << endl;
            } while (++iter != patList.end());
        }
    }

    int setString(const string& compressedString)
    {
        string curPattern;
        size_t prevSize = 0;

        for (size_t i = 0; i < compressedString.size(); i++)
        {
            char c = compressedString[i];
            if (isalpha(c))
            {
                curPattern += c; // add to the current pattern string
            }
            else if (isdigit(c))
            {
                Node newN;

                newN.numRepeats = c - '0'; // only 1 digit specification currently supported
                // assuming numRepeats is not specified as '0'

                newN.totalLen = prevSize + curPattern.size();
                newN.pattern = curPattern;

                patList.push_front(newN);  // new node goes to the front of the list (not back)
                // this helps to reduce the search position by modulo the totalLen

                prevSize = newN.totalLen * newN.numRepeats; // retain for use in next node

                curPattern.clear();
            }
            else 
            {
                cerr << "parse error at position=" << i << endl;
                return -1;
            }
        }
        return 0;
    }

    char getCharAtPos(size_t position) const
    {
        if (position > totalStringLen())
        {
            cerr << "Position=" << position << " is out of range of string of size=" << totalStringLen() << endl;
            return '0';
        }

        list<Node>::const_iterator iter;
        
        for (iter = patList.begin(); iter != patList.end(); ++iter)
        {
            const Node& curN = *iter;

            if (position >= curN.totalLen)  
            {
                position %= curN.totalLen; // reduce position modulo totalLen
            }

            if (curN.totalLen != curN.pattern.size()) // this is not the last node
            {
                // check if position falls within this part of the string
                if (position >= curN.totalLen - curN.pattern.size())
                {
                    // decrement the position by the rest of the string
                    position -= (curN.totalLen - curN.pattern.size());
                    return curN.pattern[position];
                }
            }
            else
            {
                // this is the last node
                assert(position < curN.pattern.size());
                return curN.pattern[position];
            }
        }
        assert("should not come here" == 0);
    }
};

int main(int argc, char** argv)
{
    CompressedPattern p;

    if (argc == 1) 
    {
        cerr << "first argument missing.  input the compressed string " << endl;
        exit(1);
    }

    p.setString(string(argv[1]));

    // print the nodes which store compressed info
    // p.printAllNodes(cout);

    // search for each position possible
    for (int i = 0; i < p.totalStringLen(); i++)
    {
        cout << p.getCharAtPos(i) << " ";
    }
    cout << endl;
}
