
/*

https://www.geeksforgeeks.org/find-distance-between-two-nodes-of-a-binary-tree/

both are in same subtree ? dist = N1 + n2
if one found in subtree and other is the current node ? dist = N1

two options for distance
1. pass level down and node notes its level
1. let node set dist = 0 and then increment it on every pop

what should node do ? initialize
what should parent do ? increment by 1 and pass to parent

*/

#include <iostream>
#include <stdlib.h>
 
using namespace std;

struct Algo
{
    int left_data;
    int right_data;

    Algo(int l, int r) : left_data(l), right_data(r) {}
};
 
struct Node
{
   int data;
   Node* left = nullptr;
   Node* right = nullptr;

   Node(int d) : data(d) { }
};

struct ReturnVal
{
    int r = -1;
    int l = -1;
};

ReturnVal preorder(const Node* current, const Algo& a)
{
    ReturnVal v;
    if (current == nullptr)
    {
        return v;
    }

    if (current->data == a.left_data)
    {
        cout << "l" << current->data << endl;
        v.l = 0;
    }
    else if (current->data == a.right_data)
    {
        cout << "r" << current->data << endl;
        v.r = 0;
    }
    auto ret_left = preorder(current->left, a);
    auto ret_right = preorder(current->right, a);

    if (ret_left.l != -1) {
       v.l = ret_left.l + 1;
    } else if (ret_left.r != -1) {
       v.r = ret_left.r + 1;
    }

    if (ret_right.l != -1) {
       v.l = ret_right.l + 1;
    } else if (ret_right.r != -1) {
       v.r = ret_right.r + 1;
    }

    if (v.r >= 0 && v.l >= 0) {
        cout << "distance " << v.l << "," << v.r << endl;
        v.r = -1;
        v.l = -1;
    } 
    else {
        cout << current->data << " v " << v.l << "," << v.r << endl;
    }
    return v;
}


int main()
{

    Node *root = new Node(1);

    root->left        = new Node(2);
    root->right       = new Node(3);
    root->left->left  = new Node(4);
    root->left->right = new Node(5);
    root->left->left->left  = new Node(7);

    int left_distance = -1;
    int right_distance = -1;

    Algo a(1, 4);
    preorder(root, a);
}

