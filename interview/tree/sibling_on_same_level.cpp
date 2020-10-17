
Given a binary tree having 3 pointers, left, right and sibling out of which all the left and the right child pointers are already filled, you need to fill the sibling pointers with the addresses of the next node on the same level. If it is the last node of a level, fill NULL.

I first told him an approach using a level order traversal with a queue. Then he asked me to do it without a queue using recursion. I told him the approach and when he was satisfied, he asked me to write a code on paper with all the corner cases covered.

create linked list of sibling ptr 

TODO

Traverse(Node* node, Node* head)
{
    head->sibling = node->left;

    Traverse(node->left, NULL);

    head = node->left->sibling;
    node->left->sibling = node->right;

    Traverse(node->right, head);
}

void SetSibling(Node* node)
{
    if (!node) return;

    Node* l = node->left;
    Node* r = node->right;

    SetSibling(l);
    SetSibling(r);

    while (l && r)
    {
        l->sibling = r;
        l = l->right;
        r = r->left;
    }
}


http://www.geeksforgeeks.org/connect-nodes-at-same-level/

void connectRecur(struct node* p)
{
      // Base case
      if (!p) return;
      
      // Set the nextRight pointer for p's left child
      if (p->left)
        p->left->nextRight = p->right;
      
      // Set the nextRight pointer for p's right child
      // p->nextRight will be NULL if p is the right most child at its level
      if (p->right)
        p->right->nextRight = (p->nextRight)? p->nextRight->left: NULL;
      
      // Set nextRight for other nodes in pre order fashion
      connectRecur(p->left);
      connectRecur(p->right);
}

//http://www.geeksforgeeks.org/connect-nodes-at-same-level-with-o1-extra-space/

void connectRecur(struct node* p);
struct node *getNextRight(struct node *p);
 
// Sets the nextRight of root and calls connectRecur() for other nodes
void connect (struct node *p)
{
    // Set the nextRight for root
    p->nextRight = NULL;
 
    // Set the next right for rest of the nodes (other than root)
    connectRecur(p);
}
 
/* Set next right of all descendents of p. This function makes sure that
nextRight of nodes ar level i is set before level i+1 nodes. */
void connectRecur(struct node* p)
{
    // Base case
    if (!p)
       return;
 
    /* Before setting nextRight of left and right children, set nextRight
    of children of other nodes at same level (because we can access
    children of other nodes using p's nextRight only) */
    if (p->nextRight != NULL)
       connectRecur(p->nextRight);
 
    /* Set the nextRight pointer for p's left child */
    if (p->left)
    {
       if (p->right)
       {
           p->left->nextRight = p->right;
           p->right->nextRight = getNextRight(p);
       }
       else
           p->left->nextRight = getNextRight(p);
 
       /* Recursively call for next level nodes.  Note that we call only
       for left child. The call for left child will call for right child */
       connectRecur(p->left);
    }
 
    /* If left child is NULL then first node of next level will either be
      p->right or getNextRight(p) */
    else if (p->right)
    {
        p->right->nextRight = getNextRight(p);
        connectRecur(p->right);
    }
    else
       connectRecur(getNextRight(p));
}
 
/* This function returns the leftmost child of nodes at the same level as p.
   This function is used to getNExt right of p's right child
   If right child of p is NULL then this can also be used for the left child */
struct node *getNextRight(struct node *p)
{
    struct node *temp = p->nextRight;
 
    /* Traverse nodes at p's level and find and return
       the first node's first child */
    while(temp != NULL)
    {
        if(temp->left != NULL)
            return temp->left;
        if(temp->right != NULL)
            return temp->right;
        temp = temp->nextRight;
    }
 
    // If all the nodes at p's level are leaf nodes then return NULL
    return NULL;
}

// ITERATIVE

/* This function returns the leftmost child of nodes at the same level as p.
   This function is used to getNExt right of p's right child
   If right child of is NULL then this can also be sued for the left child */

struct node *getNextRight(struct node *p)
{
    struct node *temp = p->nextRight;
 
    /* Traverse nodes at p's level and find and return
       the first node's first child */
    while (temp != NULL)
    {
        if (temp->left != NULL)
            return temp->left;
        if (temp->right != NULL)
            return temp->right;
        temp = temp->nextRight;
    }
 
    // If all the nodes at p's level are leaf nodes then return NULL
    return NULL;
}
 
/* Sets nextRight of all nodes of a tree with root as p */
void connect(struct node* p)
{
    struct node *temp;
 
    if (!p)
      return;
 
    // Set nextRight for root
    p->nextRight = NULL;
 
    // set nextRight of all levels one by one
    while (p != NULL)
    {
        struct node *q = p;
 
        /* Connect all childrem nodes of p and children nodes of all other nodes
          at same level as p */
        while (q != NULL)
        {
            // Set the nextRight pointer for p's left child
            if (q->left)
            {
                // If q has right child, then right child is nextRight of
                // p and we also need to set nextRight of right child
                if (q->right)
                    q->left->nextRight = q->right;
                else
                    q->left->nextRight = getNextRight(q);
            }
 
            if (q->right)
                q->right->nextRight = getNextRight(q);
 
            // Set nextRight for other nodes in pre order fashion
            q = q->nextRight;
        }
 
        // start from the first node of next level
        if (p->left)
           p = p->left;
        else if (p->right)
           p = p->right;
        else
           p = getNextRight(p);
    }
}
