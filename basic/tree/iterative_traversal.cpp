
/*

inorder and preorder only push left on stack

=============


inorder : LDR

while 1
    while (n->left)
        s.push(n->left)
        n = n->left
    n = s.pop()
    PROCESS_HERE
    n = n->right

==============

preorder : DLR

while 1
    while (n)
        PROCESS_HERE
        s.push(n)
        s = s->left
    n = s.pop()  
    n = n->right

=============

postorder : LRD (each node visited twice - after left and after right)

while 1 
  
    if n
        s.push(n)
        n = n->left
    else
        if s.empty break
        if s.top->right == null
            n = s.pop
            if n == s.top->right (i.e. both subtrees of s.top are processed)
                s.pop
        if !s.empty
            n = s.top.right
        else 
            n = null

*/
