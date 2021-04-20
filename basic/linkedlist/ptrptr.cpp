
#include <iostream>
#include <assert.h>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int d) : data(d)
    {
        next = NULL;
    }
};

struct List
{
    Node* head;
    List() {head = NULL; }
    
    int append(Node* n)
    {
        Node** pptr = &head;
        while (*pptr)
        {
            pptr = &((*pptr)->next);
        }
        assert(*pptr == NULL);
        *pptr = n;
    }

    void print(ostream& ostr)
    {
        Node* n = head;
        while (n)
        {
            cout << n->data << endl;
            n = n->next;
        }
    }
};

int main(int argc, char* argv[])
{
    List list;
    for (int i = 0; i < 10; i++)
    {
        Node* n = new Node(i);
        list.append(n);
    }
    list.print(cout);
}
