
/*
http://www.geeksforgeeks.org/program-nth-catalan-number/
*/

// A recursive function to find nth catalan number
unsigned long int catalan(unsigned int n)
{
    // Base case
    if (n <= 1) return 1;
 
    // catalan(n) is sum of catalan(i)*catalan(n-i-1)
    unsigned long int res = 0;
    for (int i=0; i<n; i++)
        res += catalan(i)*catalan(n-i-1);
 
    return res;
}

/*
Dynamic Programming Solution
We can observe that the above recursive implementation does 
a lot of repeated work (we can the same by drawing recursion tree). 
Since there are overlapping subproblems, we can use dynamic 
programming for this. Following is a Dynamic programming based implementation in C++.

*/
#include<iostream>
using namespace std;
 
// A dynamic programming based function to find nth
// Catalan number
unsigned long int catalanDP(unsigned int n)
{
    // Table to store results of subproblems
    unsigned long int catalan[n+1];
 
    // Initialize first two values in table
    catalan[0] = catalan[1] = 1;
 
    // Fill entries in catalan[] using recursive formula
    for (int i=2; i<=n; i++)
    {
        catalan[i] = 0;
        for (int j=0; j<i; j++)
            catalan[i] += catalan[j] * catalan[i-j-1];
    }
 
    // Return last entry
    return catalan[n];
}

/*
http://www.geeksforgeeks.org/dynamic-programming-set-37-boolean-parenthesization-problem/

Symbols
    'T' ---> true 
    'F' ---> false 

And following operators filled between symbols

Operators
    &   ---> boolean AND
    |   ---> boolean OR
    ^   ---> boolean XOR 

Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true. 

TODO

Given a number n find the number of balanced parentheses expressions of that length.

Input: 2

Output: 1 which is (),

    Input: 4

    Output: 2 which are (()) and ()().

    I gave a complex solution involving segment tree in which he pointed out the mistakes and then asked to write a code to check if a given expression is balanced or not.

Solution:
Let T(i, j) represents the number of ways to parenthesize the symbols between i and j (both inclusive) 
such that the subexpression between i and j evaluates to true.

trueeq

Let F(i, j) represents the number of ways to parenthesize the symbols between i and j (both inclusive) 
such that the subexpression between i and j evaluates to false.

falseeq

Base Cases:

T(i, i) = 1 if symbol[i] = 'T' 
T(i, i) = 0 if symbol[i] = 'F' 

F(i, i) = 1 if symbol[i] = 'F' 
F(i, i) = 0 if symbol[i] = 'T'

If we draw recursion tree of above recursive solution, 
we can observe that it many overlapping subproblems. 

Like other dynamic programming problems, it can be solved by filling a table in bottom up manner. 
Following is C++ implementation of dynamic programming solution.

*/

#include<iostream>
#include<cstring>
using namespace std;
 
// Returns count of all possible parenthesizations that lead to
// result true for a boolean expression with symbols like true
// and false and operators like &, | and ^ filled between symbols
int countParenth(char symb[], char oper[], int n)
{
    int F[n][n], T[n][n];
 
    // Fill diaginal entries first
    // All diagonal entries in T[i][i] are 1 if symbol[i]
    // is T (true).  Similarly, all F[i][i] entries are 1 if
    // symbol[i] is F (False)
    for (int i = 0; i < n; i++)
    {
        F[i][i] = (symb[i] == 'F')? 1: 0;
        T[i][i] = (symb[i] == 'T')? 1: 0;
    }
 
    // Now fill T[i][i+1], T[i][i+2], T[i][i+3]... in order
    // And F[i][i+1], F[i][i+2], F[i][i+3]... in order
    for (int gap=1; gap<n; ++gap)
    {
        for (int i=0, j=gap; j<n; ++i, ++j)
        {
            T[i][j] = F[i][j] = 0;
            for (int g=0; g<gap; g++)
            {
                // Find place of parenthesization using current value
                // of gap
                int k = i + g;
 
                // Store Total[i][k] and Total[k+1][j]
                int tik = T[i][k] + F[i][k];
                int tkj = T[k+1][j] + F[k+1][j];
 
                // Follow the recursive formulas according to the current
                // operator
                if (oper[k] == '&')
                {
                    T[i][j] += T[i][k]*T[k+1][j];
                    F[i][j] += (tik*tkj - T[i][k]*T[k+1][j]);
                }
                if (oper[k] == '|')
                {
                    F[i][j] += F[i][k]*F[k+1][j];
                    T[i][j] += (tik*tkj - F[i][k]*F[k+1][j]);
                }
                if (oper[k] == '^')
                {
                    T[i][j] += F[i][k]*T[k+1][j] + T[i][k]*F[k+1][j];
                    F[i][j] += T[i][k]*T[k+1][j] + F[i][k]*F[k+1][j];
                }
            }
        }
    }
    return T[0][n-1];
}
 
// Driver program to test above function
int main()
{
    char symbols[] = "TTFT";
    char operators[] = "|&^";
    int n = strlen(symbols);
 
    // There are 4 ways
    // ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T))
    cout << countParenth(symbols, operators, n);
    return 0;
}

/*
Output:

4

Time Complexity: O(n3)
Auxiliary Space: O(n2)

http://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/

Given an expression string exp, write a program to examine whether the pairs 
and the orders of “{“,”}”,”(“,”)”,”[","]” are correct in exp. 

For example, the program should print true for exp = “[()]{}{[()()]()}” and false for exp = “[(])”

Algorithm:

1) Declare a character stack S.

2) Now traverse the expression string exp.
    a) If the current character is a starting bracket (‘(‘ or ‘{‘ or ‘[') then push it to stack.
    b) If the current character is a closing bracket (')' or '}' or ']‘) then pop from stack 
       and if the popped character is the matching starting bracket then fine else parenthesis are not balanced.

3) After complete traversal, if there is some starting bracket left in stack then “not balanced”

Implementation:

*/
#include<stdio.h>
#include<stdlib.h>
#define bool int
 
/* structure of a stack node */
struct sNode
{
   char data;
   struct sNode *next;
};
 
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data);
 
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref);
 
/* Returns 1 if character1 and character2 are matching left
   and right Parenthesis */
bool isMatchingPair(char character1, char character2)
{
   if(character1 == '(' && character2 == ')')
     return 1;
   else if(character1 == '{' && character2 == '}')
     return 1;
   else if(character1 == '[' && character2 == ']')
     return 1;
   else
     return 0;
}
 
/*Return 1 if expression has balanced Parenthesis */
bool areParenthesisBalanced(char exp[])
{
   int i = 0;
 
   /* Declare an empty character stack */
   struct sNode *stack = NULL;
 
   /* Traverse the given expression to check matching parenthesis */
   while(exp[i])
   {
      /*If the exp[i] is a starting parenthesis then push it*/
      if(exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
        push(&stack, exp[i]);
 
      /* If exp[i] is a ending parenthesis then pop from stack and
          check if the popped parenthesis is a matching pair*/
      if(exp[i] == '}' || exp[i] == ')' || exp[i] == ']')
      {
             
          /*If we see an ending parenthesis without a pair then return false*/
         if(stack == NULL)
           return 0;
 
         /* Pop the top element from stack, if it is not a pair
            parenthesis of character then there is a mismatch.
            This happens for expressions like {(}) */
         else if ( !isMatchingPair(pop(&stack), exp[i]) )
           return 0;
      }
      i++;
   }
    
   /* If there is something left in expression then there is a starting
      parenthesis without a closing parenthesis */
   if(stack == NULL)
     return 1; /*balanced*/
   else
     return 0;  /*not balanced*/
}
 
/* UTILITY FUNCTIONS */
/*driver program to test above functions*/
int main()
{
  char exp[100] = "{()}[]";
  if(areParenthesisBalanced(exp))
    printf("\n Balanced ");
  else
    printf("\n Not Balanced ");  \
  getchar();
}   
 
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data)
{
  /* allocate node */
  struct sNode* new_node =
            (struct sNode*) malloc(sizeof(struct sNode));
 
  if(new_node == NULL)
  {
     printf("Stack overflow \n");
     getchar();
     exit(0);
  }          
 
  /* put in the data  */
  new_node->data  = new_data;
 
  /* link the old list off the new node */
  new_node->next = (*top_ref); 
 
  /* move the head to point to the new node */
  (*top_ref)    = new_node;
}
 
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref)
{
  char res;
  struct sNode *top;
 
  /*If stack is empty then error */
  if(*top_ref == NULL)
  {
     printf("Stack overflow \n");
     getchar();
     exit(0);
  }
  else
  {
     top = *top_ref;
     res = top->data;
     *top_ref = top->next;
     free(top);
     return res;
  }
}

/*
Time Complexity: O(n)
Auxiliary Space: O(n) for stack.

http://www.geeksforgeeks.org/print-all-combinations-of-balanced-parentheses/

Write a function to generate all possible n pairs of balanced parentheses. 

Catalan Number Problem

For example, if n=1
{}
for n=2
{}{}
{{}}

Algorithm:
Keep track of counts of open and close brackets. 
Initialize these counts as 0. 
Recursively call the _printParenthesis() function until open bracket count is less than the given n. 

If open bracket count becomes more than the close bracket count, then put a closing bracket and recursively call for the remaining brackets. 

If open bracket count is less than n, then put an opening bracket and call _printParenthesis() for the remaining brackets.

Thanks to Shekhu for providing the below code.
*/

# include<stdio.h>
# define MAX_SIZE 100
 
void _printParenthesis(int pos, int n, int open, int close);
 
/* Wrapper over _printParenthesis()*/
void printParenthesis(int n)
{
  if(n > 0)
     _printParenthesis(0, n, 0, 0);
  return;
}    
 
void _printParenthesis(int pos, int n, int open, int close)
{
  static char str[MAX_SIZE];    
 
  if(close == n)
  {
    printf("%s \n", str);
    return;
  }
  else
  {
    if(open > close) {
        str[pos] = '}';
        _printParenthesis(pos+1, n, open, close+1);
    }
    if(open < n) {
       str[pos] = '{';
       _printParenthesis(pos+1, n, open+1, close);
    }
  }
}
 
/* driver program to test above functions */
int main()
{
  int n = 4;
  printParenthesis(n);
  getchar();
  return 0;
}
