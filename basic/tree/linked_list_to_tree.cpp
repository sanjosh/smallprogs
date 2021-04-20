
Karumanchi Prob 58, p 184
TODO

bottom up algo

SortedListToBST(ListNode*& list, int start, int end)
{
    if (start > end) return nULL

    int mid = (start) + (end-start)/2
    left = SortedListTOBST(list, start, mid-1)

    parent = malloc
    parent->data = list->data
    parent->left = left;
    
    list = list->next
    parent->right = SortedListToBST(list, mid+1, end)
    
    return parent
}
