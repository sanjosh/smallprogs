
/*
TODO

#include<stdio.h>
#include<stdlib.h>
 
struct node
{
    int data;
    struct node* next;
};
 
static void reverse(struct node** head_ref)
{
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next; 
        current->next = prev;  
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
 
void push(struct node** head_ref, int new_data)
{
    struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
            
    new_node->data  = new_data;
                
    new_node->next = (*head_ref);   
        
    (*head_ref)    = new_node;
}

void printList(struct node *head)
{
    struct node *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);   
        temp = temp->next; 
    }
}   
 
int main()
{
    struct node* head = NULL;
   
     push(&head, 20);
     push(&head, 4);
     push(&head, 15);
     push(&head, 85);     
     
     printList(head);   
     reverse(&head);                     
     printf("\n Reversed Linked list \n");
     printList(head);   
     getchar();
}

void recursiveReverse(struct node** head_ref)
{
    struct node* first;
    struct node* rest;
      
    if (*head_ref == NULL)
       return;  
 
    first = *head_ref; 
    rest  = first->next;
 
    if (rest == NULL)
       return;  
 
    recursiveReverse(&rest);
    first->next->next  = first; 
     
    first->next  = NULL;         
 
    *head_ref = rest;             
}
*/



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
    
    void reverse()
    {
        Node* next = NULL;
        Node* prev = NULL;
        Node* cur = head;

        while (cur)
        {
            next = cur->next;    
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
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
    l1.reverse();
    cout << "after" << endl;
    l1.print();
}

