
/*
http://www.geeksforgeeks.org/horners-method-polynomial-evaluation/
*/

2x^3 - 6x^2 + 2x - 1

((2x - 6) * x + 2)x  - 1 = 2x^3-6x^2 + 2x -1



// returns value of poly[0]x(n-1) + poly[1]x(n-2) + .. + poly[n-1]
int horner(int poly[], int n, int x)
{
    int result = poly[0];  // Initialize result
 
    // Evaluate value of polynomial using Horner's method
    for (int i=1; i<n; i++)
        result = result*x + poly[i];
 
    return result;
}
