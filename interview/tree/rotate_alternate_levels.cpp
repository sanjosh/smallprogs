
/*
Q2- Rotate the alternate levels of a binary tree.

Input:
                     1                             
                  /     \                    
                 2       3                  
               /   \   /   \
              4    5  6     7 
             /    / \      / \    
            8    11  10   12  13 
Output:

                     1                             
                  /     \                    
                 3       2                  
               /   \   /   \
              6    7  4     5 
                 /  \  \  /   \  
                13   12 8  11  10

First he asked to do it without recursion and then with recursion. O(n) time complexity.
*/


void Rotate(Node* n, int level)
{
    if (level & 0x01)
    {
        Node* tmp = n->left;
        n->left = n->right;
        n->right = tmp;
    }
    Rotate(n->left, level + 1);
    Rotate(n->right, level + 1);
}
