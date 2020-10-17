
//http://code.google.com/codejam/contest/619102/dashboard#s=p0

 A company is located in two very tall buildings. The company intranet connecting the buildings consists of many wires, each connecting a window on the first building to a window on the second building.

You are looking at those buildings from the side, so that one of the buildings is to the left and one is to the right. The windows on the left building are seen as points on its right wall, and the windows on the right building are seen as points on its left wall. Wires are straight segments connecting a window on the left building to a window on the right building.

#include <iostream>
#include <stdio.h>
using namespace std;

struct Line
{
    int A;
    int B;
};

int sign(int a)
{
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

int main(int argc, char* argv[])
{
    int intersect = 0;

    int len = 0;
    scanf("%d", &len);

    Line* line = new Line[len];
    for (int i = 0; i < len; i++)
    {
        scanf("%d %d", &line[i].A, &line[i].B);
    }

    /* for the Lines on A for better perf */
    for (int i = 0; i < len; i++)
    {
        for (int j = i+1; j < len; j++)
        {   
            int asign = (line[i].A - line[j].A) ;
            int bsign = (line[i].B - line[j].B) ;
            if (asign != bsign) intersect ++;
        }
    } 

    cout << "Case# " << intersect << endl;
}
