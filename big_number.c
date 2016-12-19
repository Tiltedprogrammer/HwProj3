#include <stdio.h>
#include <stdlib.h>
#include "big_number.h"
Node *new_Node(char c)
{
	Node *new_node = (Node*)malloc(sizeof(Node));
	if(!new_node)
	{
		printf("Error occured while allocating");
		exit(0);
	}
	new_node -> digit = c;
	new_node -> next_node = NULL;
	new_node -> prev_node = NULL;
	return new_node;
} 
Bignumber *new_Number()
{
	Bignumber *new_number = (Bignumber*)malloc(sizeof(Bignumber));
	if(!new_number)
	{
		printf("Error occured while allocating");
		exit(0) ;
	}
	new_number -> head = NULL;
	new_number -> tail = NULL;
	new_number -> size = 0;
	return new_number;
}
void add_to_b(Bignumber **head_ref, char c)
{
	Node *new_digit = new_Node(c);
	if(!(*head_ref) -> head )
	{
		(*head_ref) -> head = new_digit;
		(*head_ref) -> tail = (*head_ref) -> head;
		(*head_ref)->size++;
	}	
	else 
	{
		new_digit -> next_node = (*head_ref) -> head;
		(*head_ref) -> head-> prev_node = new_digit;
		(*head_ref) -> head = new_digit;
		(*head_ref)->size++;
	}

}
void add_to_e(Bignumber **tail_ref, char c)
{
	Node *new_digit = new_Node(c);
	if(!(*tail_ref) -> tail )
	{
		(*tail_ref) -> tail = new_digit;
		(*tail_ref) -> head = (*tail_ref) -> tail;	//}
		(*tail_ref)->size++;
	}	
	else 
	{
		new_digit -> prev_node = (*tail_ref) -> tail;
		(*tail_ref) -> tail-> next_node = new_digit;
		(*tail_ref) -> tail = new_digit;
		(*tail_ref)->size++;
	}
}
Bignumber *get_number(char c)
{
    Bignumber *number = new_Number();
    add_to_b(&number, c - '0');
    while(((c = fgetc(stdin)) >= '0') && (c <= '9'))
    {
        add_to_b(&number, c - '0');
    }
    return number;
}
void print_number(Bignumber *number)
{
	Node *cur = number -> tail;
	while(cur)
	{
		printf("%c", (cur -> digit + '0'));
		cur = cur -> prev_node;	

	}
	printf("\n");
}
void free_list(Bignumber **list)
{
	Node *tmp = NULL;
    while(tmp = (*list)->head)
    {
        (*list)->head = (*list) ->head->next_node;
        free(tmp);
    }
    free(*list);
}
void swap(Bignumber **f, Bignumber **s)
{
    Bignumber *tmp = NULL;
    tmp = *f;
    *f = *s;
    *s = tmp;

}   