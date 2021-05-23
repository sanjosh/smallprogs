/*

NGE[i] = smallest element in (i+1, n) which is greater

if NGE[i - 1] < NGE[i], 
   then NGE[i - 1] = NGE[i]
   else NGE[i - 1] = some element in (index of NGE[i], n)

there will be no intersection between (i-1, index of NGE[i-1]) and (i, index of NGE[i])

e.g. {7, 5, 6, 8}
NGE[7] = 8, NGE[5] = 6

e.g. {7, 5, 8, 6}
NGE[7] = NGE[5] = 8

since there is no overlap, this problem can be solved using stack (nested scope)

nge(i-1) is either nge(i) or an element beyond nge(i)

*/

/*
http://www.geeksforgeeks.org/amazon-interview-set-86-sde/

Written test
1) Given a array of number find the next greater no in the right of each element

Example-    Input     12 15 22 09 07 02 18 23 27
            Output    15 22 27 18 18 18 23 27 -1


*/

#include <climits>
#include <iostream>
#include <strings.h>
#include <stack>

using namespace std;

void NGE_Stack_reverse(int a[], int max) 
{
    stack<int> s;
    s.push(a[max - 1]);
    int nge[max];

    nge[max - 1] = -1;

    for (int j = max - 2; j >= 0; j --) {
        while (s.size() && a[j] > s.top()) {
            s.pop();
        }
        if (s.size()) {
            nge[j] = s.top();
        } else {
            nge[j] = -1;
        }
        s.push(a[j]);
    }

    for (int j = 0; j < max; j ++) {
        cout << a[j] << " next greater is " << nge[j] << endl;
    }
}

void NGE_nostack(int a[], int max) 
{
   
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

/*
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
*/

#include<stdio.h>
#include<stdlib.h>
#define STACKSIZE 100
 
// stack structure
struct MyStack
{
    int top;
    int items[STACKSIZE];
};
 
// Stack Functions to be used by printNGE()
void push(struct MyStack *ps, int x)
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
 
bool isEmpty(struct MyStack *ps)
{
    return (ps->top == -1)? true : false;
}
 
int pop(struct MyStack *ps)
{
    int temp;
    if (ps->top == -1)
    {
        printf("Error: MyStack underflow \n");
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
    struct MyStack s;
    s.top = -1;
    int element, next;
 
    /* push the first element to MyStack */
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
                printf("%d --> %d\n", element, next);
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
        printf("%d -- %d\n", element, next);
    }
}
 
/* Driver program to test above functions */
int main()
{
    int arr[]= {7, 5, 8, 18};
    int n = sizeof(arr)/sizeof(arr[0]);
    printNGE(arr, n);
    NGE_Stack_reverse(arr, n);
    return 0;
}

/*
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
*/
