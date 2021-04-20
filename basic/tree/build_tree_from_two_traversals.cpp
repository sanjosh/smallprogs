
/*
Problm 26 - p 152 Karumanchi

tree is 
    A
  B   C
 D E F

inorder = DBEAFC
pre     = ABDECF

leftmost(pre) = root
all elem left(root) in inorder become left subtree
all elem right(root) in inorder become right subtree

Step1: (0, 5) root = A; left = DBE; right = FC
Step2: (0,2) in inorder subtree DBE, root = B, left=D, right=E
Step3: (0,0) root=D
Step4: (2,2) root=E
Step5: (4,5) in inorder subtree FC, root=C, right=F (or other way round)
Step6: (5,5) root=F
    
*/

int preIndex = 0;
string inorder;
string preorder;

call BuildTree(0, n-1)

Node* BuildTree(int start, int end) // indices in inorder seq
{
    if (start > end) return NULL
    newNode = malloc
    newnode->data = preorder[preindex];
    preindex++
    if (start==end) return newNode

    int inIndex = search(inOrder, start, end, newNode->data);
    
    newNode->left = buildTree(start, inIndex - 1);
    newNode->right = buildTree(inIndex + 1, end);
    return newNode;
}

