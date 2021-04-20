
#include <string>
#include <stdlib.h>
#include <stack>
#include <iostream>

using namespace std;


void anagram(string s1, string s2, string instr, string s, int level)
{
    cout << "DEBUG=" << s1 << ":" << s2 << ":" << instr << ":" << level << endl;

    if (s2.empty())
    {   
        if (s1.empty() && s.empty())
        {
            cout << instr << endl;
        }
        return;
    }

    if (s1.size())
    {
        anagram(s1.substr(1), s2, instr + "i", s1[0] + s, level + 1);
    }
    if (s.size() && s[0] == s2[0])
    {
        anagram(s1, s2.substr(1), instr + "o", s.substr(1), level + 1);
    }
}

void anagram(string s1, string s2)
{
    string instr;
    string s;
    cout << "["  << endl;
    anagram(s1, s2, instr, s, 1);
    cout << "]" << endl;
}

int main(int argc, char* argv[])
{
    if (argc != 3) exit(1);
    anagram(argv[1], argv[2]);
}

