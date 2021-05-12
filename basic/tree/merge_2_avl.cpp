
/*
http://dhruvbird.blogspot.in/2014/01/merging-avl-trees.html

Problem Statement: Given two AVL trees T1 and T2, where the largest key in T1 is less than the smallest key in T2, 
Join(T1, T2) returns an AVL tree containing the union of the elements in T1 and T2. 
Give an algorithm (in pseudocode) for Join() that runs in time O(log n), where n is the size of the resulting AVL tree. 

Justify the correctness and efficiency of your algorithm.

Problem statement and solution stolen from these assignment solutions.

Solution: Begin by computing the heights h1 of T1 and h2 of T2. 
This takes time O(h1 + h2). 
You simply traverse a path from the root, going to left child if the balance factor is -1, to the right child if it is positive, 
and to any of the children if the balance factor is 0, until you reach a leaf. Assume that h1 > h2; the other case is symmetric.

Next, DELETE the smallest element x from T2, leaving T'2 of height h. This takes O(h2) time.

Find a node v on the rightmost path from the root of T1, whose height is either h or h + 1, as follows:

v = root(T1)
    h' = h1
    while h' > h + 1 do
      if balance factor(v) = -1
        then h' = h' - 2
        else h' = h' - 1
            v = right-child(v)


    This takes O(h1) time.

    The reason we choose a node with height h or h + 1 is because 
    if we are at a node of height h, and we move to its parent node, 
    then the height of the new (parent) node might increase by 2 (to h + 1), 
    since the sibling of node from which we moved up might have a height greater (by 1) than its sibling.

    Let u denote the parent of v.

    Form a new tree whose root contains the key x, whose left sub-tree is the sub-tree rooted at v and whose right sub-tree is T'2.

    Note that this is a valid binary search tree, since all the keys in the sub-tree rooted at v are in T1 and, hence, smaller than x, and, by construction, x is smaller than or equal to all elements in T'2. The balance factor of the root of this new tree is h - h' which is either -1 or 0, so this new tree is a valid AVL tree. The height of this new tree is h' + 1, which is 1 bigger than v's height. Let the root of this new tree be the right child of u, in place of v. Again, since all keys in this new tree are at least as big as u, this results in a valid binary search tree. This part of the construction takes constant time.

    Now, as in the INSERT algorithm, we go up the tree, starting at u, fixing balance factors and perhaps doing a rotation. This takes O(h1) time. Note that the correctness follows from the condition at u before this process is begun is a condition that can arise during the INSERT algorithm.

    Since h1, h2 ∈ O(log n), the total time taken by this algorithm is in O(log n). 

*/
