
/*

https://www.geeksforgeeks.org/find-distance-between-two-nodes-of-a-binary-tree/

*/

#include <iostream>
#include <stdlib.h>
 
using namespace std;
 
struct Node
{
   int data;
   Node* left = nullptr;
   Node* right = nullptr;

   Node(int d) : data(d) { }
};

struct Algo
{
    int left_data;
    int right_data;
    int leftDistance = -1;
    int rightDistance = -1;

    Algo(int l, int r) : left_data(l), right_data(r) {}

    void predicate(const Node* n, bool& l, bool& r)
    {
        if (n->data == this->left_data) {
           leftDistance = 0;
           l = true;
           cout << "left found" << endl;
        } else if (n->data == this->right_data) {
           rightDistance = 0;
           r = true;
           cout << "right found" << endl;
        }
    }

    void postProcessLeft()
    {
        if (leftDistance != -1) {
            leftDistance ++;
            cout << leftDistance << "L" << endl;
        }
    }

    void postProcessRight()
    {
        if (rightDistance != -1) {
            rightDistance ++;
            cout << rightDistance << "R" << endl;
        }
    }

    void postProcess(const Node* current) {
        if ((leftDistance != -1) && (rightDistance != -1))
        {
            cout << current->data << ":" << leftDistance + rightDistance << endl;
            leftDistance = -1;
            rightDistance = -1;
        }
    }
};

bool preorder(const Node* current, int level, int &left_level, int& right_level, Algo& a)
{
    if (current == nullptr)
    {
        return false;
    }

    if (current->data = a.left_data)
    {
        left_level = level;
    }
    else if (current->data = a.right_data)
    {
        right_level = level;
    }
    preorder(current->left, level + 1, left_level, right_level, a);
    preorder(current->right, level + 1, left_level, right_level, a);
    if (left_level && right_level) {
        cout << "distance 
    }
}



int main()
{

    Node *root = new Node(1);

    root->left        = new Node(2);
    root->right       = new Node(3);
    root->left->left  = new Node(4);
    root->left->right = new Node(5);
    root->left->left->left  = new Node(7);

    Algo a(2, 5);
 
    preorder(root, a);
}

