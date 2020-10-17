
#include<stdio.h>
#include<stdlib.h>
 
/* Link list node */
struct node
{
    int data;
    struct node* next;
};


/* Function to push a node */
void push(struct node** head_ref, int new_data)
{
    /* allocate node */
    struct node* new_node =
            (struct node*) malloc(sizeof(struct node));
            
    /* put in the data  */
    new_node->data  = new_data;
                
    /* link the old list off the new node */
    new_node->next = (*head_ref);   
        
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* Function to print linked list */
void printList(struct node *head)
{
    struct node *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);   
        temp = temp->next; 
    }
}   

void recursiveReverse(struct node** head_ref)
{
    struct node* first;
    struct node* rest;
      
    /* empty list */
    if (*head_ref == NULL)
       return;  
 
    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref; 
    rest  = first->next; // retain ptr to 2nd
 
    /* List has only one node */
    if (rest == NULL)
       return;  
 
    /* reverse the rest list and put the first element at the end */
    recursiveReverse(&rest);

    // rest is now head
    first->next->next  = first;  // 2nd last elem points to first
    first->next  = NULL;          // last elem points to null
 
    *head_ref = rest;             // head pts to last elem 
}
 
/* Drier program to test above function*/
int main()
{
    /* Start with the empty list */
    struct node* head = NULL;
   
     push(&head, 20);
     push(&head, 4);
     push(&head, 15);
     push(&head, 85);     
     
     printList(head);   
     recursiveReverse(&head);                     
     printf("\n Reversed Linked list \n");
     printList(head);   
     getchar();
}
