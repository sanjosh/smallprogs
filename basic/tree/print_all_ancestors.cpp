
/*
http://en.wikipedia.org/wiki/Level_ancestor_problem

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

*/

#include <iostream>
#include <stdlib.h>
 
using namespace std;
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
   int data;
   Node* left = nullptr;
   Node* right = nullptr;

   Node(int d) : data(d) { }
};

struct Algo
{
    int data;

    Algo(int d) : data(d) {}

    bool predicate(const Node* n)
    {
        return (n->data == this->data);
    }

    void postProcess(const Node* p)
    {
        cout << p->data << endl;
    }
};

bool preorder(const Node* current, Algo& a)
{
   if (current == nullptr)
   {
      return false;
   }

    if (a.predicate(current))
    {
         return true;
    }
    auto x = preorder(current->left, a);
    auto y = preorder(current->right, a);
    if (x || y) {
      a.postProcess(current);
   }
   return x || y;
}



int main()
{
    Algo a(4);

    Node *root = new Node(1);

    root->left        = new Node(2);
    root->right       = new Node(3);
    root->left->left  = new Node(4);
    root->left->right = new Node(5);
    root->left->left->left  = new Node(7);
 
    preorder(root, a);
}

