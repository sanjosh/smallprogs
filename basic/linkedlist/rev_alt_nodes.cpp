/*

http://www.geeksforgeeks.org/given-linked-list-reverse-alternate-nodes-append-end/

TODO : do it in O(1) space and one pass

http://ideone.com/HTkyDX

http://yougeeks.blogspot.in/2013/08/recursive-approach-to-reverse-singly.html


#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int d)  : data(d), next(NULL) {}
};

struct List
{
    Node* head;
    int count;

    List()
    {
        head = NULL;
        count = 0;
    }
    void insert(int d)
    {
        Node* n = new Node(d);        
        n->next = head;
        head = n;
        count ++;
    }
    void append(List& other)
    {
        Node* cur = head;
        while (cur)
        {
            if (!cur->next)
            {
                cur->next = other.head;
                count += other.count;
                other.head = NULL;
                other.count = 0;
            }
            cur = cur->next;
        }
        
    }
    void print()
    {
        Node* cur = head;
        while (cur)
        {
            cout << cur->data << endl;
            cur = cur->next;
        }
    }
    void rearrange(List& other)
    {
        if (count < 3) return;

        Node* cur = head;        
        Node* prev = NULL;
        int local = 0;

        while (cur)
        {
            local ++;
            Node* next_node = cur->next;
            if (local % 2 == 0)
            {
                prev->next = cur->next;    
                other.insert(cur->data);
            }
            prev = cur;
            if (local % 2 == 0)
            {
                delete cur;
            }
            cur = next_node;
        }

        prev->next = other.head;
    }
};

int main(int argc, char* argv[])
{
    List l1;
    for (int i = 10; i > 0; i--)
    {
        l1.insert(i);
    }
    cout << "before" << endl;
    l1.print();
    List other;
    l1.rearrange(other);
    l1.append(other);
    cout << "after" << endl;
    l1.print();
    cout << "other" << endl;
    other.print();
}

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
