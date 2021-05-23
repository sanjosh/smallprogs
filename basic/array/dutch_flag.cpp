
/* Another method : keep count number of 0, 1, 2 and simply replace
 */

#include <iostream>
using namespace std;
#include <string.h>

void swap(char* str, int i, int index)
{
    cout << "swapping " << i << " and " << index << endl;
    char tmp = str[i];
    str[i] = str[index];
    str[index] = tmp;
}

int main(int argc, char* argv[])
{
    char* str = strdup(argv[1]);
    int len = strlen(str);

    int low = 0;
    int mid = 0;
    int high = len-1;

    while (mid <= high)
    {
        if (str[mid] == '0') 
        {
            swap(str, low, mid); 
            low++; 
            mid++;
        }
        else if (str[mid] == '1') 
        {
            mid++; 
        }
        else if (str[mid] == '2') 
        {
            swap(str, mid, high); 
            high--;
        }
        cout << str << endl;
    }
    cout << str << endl;
}
