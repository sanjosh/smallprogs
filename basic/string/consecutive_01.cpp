#include <assert.h>
#include <iostream>

using namespace std;

/*

find max string in which consecutive 0's match consecutive 1's

DFA 

int len[2] 

000  
111  : if (len[0] = len[1])
00  : if (len[0] = len[1]) { len[0] = 0}
111 

 0 : 
    if (transition)
    { 
        if len[1] == len[0] - output
        len[1] = 0;
    }
    len[0] ++

 1 : 
    len[1] ++

*/


int main(int argc, char* argv[])
{
    char* str = argv[1];
    char c;
        
    int len[2] = {0, 0 };

    char prevchar = '-';

    while (c = *str)
    {
        switch (c) 
        {
            case '0':
            {
                if (prevchar == '1')
                {
                    if (len[1] && (len[1] == len[0]))
                    {
                        cout << "same:" << len[0] << ":" << len[1] << endl; 
                    } 
                    len[0] = 0;
                }
                len[0] ++;
                break;
            }

            case '1':
            {
                if (prevchar == '0')
                {
                    if (len[0] && (len[1] == len[0]))
                    {
                        cout << "same:" << len[0] << ":" << len[1] << endl; 
                    }
                    len[1] = 0;
                }
                len[1] ++;
                break;
            }

            default:
            {
                assert("what" == 0);
            }
        }
        prevchar = c;
        str ++;
    }

    if (len[1] && (len[1] == len[0]))
    {
        cout << "same:" << len[0] << ":" << len[1] << endl; 
    } 
}
