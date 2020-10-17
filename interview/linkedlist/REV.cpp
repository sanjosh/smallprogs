#include <iostream>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct Node
{
    Node* next;
    int value;

    Node(int val): value(val) { next = NULL; }
};

void reverseK(Node*& cur, int k, Node*& newhead)
{
        Node* prev = NULL;
        Node* next = NULL;
        Node* newtail = cur;

        while (cur && k)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;

            k--;
        }

        newtail->next = cur;
        newhead = prev;
        cur = newtail;
}

void traverseK(Node*& cur, int k)
{
    while (cur && k)
    {
        cur = cur->next;

        k--;
    }
}

int revKNodes(Node*& head, int k)
{
    Node* cur = head;
    Node** addrOfCur = &head;

    assert(k);

    while (cur)
    {
        Node* newhead = NULL;

        reverseK(cur, k, newhead);

        *addrOfCur = newhead;
        if (cur)
        {
            prev = cur;
            cur = cur->next;
        }

        traverseK(cur, k);

    }
}

void print(Node* head)
{
    while (head)
    {
        cout << head->value << " ";
        head = head->next;
    }        
    cout << endl;
}

int main(int argc, char* argv[])
{
    Node* head = NULL;

    for (int i = atoi(argv[1]); i >= 0; i--)
    {            
        Node* cur = new Node(i);
        cur->next= head;
        head = cur;
    }

    print(head);
    revKNodes(head, atoi(argv[2]));
    print(head);

}
