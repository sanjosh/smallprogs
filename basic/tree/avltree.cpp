/*

Karumanchi page 194

if (X->left) is NULL
    Predecessor(X) = first left ancestor
else
    Predecessor(X) = rightmost in left subtree

Same for Successor?

if (X->right) is NULL
    Successor(X) = first right ancestor
else
    Successor(X) = leftmost in right subtree
*/

#include <iostream>
using namespace std;

struct Node
{
    int data;
    int height;
    Node* left = nullptr;
    Node* right = nullptr;
};

void setMaxHeight(Node* n)
{
    int leftHeight = -1;
    int rightHeight = -1;
    if (n->left) leftHeight = n->left->height;
    if (n->right) rightHeight = n->right->height;

    n->height = max(leftHeight, rightHeight) + 1;
    //cout << "setting height of data=" << n->data << " at " << n->height << endl;
}

/*
     X               W
    /                 \
   W        ==>        X
    \                 /
     Wr              Wr
*/
Node* SingleRotateLeft(Node* X) // LL
{
    cout << "single rotate left at " << X->data << endl;
    Node* W = X->left;
    
    X->left = W->right;
    W->right = X;
    setMaxHeight(X);
    setMaxHeight(W);
    return W;
}

Node* SingleRotateRight(Node* X) // RR
{
    cout << "single rotate right at " << X->data << endl;
    Node* W = X->right;
    
    X->right = W->left;
    W->left = X;
    setMaxHeight(X);
    setMaxHeight(W);
    return W;
}


Node* DoubleRotateLeft(Node* Z) //LR
{
    cout << "double rotate left at " << Z->data << endl;
    Z->left = SingleRotateRight(Z->left);
    return SingleRotateLeft(Z);
}

Node* DoubleRotateRight(Node* Z) // RL
{
    cout << "double rotate right at " << Z->data << endl;
    Z->right = SingleRotateLeft(Z->right);
    return SingleRotateRight(Z);
}

Node* InsertAVLTree(Node* root, Node* parent, int data)
{
    if (!root)
    {
        root = new Node;
        root->height = 0;
        root->data = data;
        root->left = root->right = nullptr;
        return root;
    }
    else if (data < root->data)
    {
        root->left = InsertAVLTree(root->left, root, data);

        int leftHeight = -1;
        int rightHeight = -1;
        if (root->left) leftHeight = root->left->height;
        if (root->right) rightHeight = root->right->height;

        if (leftHeight - rightHeight >= 2)
            if (data < root->left->data)
                root = SingleRotateLeft(root);
            else
                root = DoubleRotateLeft(root);
    }
    else if (data > root->data)
    {
        root->right = InsertAVLTree(root->right, root, data);

        int leftHeight = -1;
        int rightHeight = -1;
        if (root->left) leftHeight = root->left->height;
        if (root->right) rightHeight = root->right->height;

        if (rightHeight - leftHeight >= 2)
            if (data > root->right->data)
                root = SingleRotateRight(root);
            else
                root = DoubleRotateRight(root);
    }
        
    setMaxHeight(root);
    return root;
}

void printInOrder (Node* n, int level)
{
    if (!n) return;
    printInOrder(n->left, level+1);
    int leftno = (n->left ? n->left->data : -1);
    int rightno = (n->right ? n->right->data : -1);
    cout << leftno << ":" << n->data << ":" << rightno << " of height=" << n->height << " at " << level << endl;
    printInOrder(n->right, level+1);
}


int main()
{
    Node* root = NULL;

    //for (int i = 0; i < 31; i ++)
    for (int i = 30; i >= 0; i --)
    {
        root = InsertAVLTree(root, NULL, i);
    }
    printInOrder(root, 0);
}

