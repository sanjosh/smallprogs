
# techniques 

1. traversal : pass ptr to modify in stack if computing min/max across all nodes (e.g. max node value)
2. traversal : return as value from function if you have to compare left and right (e.g. distance between nodes)
3. traversal : pass by value if child is going to add to it (e.g. print path to all leafs)
4. increment before passing to parent
5. detect leaf condition : nullptr


# Inorder preorder postorder 

inorder_predecessor
```
	if x->left is null
		predecessor(x) = leftmost ancestor up the tree (ancestor->right->left->left = me)
	else
		predecessor(x) = rightmost in left subtree (me->left->right->right = pred)
```

https://www.geeksforgeeks.org/inorder-succesor-node-binary-tree/
		
https://www.geeksforgeeks.org/populate-inorder-successor-for-all-nodes/

https://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/

FULL tree = every node has 0 or 2 nodes  

such a tree can be constructed from preorder + postorder

inorder + preorder/postorder uniquely identify a tree

postorder - use to delete a tree (LRD)

preorder - use to create copy of tree (DLR)

# serialize a tree   

do preorder; output 0 if null encountered; output 1 and node if data

https://www.geeksforgeeks.org/serialize-deserialize-binary-tree/

# non-recursive traversal

threading - Morris traversal

Add threading pointers

no stack required if parent ptr exists

# Views

* left view - bfs OR recursive with global cur_level variable
* right view - recursive but right subtree first
* top view - vertical traversal
* bottom view - vertical traversal
* boundary view -

```
{
	if (root->left)
	else if (root->right)
}
```

* left boundary - if left print else print right

* diagonal view

# find if property satisfied

https://www.geeksforgeeks.org/change-a-binary-tree-so-that-every-node-stores-sum-of-all-nodes-in-left-subtree/

max sum between nodes - left and right subtree

print nodes at distance k - look up and down
```
{
	if root = this
	  print nodes down at distance k
	if dist = found in left subtree
		look for dist - cur in right subtree (including cur)
	if dist = found in right subtree
	  look in left
}
```

https://www.geeksforgeeks.org/find-distance-between-two-nodes-of-a-binary-tree/

find kth smallest elem

# Ancestors

https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

Lowest Common Ancestor - return node if key found; if both found

http://www.geeksforgeeks.org/sqrt-square-root-decomposition-set-2-lca-tree-osqrth-time/

http://www.geeksforgeeks.org/find-lca-in-binary-tree-using-rmq/

The LCA of nodes 4 and 9 is node 2, which happens to be the node closest 
to the root amongst all those encountered between the visits of 4 and 9 
during an Euler tour of T. 

http://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/

http://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-tree-set-2-using-parent-pointer/

http://www.geeksforgeeks.org/lca-for-general-or-n-ary-trees-sparse-matrix-dp-approach-onlogn-ologn/


# Properties 

Balance the tree

Diameter

Print paths


# BST to DLL

subtree returns min, max
http://www.geeksforgeeks.org/in-place-convert-a-given-binary-tree-to-doubly-linked-list/

http://www.geeksforgeeks.org/convert-a-given-binary-tree-to-doubly-linked-list-set-2/

TRICK use inorder - keep global prev variable 
http://www.geeksforgeeks.org/convert-given-binary-tree-doubly-linked-list-set-3/

reverse inorder - 
http://www.geeksforgeeks.org/convert-a-given-binary-tree-to-doubly-linked-list-set-4/

# DLL to BST

Build tree given inorder + preorder/postorder

# Clone

Clone tree with random ptr

# Traversal

During BFS, Change in level signaled by
1. inserting null ptr into bfs queue
2. augmenting bfs queue node with level number
3. noting queue size at start of while loop

# Modify

Connect nodes at same level
```
if (root->left)
  root->left->next = root->right

if (root->right)
  root->right->next = root->next->left
```

merge two AVL trees

convert to DLL; merge  and then rebuild

https://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/


Heavy light decomposition

https://www.geeksforgeeks.org/heavy-light-decomposition-set-2-implementation/

# Fenwick

Fenwick tree for prefix sum/CDF - Log(N) for update and add

represent index by powers of 2

parent(i) = i - i & (-i)

every node stores sum of n elem where n = power of 2

sparse vectors of FST - use double array trie

# binary search

binary search - avoid overflow for large low & high
```
int mid = low + (high - low) / 2 
instead of
int mid = low + high/2
```
