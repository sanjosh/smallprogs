
Flajolet Sedgewick analysis of Algo page 268:

For binary trees, nodes have either 2 or zero children.  if we list, for each node, one less than
the number of chuldren, then we get either +1/-1 which is +/-.  Thus a binary tree can be uniquely
represented as a string of +/- symbols.  The tree in preorder is "+++---+-++-+--++----".

Equivalent representations of binary tree
1) Parenthesis  - number of parenthesis equals number of nodes
2) Triangulations N-gon
3) Gambler Ruin sequences

http://stackoverflow.com/questions/2675756/efficient-array-storage-for-binary-tree

http://stackoverflow.com/questions/24727205/passing-binary-tree-on-a-network-with-minimum-space

is it BST or Binary Tree 
Will tree be height-balanced ?
what is range of nodes ?

1) pass preorder with null ptrs embedded
2) node at i index, child at (2i, 2i+1) entries;
3) pass difference between nodes 

traditionally, 2 orders - one of which is inorder requried to rebuilt tree uniquely

on other side, you follow algo "create tree from linked list"

==============

 I implemented an array-based approach where the children of node i (numbering in level-order traversal) were at the 2*i index for the left child and 2*i + 1 for the right child.

BST
http://leetcode.com/2010/09/saving-binary-search-tree-to-file.html
Preorder because Node's parent is output before node

Binary Tree
http://leetcode.com/2010/09/serializationdeserialization-of-binary.html

Store Preorder with null ptrs

void writeBinaryTree(BinaryTree *p, ostream &out) {
  if (!p) {
    out << "# ";
  } else {
    out << p->data << " ";
    writeBinaryTree(p->left, out);
    writeBinaryTree(p->right, out);
  }
}

Deserializing a Binary Tree:

Reading the binary tree from the file is similar. We read tokens one at a time using pre-order traversal. If the token is a sentinel, we ignore it. If the token is a number, we insert it to the current node, and traverse to its left child, then its right child.
void readBinaryTree(BinaryTree *&p, ifstream &fin) { int token; bool isNumber; if (!readNextToken(token, fin, isNumber)) return; if (isNumber) { p = new BinaryTree(token); readBinaryTree(p->left, fin); readBinaryTree(p->right, fin); } }
    
void readBinaryTree(BinaryTree *&p, ifstream &fin) {
  int token;
  bool isNumber;
  if (!readNextToken(token, fin, isNumber))
    return;
  if (isNumber) {
    p = new BinaryTree(token);
    readBinaryTree(p->left, fin);
    readBinaryTree(p->right, fin);
  }
}


http://stackoverflow.com/questions/2675756/efficient-array-storage-for-binary-tree/

===================

http://www.geeksforgeeks.org/serialize-deserialize-binary-tree/

// A C++ program to demonstrate serialization and deserialiation of
// Binary Tree
#include <stdio.h>
#define MARKER -1
 
/* A binary tree Node has key, pointer to left and right children */
struct Node
{
    int key;
    struct Node* left, *right;
};
 
/* Helper function that allocates a new Node with the
   given key and NULL left and right pointers. */
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return (temp);
}
 
// This function stores a tree in a file pointed by fp
void serialize(Node *root, FILE *fp)
{
    // If current node is NULL, store marker
    if (root == NULL)
    {
        fprintf(fp, "%d ", MARKER);
        return;
    }
 
    // Else, store current node and recur for its children
    fprintf(fp, "%d ", root->key);
    serialize(root->left, fp);
    serialize(root->right, fp);
}
 
// This function constructs a tree from a file pointed by 'fp'
void deSerialize(Node *&root, FILE *fp)
{
    // Read next item from file. If theere are no more items or next
    // item is marker, then return
    int val;
    if ( !fscanf(fp, "%d ", &val) || val == MARKER)
       return;
 
    // Else create node with this item and recur for children
    root = newNode(val);
    deSerialize(root->left, fp);
    deSerialize(root->right, fp);
}
 
// A simple inorder traversal used for testing the constructed tree
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}
 
/* Driver program to test above functions*/
int main()
{
    // Let us construct a tree shown in the above figure
    struct Node *root        = newNode(20);
    root->left               = newNode(8);
    root->right              = newNode(22);
    root->left->left         = newNode(4);
    root->left->right        = newNode(12);
    root->left->right->left  = newNode(10);
    root->left->right->right = newNode(14);
 
    // Let us open a file and serialize the tree into the file
    FILE *fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    serialize(root, fp);
    fclose(fp);
 
    // Let us deserialize the storeed tree into root1
    Node *root1 = NULL;
    fp = fopen("tree.txt", "r");
    deSerialize(root1, fp);
 
    printf("Inorder Traversal of the tree constructed from file:\n");
    inorder(root1);
 
    return 0;
}
