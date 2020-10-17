#include <iostream>
using namespace std;

bool isPower(unsigned int a)
{
    unsigned int x = 1;
    unsigned int count = 0;
    while (x) 
    {   
        if (a & x) count ++; 
        x <<= 1;
    }   
    return (count == 1); 
}

int main(int argc, char* argv[])
{
    unsigned int i = 0;
    for (i = 0; i < 65536; i++)
    {
        if (isPower(i))
        {
            cout << i << "is " << endl;
        }
    }
}
