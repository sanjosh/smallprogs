
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

void reverseK(Node*& cur, Node*& prevPtr, int k)
{
        Node* prev = NULL;
        Node* next = NULL;
        Node* newtail = cur;

        if (!cur) return;

        while (cur && k)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;

            k--;
        }

        newtail->next = cur; // set tail ptr of new list
        prevPtr->next = prev; // link in the new head
        prevPtr = newtail; // set prev of cur
}

void traverseK(Node*& cur, Node*& prevPtr, int k)
{
    while (cur && k)
    {
        prevPtr = cur;
        cur = cur->next;
        k--;
    }
}

int revKNodes(Node*& head, int k)
{
    Node* cur = head;
    Node* prevPtr = NULL;

    assert(k > 1);

    while (cur)
    {
        traverseK(cur, prevPtr, k);
        reverseK(cur, prevPtr, k);
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
    // first arg is number of elem
    // second arg is how many nodes to reverse at once
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
