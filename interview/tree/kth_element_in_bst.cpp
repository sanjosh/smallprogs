
TODO http://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/

Given root of binary search tree and K as input, find K-th smallest element in BST.

For example, in the following BST, if k = 3, then output should be 10, and if k = 5, then output should be 14.

Method 1: Using Inorder Traversal.

Inorder traversal of BST retrieves elements of tree in the sorted order. The inorder traversal uses stack to store to be explored nodes of tree (threaded tree avoids stack and recursion for traversal, see this post). The idea is to keep track of popped elements which participate in the order statics. Hypothetical algorithm is provided below,

Time complexity: O(n) where n is total nodes in tree..

Algorithm:

/* initialization */
pCrawl = root
set initial stack element as NULL (sentinal)

/* traverse upto left extreme */
while(pCrawl is valid )
   stack.push(pCrawl)
   pCrawl = pCrawl.left

/* process other nodes */
while( pCrawl = stack.pop() is valid )
   stop if sufficient number of elements are popped.
   if( pCrawl.right is valid )
      pCrawl = pCrawl.right
      while( pCrawl is valid )
         stack.push(pCrawl)
         pCrawl = pCrawl.left

Implementation:
#include <stdio.h>
#include <stdlib.h>
 
#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])
 
/* just add elements to test */
/* NOTE: A sorted array results in skewed tree */
int ele[] = { 20, 8, 22, 4, 12, 10, 14 };
 
/* same alias */
typedef struct node_t node_t;
 
/* Binary tree node */
struct node_t
{
    int data;
 
    node_t* left;
    node_t* right;
};
 
/* simple stack that stores node addresses */
typedef struct stack_t stack_t;
 
/* initial element always NULL, uses as sentinal */
struct stack_t
{
    node_t*  base[ARRAY_SIZE(ele) + 1];
    int      stackIndex;
};
 
/* pop operation of stack */
node_t *pop(stack_t *st)
{
    node_t *ret = NULL;
 
    if( st && st->stackIndex > 0 )
    {
        ret = st->base[st->stackIndex];
        st->stackIndex--;
    }
 
    return ret;
}
 
/* push operation of stack */
void push(stack_t *st, node_t *node)
{
    if( st )
    {
        st->stackIndex++;
        st->base[st->stackIndex] = node;
    }
}
 
/* Iterative insertion
   Recursion is least preferred unless we gain something
*/
node_t *insert_node(node_t *root, node_t* node)
{
    /* A crawling pointer */
    node_t *pTraverse = root;
    node_t *currentParent = root;
 
    // Traverse till appropriate node
    while(pTraverse)
    {
        currentParent = pTraverse;
 
        if( node->data < pTraverse->data )
        {
            /* left subtree */
            pTraverse = pTraverse->left;
        }
        else
        {
            /* right subtree */
            pTraverse = pTraverse->right;
        }
    }
 
    /* If the tree is empty, make it as root node */
    if( !root )
    {
        root = node;
    }
    else if( node->data < currentParent->data )
    {
        /* Insert on left side */
        currentParent->left = node;
    }
    else
    {
        /* Insert on right side */
        currentParent->right = node;
    }
 
    return root;
}
 
/* Elements are in an array. The function builds binary tree */
node_t* binary_search_tree(node_t *root, int keys[], int const size)
{
    int iterator;
    node_t *new_node = NULL;
 
    for(iterator = 0; iterator < size; iterator++)
    {
        new_node = (node_t *)malloc( sizeof(node_t) );
 
        /* initialize */
        new_node->data   = keys[iterator];
        new_node->left   = NULL;
        new_node->right  = NULL;
 
        /* insert into BST */
        root = insert_node(root, new_node);
    }
 
    return root;
}
 
node_t *k_smallest_element_inorder(stack_t *stack, node_t *root, int k)
{
    stack_t *st = stack;
    node_t *pCrawl = root;
 
    /* move to left extremen (minimum) */
    while( pCrawl )
    {
        push(st, pCrawl);
        pCrawl = pCrawl->left;
    }
 
    /* pop off stack and process each node */
    while( pCrawl = pop(st) )
    {
        /* each pop operation emits one element
           in the order
        */
        if( !--k )
        {
            /* loop testing */
            st->stackIndex = 0;
            break;
        }
 
        /* there is right subtree */
        if( pCrawl->right )
        {
            /* push the left subtree of right subtree */
            pCrawl = pCrawl->right;
            while( pCrawl )
            {
                push(st, pCrawl);
                pCrawl = pCrawl->left;
            }
 
            /* pop off stack and repeat */
        }
    }
 
    /* node having k-th element or NULL node */
    return pCrawl;
}
 
/* Driver program to test above functions */
int main(void)
{
    node_t* root = NULL;
    stack_t stack = { {0}, 0 };
    node_t *kNode = NULL;
 
    int k = 5;
 
    /* Creating the tree given in the above diagram */
    root = binary_search_tree(root, ele, ARRAY_SIZE(ele));
 
    kNode = k_smallest_element_inorder(&stack, root, k);
 
    if( kNode )
    {
        printf("kth smallest elment for k = %d is %d", k, kNode->data);
    }
    else
    {
        printf("There is no such element");
    }
 
    getchar();
    return 0;
}

Method 2: Augmented  Tree Data Structure.

The idea is to maintain rank of each node. We can keep track of elements in a subtree of any node while building the tree. Since we need K-th smallest element, we can maintain number of elements of left subtree in every node.

Assume that the root is having N nodes in its left subtree. If K = N + 1, root is K-th node. If K < N, we will continue our search (recursion) for the Kth smallest element in the left subtree of root. If K > N + 1, we continue our search in the right subtree for the (K – N – 1)-th smallest element. Note that we need the count of elements in left subtree only.

Time complexity: O(n) where n is total nodes in tree.

Algorithm:

start:
if K = root.leftElement + 1
   root node is the K th node.
   goto stop
else if K > root.leftElements
   K = K - (root.leftElements + 1)
   root = root.right
   goto start
else
   root = root.left
   goto srart

stop:

Implementation:
#include <stdio.h>
#include <stdlib.h>
 
#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])
 
typedef struct node_t node_t;
 
/* Binary tree node */
struct node_t
{
    int data;
    int lCount;
 
    node_t* left;
    node_t* right;
};
 
/* Iterative insertion
   Recursion is least preferred unless we gain something
*/
node_t *insert_node(node_t *root, node_t* node)
{
    /* A crawling pointer */
    node_t *pTraverse = root;
    node_t *currentParent = root;
 
    // Traverse till appropriate node
    while(pTraverse)
    {
        currentParent = pTraverse;
 
        if( node->data < pTraverse->data )
        {
            /* We are branching to left subtree
               increment node count */
            pTraverse->lCount++;
            /* left subtree */
            pTraverse = pTraverse->left;
        }
        else
        {
            /* right subtree */
            pTraverse = pTraverse->right;
        }
    }
 
    /* If the tree is empty, make it as root node */
    if( !root )
    {
        root = node;
    }
    else if( node->data < currentParent->data )
    {
        /* Insert on left side */
        currentParent->left = node;
    }
    else
    {
        /* Insert on right side */
        currentParent->right = node;
    }
 
    return root;
}
 
/* Elements are in an array. The function builds binary tree */
node_t* binary_search_tree(node_t *root, int keys[], int const size)
{
    int iterator;
    node_t *new_node = NULL;
 
    for(iterator = 0; iterator < size; iterator++)
    {
        new_node = (node_t *)malloc( sizeof(node_t) );
 
        /* initialize */
        new_node->data   = keys[iterator];
        new_node->lCount = 0;
        new_node->left   = NULL;
        new_node->right  = NULL;
 
        /* insert into BST */
        root = insert_node(root, new_node);
    }
 
    return root;
}
 
int k_smallest_element(node_t *root, int k)
{
    int ret = -1;
 
    if( root )
    {
        /* A crawling pointer */
        node_t *pTraverse = root;
 
        /* Go to k-th smallest */
        while(pTraverse)
        {
            if( (pTraverse->lCount + 1) == k )
            {
                ret = pTraverse->data;
                break;
            }
            else if( k > pTraverse->lCount )
            {
                /*  There are less nodes on left subtree
                    Go to right subtree */
                k = k - (pTraverse->lCount + 1);
                pTraverse = pTraverse->right;
            }
            else
            {
                /* The node is on left subtree */
                pTraverse = pTraverse->left;
            }
        }
    }
 
    return ret;
}
 
/* Driver program to test above functions */
int main(void)
{
    /* just add elements to test */
    /* NOTE: A sorted array results in skewed tree */
    int ele[] = { 20, 8, 22, 4, 12, 10, 14 };
    int i;
    node_t* root = NULL;
 
    /* Creating the tree given in the above diagram */
    root = binary_search_tree(root, ele, ARRAY_SIZE(ele));
 
    /*  It should print the sorted array */
    for(i = 1; i <= ARRAY_SIZE(ele); i++)
    {
        printf("\n kth smallest elment for k = %d is %d",
                 i, k_smallest_element(root, i));
    }
 
    getchar();
    return 0;
}

Thanks to Venki for providing post. Please write comments if you find anything incorrect, or you want to share more information about the topic discussed above.
