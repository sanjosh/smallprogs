
/*
http://www.geeksforgeeks.org/amazon-interview-set-86-sde/

Written test
1) Given a array of number find the next greater no in the right of each element

Example-    Input     12 15 22 09 07 02 18 23 27
            Output    15 22 27 18 18 18 23 27 -1


*/
#include <iostream>
#include <strings.h>
using namespace std;

int main(int argc, char* argv[])
{
    int a[] = { 24, 15, 22, 9, 17, 2, 18, 43, 27};
    int max = sizeof(a)/sizeof(a[0]);
    int* nextmax = new int[max];
    bzero(nextmax, sizeof(int) * max);

    nextmax[max-1] = -1;
    for (int i = max - 2; i >=0; i --)
    {
        if (a[i] < a[i+1])
        {
            nextmax[i] = a[i+1];
        }
        else if (a[i] < nextmax[i+1])
        {
            nextmax[i] = nextmax[i+1];
        }
        else
        {
            cout << "entering loop for " << a[i] << endl;
            for (int j = i+1; j < max; j++)
            {
                if (a[i] < nextmax[j])
                {
                    nextmax[i] = nextmax[j];
                    break;
                }
            }
        }
    }
/*
    for (int i = 0; i < max-1; i++)
    {
        for (int j = i+1; j < max; j++)
        {
            if (a[j] > a[i])
            {
                nextmax[i] = a[j];
                break;
            }
        }
    }
*/
    for (int i = 0; i < max; i++)   
    {
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < max; i++)   
    {
        cout << nextmax[i] << " ";
    }
    cout << endl;
    
}

Method 2 (Using Stack)
Thanks to pchild for suggesting following approach.
1) Push the first element to stack.
2) Pick rest of the elements one by one and follow following steps in loop.
....a) Mark the current element as next.
....b) If stack is not empty, then pop an element from stack and compare it with next.
....c) If next is greater than the popped element, then next is the next greater element fot the popped element.
....d) Keep poppoing from the stack while the popped element is smaller than next. next becomes the next greater element for all such popped elements
....g) If next is smaller than the popped element, then push the popped element back.
3) After the loop in step 2 is over, pop all the elements from stack and print -1 as next element for them.

#include<stdio.h>
#include<stdlib.h>
#define STACKSIZE 100
 
// stack structure
struct stack
{
    int top;
    int items[STACKSIZE];
};
 
// Stack Functions to be used by printNGE()
void push(struct stack *ps, int x)
{
    if (ps->top == STACKSIZE-1)
    {
        printf("Error: stack overflow\n");
        getchar();
        exit(0);
    }
    else
    {
        ps->top += 1;
        int top = ps->top;
        ps->items [top] = x;
    }
}
 
bool isEmpty(struct stack *ps)
{
    return (ps->top == -1)? true : false;
}
 
int pop(struct stack *ps)
{
    int temp;
    if (ps->top == -1)
    {
        printf("Error: stack underflow \n");
        getchar();
        exit(0);
    }
    else
    {
        int top = ps->top;
        temp = ps->items [top];
        ps->top -= 1;
        return temp;
    }
}
 
/* prints element and NGE pair for all elements of
arr[] of size n */
void printNGE(int arr[], int n)
{
    int i = 0;
    struct stack s;
    s.top = -1;
    int element, next;
 
    /* push the first element to stack */
    push(&s, arr[0]);
 
    // iterate for rest of the elements
    for (i=1; i<n; i++)
    {
        next = arr[i];
 
        if (isEmpty(&s) == false)
        {
            // if stack is not empty, then pop an element from stack
            element = pop(&s);
 
            /* If the popped element is smaller than next, then
                a) print the pair
                b) keep popping while elements are smaller and
                stack is not empty */
            while (element < next)
            {
                printf("\n %d --> %d", element, next);
                if(isEmpty(&s) == true)
                   break;
                element = pop(&s);
            }
 
            /* If element is greater than next, then push
               the element back */
            if (element > next)
                push(&s, element);
        }
 
        /* push next to stack so that we can find
           next greater for it */
        push(&s, next);
    }
 
    /* After iterating over the loop, the remaining
       elements in stack do not have the next greater
       element, so print -1 for them */
    while (isEmpty(&s) == false)
    {
        element = pop(&s);
        next = -1;
        printf("\n %d -- %d", element, next);
    }
}
 
/* Driver program to test above functions */
int main()
{
    int arr[]= {11, 13, 21, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    printNGE(arr, n);
    getchar();
    return 0;
}

Output:

 11 -- 13
 13 -- 21
 3 -- -1
 21 -- -1

Time Complexity: O(n). The worst case occurs when all elements are sorted in decreasing order. If elements are sorted in decreasing order, then every element is processed at most 4 times.
a) Initialy pushed to the stack.
b) Popped from the stack when next element is being processed.
c) Pushed back to the stack because next element is smaller.
d) Popped from the stack in step 3 of algo.
