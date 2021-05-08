
/*
http://www.geeksforgeeks.org/print-right-view-binary-tree-2/

Given a Binary Tree, print Right view of it. Right view of a Binary Tree is set of nodes visible when tree is visited from Right side.

Right view of following tree is 1 3 7 8

          1
       /     \
     2        3
   /   \     /  \
  4     5   6    7
                  \
                   8


The Right view contains all nodes that are first nodes in their levels. 
A simple solution is to do level order traversal and print the last node in every level.

The problem can also be solved using simple recursive traversal. 
We can keep track of level of a node by passing a parameter to all recursive calls. 
The idea is to keep track of maximum level also. 
And traverse the tree in a manner that right subtree is visited before left subtree. 
Whenever we see a node whose level is more than maximum level so far, we print the node 
because this is the first node in its level (Note that we traverse the right subtree before left subtree). 

ideas
1. level order traversal with right first

*/
// C program to print right view of Binary Tree

#include <iostream>
#include <stdlib.h>
using namespace std;
 
struct Node
{
    int data;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(int d) : data(d) { }
};
 
// Recursive function to print right view of a binary tree.
void rightViewUtil(Node *root, int level, int *max_level)
{
    // Base Case
    if (root==nullptr)  return;
 
    // If this is the first Node of its level
    if (*max_level < level)
    {
        cout << root->data << endl;
        *max_level = level;
    }
 
    // Recur for right subtree first, then left subtree
    rightViewUtil(root->right, level+1, max_level);
    rightViewUtil(root->left, level+1, max_level);
}
 
// A wrapper over rightViewUtil()
void rightView(Node *root)
{
    int max_level = 0;
    rightViewUtil(root, 1, &max_level);
}
 
// Driver Program to test above functions
int main()
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->right->left->right = new Node(8);
 
    rightView(root);
 
    return 0;
}

