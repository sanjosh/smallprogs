
/*
    http://www.geeksforgeeks.org/tug-of-war/

    Balanced Partition problem
http://www.geeksforgeeks.org/dynamic-programming-set-18-partition-problem/

http://chinmaylokesh.wordpress.com/2011/02/10/balanced-partition-problem-finding-the-minimized-sum-between-two-partitions-of-a-set-of-positive-integers/
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>
using namespace std;

int* arr = 0;
int n = 0;
bool* soln;
int min_diff = INT_MAX;
int sum;
 
// function that tries every possible solution by calling itself recursively
void TOWUtil(bool* curr_elements, int no_of_selected_elements, int curr_sum, int curr_position)
{
    // checks whether the it is going out of bound
    if (curr_position == n)
        return;
 
    // checks that the numbers of elements left are not less than the
    // number of elements required to form the solution
    if ((n/2 - no_of_selected_elements) > (n - curr_position))
        return;
 
    // consider the cases when current element is not included in the solution
    TOWUtil(curr_elements, no_of_selected_elements, curr_sum, curr_position+1);
 
    // add the current element to the solution
    no_of_selected_elements++;
    curr_sum = curr_sum + arr[curr_position];
    curr_elements[curr_position] = true;
 
    // checks if a solution is formed
    if (no_of_selected_elements == n/2)
    {
        // checks if the solution formed is better than the best solution so far
        if (abs(sum/2 - curr_sum) < min_diff)
        {
            min_diff = abs(sum/2 - curr_sum);
            for (int i = 0; i<n; i++)
                soln[i] = curr_elements[i];
        }
    }
    else
    {
        // consider the cases where current element is included in the solution
        TOWUtil(curr_elements, no_of_selected_elements, curr_sum, curr_position+1);
    }
 
    // removes current element before returning to the caller of this function
    curr_elements[curr_position] = false;
}
 
// main function that generate an arr
void tugOfWar(int *arr, int n)
{
    // the boolen array that contains the inclusion and exclusion of an element
    // in current set. The number excluded automatically form the other set
    bool* curr_elements = new bool[n];
 
    // The inclusion/exclusion array for final solution
    soln = new bool[n];
 
    min_diff = INT_MAX;
 
    int sum = 0;
    for (int i=0; i<n; i++)
    {
        sum += arr[i];
        curr_elements[i] =  soln[i] = false;
    }
 
    // Find the solution using recursive function TOWUtil()
    TOWUtil(curr_elements, 0, 0, 0);
 
    // Print the solution
    cout << "The first subset is: ";
    int subsetsum = 0;
    for (int i=0; i<n; i++)
    {
        subsetsum += arr[i];
        if (soln[i] == true)
            cout << arr[i] << " ";
    }
    cout << "sum is " << subsetsum << endl;
    subsetsum = 0;
    cout << "\nThe second subset is: ";
    for (int i=0; i<n; i++)
    {
        subsetsum += arr[i];
        if (soln[i] == false)
            cout << arr[i] << " ";
    }
    cout << "sum is " << subsetsum << endl;
}
 
// Driver program to test above functions
int main()
{
    unsigned int seed = getpid();
    srand(seed);

    n = 20 + (rand_r(&seed) % 20);
    cout << "n elem=" << n << endl;
    arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand_r(&seed) % 100;
    }

    tugOfWar(arr, n);
    return 0;
}

