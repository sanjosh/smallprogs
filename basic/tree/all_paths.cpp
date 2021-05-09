
/*
print all paths from root to leaf
extend it to graph
http://www.careercup.com/question?id=5742219382226944

*/
#include <iostream>
using namespace std;

struct Node 
{
    char value;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(char val) : value(val) { }
};

void printpaths(const Node* n, const string& path)
{
    string localpath = path + ":" + n->value;
    if (!n->left && !n->right) { cout << localpath << endl; return; }

    if (n->left) printpaths(n->left, localpath);
    if (n->right) printpaths(n->right, localpath);
}

void printInorder (const Node* n, int level)
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
        Node* n1 = new Node(root->value + level + incr);
        Node* n2 = new Node(root->value + level - incr);

        insert(root, n1);
        insert(root, n2);

        createTree(root, level + incr, incr/2);
        createTree(root, level - incr, incr/2);
    }
}

int main(int argc, char* argv[])
{
    Node* root = new Node('j');

    createTree(root, 8, 4);

    printInorder(root, 0);

    string dmy;
    printpaths(root, dmy);
}
/*

graphs
for node in all_nodes:
    DFS(path, node) {
        print path
    if node in path:
        return
    for child in node.children:
        DFS(path+node, child)}
*/
