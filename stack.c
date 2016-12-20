#include <stdlib.h> 
#include <stdio.h>
#include "big_number.h"
#include "stack.h"

void free_stack(Stack *head)
{
    Stack *tmp = NULL;
    while((tmp = head))
    {
        head = head -> next_number;
        free_list((tmp->number));
        free(tmp);
    }
    //free(tmp);
}
void push(Stack **head, Bignumber *bignumber )
{
     Stack *tmp = (Stack*)malloc(sizeof(Stack));
     tmp -> number = bignumber;
     if(*head == NULL)
     {
         *head = tmp;
         tmp -> next_number = NULL;
     }
     else
     {
      tmp -> next_number = *head;
      *head = tmp;
     }

}
Bignumber *pop(Stack **head)
{
    Bignumber *retval = NULL;
    Stack * next_node = NULL;

    next_node = (*head)->next_number;
    retval = (*head)->number;
    free((*head));
    *head = next_node;
    return retval;	

}