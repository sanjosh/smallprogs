
//Floyd’s Cycle-Finding Algorithm:
//This is the fastest method. Traverse linked list using two pointers.  Move one pointer by one and other pointer by two.  If these pointers meet at some node then there is a loop.  If pointers do not meet then linked list doesn’t have loop.
//
//Implementation of Floyd’s Cycle-Finding Algorithm:
#include<stdio.h>
#include<stdlib.h>
 
/* Link list node */
struct node
{
  int data;
  struct node* next;
};
 
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
 
int detectloop(struct node *list)
{
  struct node  *slow_p = list, *fast_p = list;
 
  while(slow_p && fast_p &&
          fast_p->next )
  {
    slow_p = slow_p->next;
    fast_p  = fast_p->next->next;
    if (slow_p == fast_p)
    {
       printf("Found Loop");
       return 1;
    }
  }
  return 0;
}
 
/* Drier program to test above function*/
int main()
{
  /* Start with the empty list */
  struct node* head = NULL;
 
  push(&head, 20);
  push(&head, 4);
  push(&head, 15);
  push(&head, 10);
 
  /* Create a loop for testing */
  head->next->next->next->next = head;
  detectloop(head);
 
  getchar();
}

// HOW TO REMOVE LOOP

http://stackoverflow.com/questions/24585129/how-the-loops-are-removed-from-link-list

1) Detect Loop using Floyd’s Cycle detection algo and get the pointer to a loop 
   node.
2) Count the number of nodes in loop. Let the count be k.
3) Fix one pointer to the head and another to kth node from head.
4) Move both pointers at the same pace, they will meet at loop starting node.
5) Get pointer to the last node of loop and make next of it as NULL.

e.g. of your case: 1->2->3->4->5->6->7->8->9->4

1) Loop verified by Floyd's cycle detection algo.
2) count of nodes in loop = 6
3) head->1, p->7 (6th node from head)
4) Loop while head!=p head=head->next and p=p->next. Both will meet at node 4
5) p=p->next Loop while(p->next!=head) p=p->next;
   Put p->next=NULL after termination of above loop. Your new list will be 1->2->3->`

http://en.wikipedia.org/wiki/Cycle_detection#Tortoise_and_hare

http://stackoverflow.com/questions/11669082/floyd-loop-detection-algorithm-with-different-step-size
