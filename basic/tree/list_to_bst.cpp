

// karumanchi 7.58 problem
//
TreeNode* SortedListToBST(ListNode*& listNode, int start, int end)
{
    if (start > end) return NULL;

    int mid = start + (end-start)/2;

    TreeNode* leftChild = SortedListToBST(listNode, start, mid - 1);

    TreeNode* parent = new TreeNode;
    parent->data = list->data;
    parent->left = leftChild;

    listNode = listNode->next;

    parent->right = SortedListToBST(listNode, mid+1, end);

    return parent;
}

TreeNode* SortedListToBST(ListNode* head, int n)
{
    return SortedListToBST(head, 0, n-1);
}
