
http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/

http://stackoverflow.com/questions/5502916/explain-morris-inorder-tree-traversal-without-using-stacks-or-recursion

            1
    2               3
  4   5           6   7

go to 2
link from 5->1
go to 4
link from 4->2
go to 3
link from 6->3


Karumanchi

Using Morris Traversal, we can traverse the tree without using stack and recursion. The idea of Morris Traversal is based on Threaded Binary Tree. In this traversal, we first create links to Inorder successor and print the data using these links, and finally revert the changes to restore original tree.

1. Initialize current as root 
2. While current is not NULL
   If current does not have left child
      a) Print current’s data
      b) Go to the right, i.e., current = current->right
   Else
      a) Make current as right child of the rightmost node in current's left subtree
      b) Go to this left child, i.e., current = current->left

Although the tree is modified through the traversal, it is reverted back to its original shape after the completion. Unlike Stack based traversal, no extra space is required for this traversal.


void MorrisTraversal(struct tNode *root)
{
  struct tNode *current,*pre;
 
  if(root == NULL)
     return;
 
  current = root;
  while(current != NULL)
  {                
    if(current->left == NULL)
    {
      printf(" %d ", current->data);
    // uses the threaded ptr inserted in  (1)
      current = current->right;     
    }   
    else
    {
      /* Find the inorder predecessor of current */
      pre = current->left;
      while(pre->right != NULL && pre->right != current)
        pre = pre->right;
 
      /* Make current as right child of its inorder predecessor */
      if(pre->right == NULL)
      {
        pre->right = current; // (1)
        current = current->left; // move down left subtree
      }
             
      /* Revert the changes made in if part to restore the original
        tree i.e., fix the right child of predecssor */   
      else  // pre->right = current
      {
        pre->right = NULL; // reset threaded ptr inserted in (1)
        printf(" %d ",current->data);
        current = current->right;      // go back to root 
      } /* End of if condition pre->right == NULL */
    } /* End of if condition current->left == NULL*/
  } /* End of while */
}

//////////////

