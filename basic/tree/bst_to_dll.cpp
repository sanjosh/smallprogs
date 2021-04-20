

/* convert bst to dll 
http://www.geeksforgeeks.org/in-place-convert-a-given-binary-tree-to-doubly-linked-list/

        a
    b        c 
  d   e    f   g
 h i j k  l m n o

d b e a f c g

insert b : d->right = b; b->left = d
insert e : 


e->left = b
e->right = parent(parent(b))

a->right = f
f->left = a

f->right = c

POST LDR
PRE DLR
IN LDR

do in order traversal

*/

/* This is the core function to convert Tree to list. This function follows
  steps 1 and 2 of the above algorithm */
node* bintree2listUtil(node* root)
{
    // Base case
    if (root == NULL)
        return root;
 
    // Convert the left subtree and link to root
    if (root->left != NULL)
    {
        // Convert the left subtree
        node* l = bintree2listUtil(root->left);
 
        // Find inorder predecessor. After this loop, left
        // will point to the inorder predecessor
        for (; l->right!=NULL; l=l->right);
 
        // Make root as next of the predecessor
        l->right = root;
 
        // Make predecssor as previous of root
        root->left = l;
    }
 
    // Convert the right subtree and link to root
    if (root->right!=NULL)
    {
        // Convert the right subtree
        node* r = bintree2listUtil(root->right);
 
        // Find inorder successor. After this loop, right
        // will point to the inorder successor
        for (; r->left!=NULL; r = r->left);
 
        // Make root as previous of successor
        r->left = root;
 
        // Make successor as next of root
        root->right = r;
    }
 
    return root;
}
 

/*
std::queue<Node*> que;

void inorder(Node* n, que& q)
{
    if (n == NULL) return;
    inorder(n->left, q);
    q.push_back(n);
    inorder(n->right, q);
}

int main(int argc, char* argv[])
{
    que q;
    inorder(root, q);
    que::const_iterator iter;
    for (iter = q.begin(); iter != q.end(); ++q)
    {
        Node* n = q.front();    
        q.pop_front();
    }
}
*/
