/*
    convert BST to Doubly linked list
    IMP
*/

#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(int val) : value(val) { }
};

void makeDLL(Node* n, Node*& gmin, Node*& gmax)
{
    if (n->left)
    {
        Node* max;
        Node* min;

        makeDLL(n->left, min, max);

        max->right = n; // max of left subtree is predecessor
        n->left = max;

        gmin = min;  // return min for use by caller
    }            
    else
    {
        gmin = n;
    }

    if (n->right)
    {
        Node* max;
        Node* min;

        makeDLL(n->right, min, max);

        min->left = n; // min of right subtree is successor
        n->right = min;

        gmax = max; // return max for use by caller
    }
    else
    {
        gmax = n;
    }
}

void makeDLL2(Node* cur, Node*& prevNode)
{
    if (cur == nullptr) {
        return;
    }
    makeDLL2(cur->left, prevNode);
    if (prevNode)
    {
        prevNode->right = cur;
        cur->left = prevNode;
        cout << prevNode->value << ":" << cur->value  << endl;
    }
    prevNode = cur;
    makeDLL2(cur->right, prevNode);
}

void printInorder (Node* n, int level)
{
    if (!n) return;
    printInorder(n->left, level+1);
    cout << n->value << " at " << level << endl;
    printInorder(n->right, level+1);
}

void insert(Node* root, Node* n)
{
    if (root->value > n->value)
    {
        if (root->left)
            insert(root->left, n);
        else
            root->left = n;
    }
    else 
    {
        if (root->right)
            insert(root->right, n);
        else
            root->right = n;
    }
}

void createTree(Node* root, int level, int incr)
{
    if (incr > 0)
    {
        Node* n1 = new Node(level + incr);
        Node* n2 = new Node(level - incr);

        insert(root, n1);
        insert(root, n2);

        createTree(root, level + incr, incr/2);
        createTree(root, level - incr, incr/2);
    }
}

int main(int argc, char* argv[])
{
    Node* root = new Node(8);

    createTree(root, 8, 4);

    printInorder(root, 0);

    Node* min = NULL;
    Node* max = NULL;
    makeDLL2(root, min);

    cout << "----PRINT DLL FROM RIGHT TO LEFT-----------" << endl;
    Node *n = min;
    for (; n; n = n->left)
    {
        cout << n->value << "," << ((n->right) ? n->right->value : -1) << ":";
    }
    cout << endl << "-------------------" << endl;
}
