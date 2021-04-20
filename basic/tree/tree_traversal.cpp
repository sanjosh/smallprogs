#include <iostream>
#include <errno.h>

Therefore, following combination can uniquely identify a tree.

Inorder and Preorder.
Inorder and Postorder.
Inorder and Level-order.

Preorder or Postorder give u root of tree at end
inorder gives u sequence

And following do not.
Postorder and Preorder.
Preorder and Level-order.
Postorder and Level-order.

using namespace std;

template <class T> class Tree;

template <class T>
class Node
{
    T data;
    size_t height;
    Node<T>* left;
    Node<T>* right;

    public:

    Node(const T& inData) : data(inData)
    {
        left = right = NULL;
        height = 1;
    }

    friend class Tree<T>;

    // REMEMBER PRED - POL
    // PRE - D
    void printPreorder(ostream& ostr)
    {
        ostr << data  << " at height=" << height << endl;
        if (this->left) this->left->printPreorder(ostr);
        if (this->right) this->right->printPreorder(ostr);
    }
    // IN 
    void printInorder(ostream& ostr)
    {
        if (this->left) this->left->printInorder(ostr);
        ostr << data  << " at height=" << height << endl;
        if (this->right) this->right->printInorder(ostr);
    }
    // POST AL
    void printPostorder(ostream& ostr)
    {
        if (this->left) this->left->printPostorder(ostr);
        if (this->right) this->right->printPostorder(ostr);
        ostr << data  << " at height=" << height << endl;
    }
};


template <class T>
class Tree
{
    Node<T>* root;

    public:

    Tree()
    {
        root = NULL;
    }

    enum TURN { left, right } ;
    enum ORDER { INORDER, PREORDER, POSTORDER } ;

    int insert(T& data)
    {
        if (root == NULL)
        {
            root = new Node<T>(data);
            return 0;
        }

        TURN turn;
        Node<T>* prev = NULL;
        Node<T>* node = root;

        while (node != NULL)    
        {
            prev = node;
            if (node->data > data) 
            {
                turn = left;
                node =  node->left;
            }
            else if (node->data < data) 
            {
                turn = right;
                node = node->right;
            }
            else 
            {
                return -EEXIST; 
            }
        }
        if (turn == left)
        {
            prev->left = new Node<T>(data);
            cout << "inserted " << data << " to left of " << prev->data << endl;
        }     
        else
        {
            prev->right = new Node<T>(data);
            cout << "inserted " << data << " to right of " << prev->data << endl;
        }
        return 0;
    }

    void print(ostream& ostr, ORDER type)
    {
        Node<T>* node = root; 
        cout << "start =====================" << type << endl;
        if (!root) return ;
        switch(type)
        {
            case INORDER:
                root->printInorder(ostr);
                break;
            case PREORDER:
                root->printPreorder(ostr);
                break;
            case POSTORDER:
                root->printPostorder(ostr);
                break;
            default:
                cout << "what ?" << endl; 
        }
        cout << "end =====================" << type << endl;
    }
    void printLevel(ostream& ostr)
    {
    }
};


int main()
{
    Tree<int> aTree;
    for (int i = 0; i < 10; i++)
    {
        int data = i * 20;
        if (i % 2) data = data - 1000;
        int ret = aTree.insert(data);
        if (ret == 0)
        {
            cout << "insert " << data << " succeeded " << endl;
        }
    }
    aTree.print(cout, Tree<int>::INORDER);
    aTree.print(cout, Tree<int>::PREORDER);
    aTree.print(cout, Tree<int>::POSTORDER);
}

/* ------------ iterative ------------*/

inorder(Node* root)
{
    while (1)
    {
        while (root)
        {
            s.push(root);

            root = root->left
        }

        if s.isempty() 
            break

        root = s.pop();

        print root <===

        root = root->right
    }
}

preorder(Node* root)
{
    while (1)
    {
        while (root)
        {
            print root <===

            s.push(root);

            root = root->left
        }

        if s.isempty() 
            break

        root = s.pop();

        root = root->right
    }
}

postorder(Node* root)
{
    while (1)
    {
        if (root)
        {
            s.push(root)

            root = root->left
        }
        else
        {
            if s.isempty() break

            else if (s.top()->right == NULL)
            {
                root = s.pop()
                print root (LEFT LEAF)

                if (root = s.top->right)
                {
                    print root (RIGHT ELEM)
                    s.pop() - pop root elem
                }
            }

            if (s.isempty() == false)
                root = s.top->right
            else    
                root = null
        }
    }
}
