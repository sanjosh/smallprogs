/*

Reverse alternate nodes of a linked list

*/

#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;

    Node(int val) : value(val)
    {
        next = NULL;
    }
};

// merge 2 linked lists alternatively
void merge(Node* n1, Node* n2)
{
    Node* n1next = NULL;
    Node* n2next = NULL;

    while (n2 && n1)
    {
        n1next = n1->next;            
        n2next = n2->next;            

        n2->next = n1next;
        n1->next = n2;

        n2 = n2next;
        n1 = n1next;
    }        
}

// reverse a linked list
Node* reverse(Node* n1)
{
    Node* cur = n1;
    Node* prev = NULL;
    Node* next = NULL;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }        
    return prev;
}

// split a linked list into 2 lists by placing alternate nodes into different list
Node* divide(Node* n1)
{
    Node* cur = n1;
    Node* next = NULL;

    if (!cur) return NULL;

    Node* otherHead = cur->next; // retain head of the odd elem list 

    while (cur)
    {
        next = cur->next;
        cur->next = (cur->next ? cur->next->next : NULL); 
        cur = next;
    }
    return otherHead;
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

int main()
{
    Node* head = NULL;

    for (int i = 9; i >= 0; i--)
    {            
        Node* cur = new Node(i);
        cur->next= head;
        head = cur;
    }

    print(head);

    Node* otherHead = divide(head);
    otherHead = reverse(otherHead);
    merge(head, otherHead); 

    print(head);
}
