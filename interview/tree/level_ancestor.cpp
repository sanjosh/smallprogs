
http://en.wikipedia.org/wiki/Level_ancestor_problem

TODO

Given a Binary Tree and a key, write a function that prints all the ancestors of the key in the given binary tree.

For example, if the given tree is following Binary Tree and key is 7, then your function should print 4, 2 and 1.


              1
            /   \
          2      3
        /  \
      4     5
     /
    7

Thanks to Mike , Sambasiva and wgpshashank for their contribution.
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
 
using namespace std;
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
   int data;
   struct node* left;
   struct node* right;
};
 
/* If target is present in tree, then prints the ancestors
   and returns true, otherwise returns false. */
bool printAncestors(struct node *root, int target)
{
  /* base cases */
  if (root == NULL)
     return false;
 
  if (root->data == target)
     return true;
 
  /* If target is present in either left or right subtree of this node,
     then print this node */
  if ( printAncestors(root->left, target) ||
       printAncestors(root->right, target) )
  {
    cout << root->data << " ";
    return true;
  }
 
  /* Else return false */
  return false;
}
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newnode(int data)
{
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}
 
/* Driver program to test above functions*/
int main()
{
 
  /* Construct the following binary tree
              1
            /   \
          2      3
        /  \
      4     5
     /
    7
  */
  struct node *root = newnode(1);
  root->left        = newnode(2);
  root->right       = newnode(3);
  root->left->left  = newnode(4);
  root->left->right = newnode(5);
  root->left->left->left  = newnode(7);
 
  printAncestors(root, 7);
 
  getchar();
  return 0;
}

Output:
4 2 1

Time Complexity: O(n) where n is the number of nodes in the given Binary Tree.
