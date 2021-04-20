#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

static string keypad[] =
{
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz",
};

int main(int argc, char* argv[])
{
    list<string> generated;
    list<string> old_generated;
    char* input = argv[1];

    old_generated.push_back("0"); // dummy char

    char c;
    while (c = *input ++)
    {
        assert (isdigit(c));
        if ((c == '0') || (c == '1')) 
        {   
            continue;
        }

        const string& s = keypad[c - '2'];
        list<string>::iterator iter;
        for (iter = old_generated.begin(); iter != old_generated.end(); ++iter)
        {
            for (size_t i = 0; i < s.size(); i++)
            {
                string newstr = string(*iter).append(1, s[i]);
                generated.push_back(newstr);
            }
        }
        old_generated = generated;
        generated.clear();

    }

    generated = old_generated;

    list<string>::iterator iter;
    for (iter = generated.begin(); iter != generated.end(); ++iter)
    {
        iter->erase(0, 1);
        std::cout << *iter << std::endl;
    }
}

