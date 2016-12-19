#pragma once 


typedef struct Stack{
    Bignumber *number;
    struct Stack *next_number;
    char sign;
} Stack;

void free_stack(Stack *head);
void push(Stack **head, Bignumber *bignumber );
Bignumber *pop(Stack **head);