
// Given a tree construct a mirror tree and return root of mirror tree.

Do it without recursion
http://www.careercup.com/question?id=6721875

// Mirror of binary tree without recursion is done
// using a stack and then basically do a DFS
void MirrorWithoutRecursion(Node * tree)
{
    if (!tree)
        return;

    Stack s;
    s.push(tree);
    while(!s.empty())
    {
        Node * current = s.pop();
        
        // Swap the children
        //
        Node * temp = current->right;
        current->right = current->left;
        current->left = temp;

        // Push the children on the stack
        //
        if (current->right)
            s.push(current->right);

        if (current->left)
            s.push(current->left);
    }
}

build a mirror version of new tree in the following way: with 2 stacks

public static TreeNode mirrorCopy(TreeNode root){
        if(root == null){
            return null;
        }
        
        Stack<TreeNode> stack = new Stack<TreeNode>();
        Stack<TreeNode> newStack = new Stack<TreeNode>();
        stack.push(root);
        TreeNode newRoot = new TreeNode(root.val);
        newStack.push(newRoot);
        
        while( !stack.isEmpty() ){
            TreeNode cur = stack.pop();
            TreeNode newCur = newStack.pop();
            
            if(cur.right != null){
                stack.push(cur.right);
                newCur.left = new TreeNode(cur.right.val);
                newStack.push(newCur.left);
            }
            if(cur.left != null){
                stack.push(cur.left);
                newCur.right = new TreeNode(cur.left.val);
                newStack.push(newCur.right);
            }
        }
        
        return newRoot;
    }

http://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/

Mirror of a Tree: Mirror of a Binary Tree T is another Binary Tree M(T) with left and right children of all non-leaf nodes interchanged.

MirrorTree1
Trees in the below figure are mirror of each other

Algorithm - Mirror(tree):

(1)  Call Mirror for left-subtree    i.e., Mirror(left-subtree)
(2)  Call Mirror for right-subtree  i.e., Mirror(left-subtree)
(3)  Swap left and right subtrees.
          temp = left-subtree
          left-subtree = right-subtree
          right-subtree = temp

Program:
#include<stdio.h>
#include<stdlib.h>
 
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node
{
    int data;
    struct node* left;
    struct node* right;
};
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
 
{
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
   
  return(node);
}
 
 
/* Change a tree so that the roles of the  left and
    right pointers are swapped at every node.
 
 So the tree...
       4
      / \
     2   5
    / \
   1   3
 
 is changed to...
       4
      / \
     5   2
        / \
       3   1
*/
void mirror(struct node* node)
{
  if (node==NULL)
    return; 
  else
  {
    struct node* temp;
     
    /* do the subtrees */
    mirror(node->left);
    mirror(node->right);
 
    /* swap the pointers in this node */
    temp        = node->left;
    node->left  = node->right;
    node->right = temp;
  }
}
 
 
/* Helper function to test mirror(). Given a binary
   search tree, print out its data elements in
   increasing sorted order.*/
void inOrder(struct node* node)
{
  if (node == NULL)
    return;
   
  inOrder(node->left);
  printf("%d ", node->data);
 
  inOrder(node->right);
} 
 
 
/* Driver program to test mirror() */
int main()
{
  struct node *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);
   
  /* Print inorder traversal of the input tree */
  printf("\n Inorder traversal of the constructed tree is \n");
  inOrder(root);
   
  /* Convert tree to its mirror */
  mirror(root);
   
  /* Print inorder traversal of the mirror tree */
  printf("\n Inorder traversal of the mirror tree is \n"); 
  inOrder(root);
   
  getchar();
  return 0; 
}

Time & Space Complexities: This program is similar to traversal of tree space and time complexities will be same as Tree traversal (Please see our Tree Traversal post for details)


