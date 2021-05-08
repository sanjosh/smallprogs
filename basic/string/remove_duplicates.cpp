#include <string>
#include <iostream>

/*

cases:
1. duplicates follow each other
1. duplicates have distance of one or more
1. some characters after last duplicate
1. no characters after last duplicate
1. all duplicates
1. no duplicates

insertPos can be different from location of previous duplicate, in case of consecutive duplicates

keep location of previous duplicate, since u have to move characters between them

keep next insert position (which can be behind prevDupLoc)

number of characters to move = [prevDupLoc + 1) to (curIndex -1)

*/

using namespace std;

int moveChar(std::string& s, int numMove, int insertLoc, int fromLoc)
{
    int count = 0;
    while (count < numMove)
    {
        s[insertLoc + count] = s[fromLoc + count];
        count ++;
    }
    return insertLoc + numMove;
}

bool isDuplicate(const string& s, char c, int loc)
{
    for (int j = 0; j < loc; j++)
        if (s[j] == c) return true;
    return false;
}

int main()
{
    int prevDupLoc = -1;
    int insertPos = -1;

    string s = "abcdxycdpqars";

    int i = 0;
    int n = s.size();

    while (i < n)
    {
        if (isDuplicate(s, s[i], i))
        {
            if (prevDupLoc != -1)
            {
                insertPos = moveChar(s, i - prevDupLoc - 1, insertPos, prevDupLoc + 1);
            }
            else 
            {
                insertPos = i;
            }
            prevDupLoc = i;
        }
        i ++;
    }
    if (prevDupLoc != -1)
    {
        insertPos = moveChar(s, i - prevDupLoc - 1, insertPos, prevDupLoc + 1);
    }
    while (insertPos < s.size())
    {
        s[insertPos] = '\0';
        insertPos ++;
    }
    cout << s << endl;
}
