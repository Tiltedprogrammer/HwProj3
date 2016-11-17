#include "stdio.h"
#include "malloc.h"

typedef struct Bignumber{
	int digit;
	struct Bignumber *next_digit;
    int sign;
}Bignumber;

typedef struct Stack{
    Bignumber *number;
    struct Stack *next_number;
    char sign;
} Stack;

Bignumber *list_init()
{
    Bignumber *list = NULL;
    return list;
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

void free_list(Stack *head)
{
    Bignumber *cur = head->number;
    while(cur != NULL)
    {
        head->number = head->number-> next_digit;
        free(cur);
    }


}

Bignumber *pop(Stack **head)
{
    Stack *retval = NULL;
    Stack * next_node = NULL;

    if (*head == NULL) {
        printf("Piwev nahuy, stack pustoy");
        return NULL;
    }

    next_node = (*head)->next_number;
    retval = (*head);
    //free_list(*head);
    *head = next_node;

    return retval->number;

}

Bignumber *new_Number(int value)
{
    Bignumber *new_number = (Bignumber*)malloc(sizeof(Bignumber));
    new_number -> digit = value;
    new_number -> next_digit = NULL;
    return new_number;
}

void add_digit(Bignumber **head, int data) //adds the digit to the beginning of the list, to reverse the number;
{
    Bignumber *new_digit = new_Number(data);
    new_digit -> next_digit = *head; //our value is now linked to where the head was;
    *head = new_digit; //our value is head now;
}

Bignumber *sum_of(Bignumber *first, Bignumber *second)
{
    Bignumber *res = NULL;
    Bignumber *tmp, *prev = NULL;
    int carry = 0, sum;
    while(first != NULL || second != NULL)
    {
        sum = carry + (first? first->digit: 0) + (second? second->digit: 0);
        carry = (sum >= 10)? 1 : 0;
        sum = sum % 10;
        tmp = new_Number(sum);
        if(res==NULL)
        {
            res = tmp;
        }
        else
        {
            prev->next_digit = tmp;
        }
        prev = tmp;
        if(first) first = first -> next_digit;
        if(second) second = second -> next_digit;
    }
    if(carry > 0)
    {
        tmp -> next_digit = new_Number(carry);
    }
    return res;
}
Bignumber *number_input()
{

}
/**Bignumber multiply(Bignumber *first, Bignumber *second)
{
    Bignumber *res = NULL;
    Bignumber *tmp, *prev = NULL, *temp1, *buff;
    int carry = 0, multy;
    while(second)
    {
        temp1 = NULL;
        *first = first;
        while(first)
        {
            multy = (first -> digit)*(second -> digit);
            carry = (multy >= 10) ? multy / 10 : 0;
            multy = multy % 10;
            tmp = new_Number(multy);
        if(temp1==NULL)
        {
            temp1 = tmp;
        }
        else
        {
            prev->next_digit = tmp;
        }
        prev = tmp;
        if(first) first = first -> next_digit;

        }
        if(carry > 0) tmp -> next_digit = new_Number(carry);
        if(second) second = second -> next_digit;
        buff = temp1;
    }

}**/
void print_number(Bignumber *head)
{
    Bignumber* cur = head;

    while (cur != NULL) {
        printf("%i", cur->digit);
        cur = cur->next_digit;
    }
}
int main(void) {
//Bignumber *second=NULL;
Bignumber *res = NULL;
Stack *stack = NULL;
int c;
while(1)
{
    Bignumber *first = NULL;
    while((c = fgetc(stdin)) >= '0' && (c <= '9'))
    {
        //if(c == '\n')break;
        //if(c == ' ') break;
        add_digit(&first,c -'0');
    }
    push(&stack, first);
    if(c == '\n')break;

}
//while((c = fgetc(stdin)) >= '0' && (c <= '9'))
//{
  // add_digit(&second,c-'0');
//}
//push(&stack, second);
//Bignumber *cur1 =pop(&stack);
//Bignumber *cur2 = pop(&stack);
res = sum_of(pop(&stack),pop(&stack));
push(&stack, res);
//Bignumber *cur = pop(&stack);
print_number(pop(&stack));
return 0;
}
