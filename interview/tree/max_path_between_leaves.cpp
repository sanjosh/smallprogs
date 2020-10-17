
SAME AS DIAMETER OF TREE

/*
http://www.geeksforgeeks.org/find-maximum-path-sum-two-leaves-binary-tree/
*/

int maxPathSumUtil(struct Node *root, int &res)
{
        // Base case
        if (root==NULL) return 0;
        //      
        // Find maximum sum in left and right subtree. Also find
        // maximum root to leaf sums in left and right subtrees
        // and store them in lLPSum and rLPSum
        int lLPSum = maxPathSumUtil(root->left, res);
        int rLPSum = maxPathSumUtil(root->right, res);
        
        // Find the maximum path sum passing through root
        int curr_sum = max((lLPSum+rLPSum+root->data), max(lLPSum, rLPSum));
        //                                    
        // Update res (or result) if needed
        if (res < curr_sum) res = curr_sum;
        
        // Return the maximum root to leaf path sum
        return max(lLPSum, rLPSum)+root->data;
}
        
// The main function which returns sum of the maximum
// sum path between two leaves.  This function mainly uses
// maxPathSumUtil()
int maxPathSum(struct Node *root)
{
    int res = 0;
    maxPathSumUtil(root, res);
    return res;
}
