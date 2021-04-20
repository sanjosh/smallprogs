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

For example, if input = "ab2c3d4", then we create 3 entries 

VECTOR = 
("ab", lenTillHere=2) 
("c", lenTillHere=2*2 + 1) 
("d", lenTillHere=5*3 + 1) 

each Node stores information as follows:

struct Node
{
    string pattern;
    size_t lenTillHere = (prevNode.numRepeats * prevNode.lenTillHere) + pattern.size()
}

Then search from the last to first to find position modulo lenTillHere

*/

#include <string>
#include <vector>
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
        size_t lenTillHere;  // length of pattern seen till now, including previous nodes
    };

    vector<Node> patternVector; // stores the total compressed pattern
    size_t totalUncompressedSize; // length of uncompressed string

    CompressedPattern()
    {
        totalUncompressedSize = 0;
    }

    size_t uncompressedSize() const 
    {
        return totalUncompressedSize;
    }

    void printAllNodes(ostream& ostr) const
    {
        for (size_t index = 0; index < patternVector.size(); index ++)
        {
            const Node &node = patternVector[index];
            ostr << "string=" << node.pattern << ":lenTillHere=" << node.lenTillHere << endl;
        } 
    }

    void addNode(size_t prevSize, const string& curPattern)
    {
        Node newN;
        newN.lenTillHere = prevSize + curPattern.size();
        newN.pattern = curPattern;

        patternVector.push_back(newN);  
        // add new entry to vector
    }

    int setString(const string& compressedString)
    {
        string curPattern;
        size_t prevSize = 0;
        size_t curNumRepeats = 0;

        for (size_t i = 0; i < compressedString.size(); i++)
        {
            char c = compressedString[i];

            if (isalpha(c))
            {
                if (curNumRepeats) 
                {
                    // new pattern has started; record previous pattern
                    addNode(prevSize, curPattern);
    
                    prevSize = (prevSize + curPattern.size()) * curNumRepeats; 
                    // retain prevSize for use in next node

                    curPattern.clear();
                    curNumRepeats = 0;
                }
    
                curPattern += c; // add to the current pattern string
            }
            else if (isdigit(c))
            {
                curNumRepeats = (curNumRepeats * 10) + (c - '0'); 
            }
            else 
            {
                cerr << "parse error at position=" << i << endl;
                return -1;
            }
        }

        // if string has ended, add whatever was recorded to the last entry
        if (curNumRepeats)
        {
            addNode(prevSize, curPattern);
            prevSize = (prevSize + curPattern.size()) * curNumRepeats; 
        }

        totalUncompressedSize = prevSize;

        return 0;
    }

    char getCharAtPos(size_t position) const
    {
        if (position > uncompressedSize())
        {
            cerr << "Position=" << position << " is out of range of string of size=" << uncompressedSize() << endl;
            return '0';
        }

        for (size_t index = patternVector.size() - 1 ; index >= 0; --index)
        {
            const Node& curN = patternVector[index];

            position %= curN.lenTillHere; // reduce position modulo lenTillHere

            ssize_t relativePos = position + curN.pattern.size() - curN.lenTillHere;

            // return char if the position falls in current node
            if (relativePos >= 0)
            {
                assert(relativePos < curN.pattern.size());
                return curN.pattern[relativePos];
            }
        }
        assert("should not come here" == 0);
    }
};

int main(int argc, char** argv)
{
    while (1)
    {
        CompressedPattern p;
        string compressedString;

        cin >> compressedString;

        if (p.setString(compressedString) != 0)
        {
            cerr << "failed" << endl;
            exit(1);
        }

        // print the nodes which store compressed info
        p.printAllNodes(cout);

        // search for each possible position in uncompressed string
        for (size_t index = 0; index < p.uncompressedSize(); index++)
        {
            cout << p.getCharAtPos(index) << " ";
        }
        cout << endl;
    }
}
