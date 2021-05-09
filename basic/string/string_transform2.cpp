/*
BFS
    https://stackoverflow.com/a/35637762/2357408
 */
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int size;

struct str
{
    char a[1000];
    int change;
};

int position(char a[], char b)
{
    for(int i = 0; i < size; i++) {
        if(a[i] == b)
            return i;
    }
    return -1;
}

void swap(char a[], int pos, int shift)
{	
    int temp = a[pos];
    a[pos] = a[pos + shift];
    a[pos + shift] = temp;
}

int minChange(char arr[], char out[])
{
    std::queue <str> q;
    
    str i;
    strcpy(i.a, arr);
    i.change = 0;
    
    q.push(i);
    
    while(!q.empty()) {
        str fin = q.front();
        q.pop();
        if(strcmp(out, fin.a) == 0)
            return fin.change;
        
        int pos = position(fin.a, '$');
            
        if(pos > 0) {
            str temp;
            strcpy(temp.a, fin.a);
            swap(temp.a, pos, -1);
            temp.change = fin.change + 1;
            q.push(temp);
        }
        if(pos < size - 1) {
            str temp;
            strcpy(temp.a, fin.a);
            swap(temp.a, pos, 1);
            temp.change = fin.change + 1;
            q.push(temp);
        }
        if(pos > 1 && (fin.a[pos - 1] != fin.a[pos - 2])) {
            str temp;
            strcpy(temp.a, fin.a);
            swap(temp.a, pos, -2);
            temp.change = fin.change + 1;
            q.push(temp);
        }
        if(pos < size - 2 && (fin.a[pos + 1] != fin.a[pos + 2])) {
            str temp;
            strcpy(temp.a, fin.a);
            swap(temp.a, pos, 2);
            temp.change = fin.change + 1;
            q.push(temp);
        }
    }
    return 0;
}


int main()
{
    size = 3;
    cout<<minChange("a$b", "ab$")<<endl;
    size = 6;
    cout<<minChange("abaa$a", "b$aaaa")<<endl;
    size = 5;
    cout<<minChange("aba$a", "$baaa")<<endl;	
}
