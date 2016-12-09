#include <stdio.h>
#include "malloc.h"
#include <stdlib.h>

typedef struct Bignumber{
	int digit;
	struct Bignumber *next_digit;
    char sign;
}Bignumber;

typedef struct Stack{
    Bignumber *number;
    struct Stack *next_number;
    char sign;
} Stack;
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

void swap(Bignumber **f, Bignumber **s)
{
    Bignumber *tmp = NULL;
    tmp = *f;
    *f = *s;
    *s = tmp;

}
void reverse(Bignumber** head)
{
    if((*head) == NULL)
    {
        return;
    }
    Bignumber* prev = NULL;
    Bignumber* cur = (*head);
    Bignumber* next;
    while (cur != NULL)
    {
        next  = cur->next_digit;
        cur->next_digit = prev;
        prev = cur;
        cur = next;
    }
    (*head) = prev;
}

void eliminate_zeroes(Bignumber **res)
{

    Bignumber *tmp;
    reverse(res);
    while(((*res) != NULL) && ((*res)->digit == 0))
    {
        tmp = (*res);
        (*res) = (*res) -> next_digit;
        free(tmp);
    }
    reverse(res);
    //printf("%i\n", cur->digit);
    //reverse(&cur);
}

int list_len(Bignumber *list)
{
    Bignumber *cur = list;
    int length = 0;
    while(cur)
    {
        length++;
        cur = cur->next_digit;
    }
    return length;
}
int comparator(Bignumber *f, Bignumber *s)
{
    if ((list_len(f)) > (list_len(s))) return 1;
    else if ((list_len(f)) < (list_len(s))) return -1;
    else
    {
        reverse(&f);
        reverse(&s);
        Bignumber *f1 = f;
        Bignumber *s1 = s;
        while(f1)
        {
            if((f1->digit) > (s1 -> digit))
            {
                reverse(&f);
                reverse(&s);
                return 1;
            }
            else if ((f1->digit) < (s1 -> digit))
            {
                reverse(&f);
                reverse(&s);
                return -1;
            }
            else
            {
                f1 = f1 -> next_digit;
                s1 = s1 -> next_digit;
            }

        }
        reverse(&f);
        reverse(&s);
        return 0;
    }

}

void free_list(Bignumber **list)
{
    Bignumber *tmp = NULL;
    while((tmp=(*list)))
    {
        (*list) = (*list) ->next_digit;
        free(tmp);
    }
    //free(tmp);
}

void free_stack(Stack *head)
{
    Stack *tmp = NULL;
    while((tmp = head))
    {
        head = head -> next_number;
        free(tmp);
    }
    //free(tmp);
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

void add_to_e(Bignumber **head, int data)
{
    Bignumber *new_digit = new_Number(data);
    Bignumber *cur = *head;
    if(*head == NULL) *head = new_digit;
    else
    {
        while(cur->next_digit)
        {
            cur = cur -> next_digit;
        }
        cur ->next_digit = new_digit;
    }
}
void print_number(Bignumber *head)
{
    Bignumber* cur = head;
    if(head == NULL)
    {
        return;
    }

    print_number(cur->next_digit);
    printf("%i", cur->digit);
}
Stack **sum_of(Stack **stack)
{
    char sign = ((*stack)->next_number->sign == 0) ? 0:1;
    Bignumber *first = pop(stack);
    Bignumber *second = pop(stack);
    Bignumber *f = first, *s = second;
    Bignumber *res = NULL;
    int carry = 0, sum;
    while(f != NULL || s != NULL)
    {
        sum = carry + (f? f->digit: 0) + (s? s->digit: 0);
        carry = (sum >= 10)? 1 : 0; // or carry = sum / 10;
        sum = sum % 10;
        add_to_e(&res,sum);
        if(f) f = f -> next_digit;
        if(s) s = s -> next_digit;
    }
    if(carry > 0)
    {
        add_to_e(&res, carry);
    }
    free_list(&first);
    free_list(&second);
    push(stack, res);
    (*stack) -> sign = sign;
    return stack;
}
Bignumber *sum_factors(Bignumber *first, Bignumber *second)
{
    Bignumber *first_to_free = first, *second_to_free = second;
    Bignumber *res = NULL;
    //Bignumber *tmp, *prev = NULL;
    int carry = 0, sum;
    while(first != NULL || second != NULL)
    {
        sum = carry + (first? first->digit: 0) + (second? second->digit: 0);
        carry = (sum >= 10)? 1 : 0;
        sum = sum % 10;
        //tmp = new_Number(sum);
        //if(res==NULL)
        //{
          //  res = tmp;
        //}
        //else
        //{
          //  prev->next_digit = tmp;
        //}
        //prev = tmp;
        add_to_e(&res,sum);
        if(first) first = first -> next_digit;
        if(second) second = second -> next_digit;
    }
    if(carry > 0)
    {
        //tmp -> next_digit = new_Number(carry);
        add_to_e(&res, carry);
    }
    free_list(&first_to_free);
    free_list(&second_to_free);
    return res;
}
Stack **multiply_of(Stack **stack)
{
    char s2 = (*stack) -> sign;
    char s1 = (*stack)->next_number->sign;
    Bignumber *first = pop(stack);
    Bignumber *second = pop(stack);
    Bignumber *res = NULL;
    if(((list_len(first) == 1)&&(first->digit == 0))|| ((list_len(second) == 1)&&(second->digit == 0)))
    {
       add_to_e(&res,0);
       push(stack,res);
       (*stack) -> sign = 0;
       free_list(&first);
       free_list(&second);
       return stack;
    }
    Bignumber *first_to_free = first, *second_to_free = second;
    //Bignumber *res = NULL;
    Stack *multy_stack = NULL;
    int factor;
    int n = 0;
    while(second)
    {
       int carry = 0;
       Bignumber *tmp = NULL;
       Bignumber *tmp_res = NULL;
       tmp = first;
       while(tmp)
       {
           factor = ((second -> digit)*(tmp ->digit)) + carry;
           //carry = factor / 10;
           add_to_e(&tmp_res,factor % 10);
           carry = factor / 10;
           tmp = tmp -> next_digit;

       }
       if(carry > 0) add_to_e(&tmp_res, carry);
       int i;
       for(i = 0; i < n; i++)
       {
           add_digit(&tmp_res,0);
       }
       push(&multy_stack, tmp_res);
       n++;
       second = second -> next_digit;
    }
    int i;
    for(i = 0; i < n-1; i++)
    {
        push(&multy_stack, sum_factors(pop(&multy_stack), pop(&multy_stack)));

    }
    res = pop(&multy_stack);
    push(stack, res);
    (*stack) -> sign = (s1 == s2) ? 0:1;
    free_stack(multy_stack);
    free_list(&first_to_free);
    free_list(&second_to_free);
    return stack;

}

Stack **substraction(Stack **stack)
{
    Bignumber *res = NULL;
    char s_res = (*stack)->next_number->sign;
    Bignumber *second = pop(stack);
    Bignumber *first = pop(stack);
    Bignumber *f = first, *s = second;
    if(comparator(first, second) == 0)
    {
        free_list(&first);
        free_list(&second);
        add_to_e(&res, 0);
        push(stack, res);
        (*stack) -> sign = 0;
        return stack;
    }
    if(comparator(first,second) == -1)
    {
        s_res = (s_res == 1) ? 0:1;
        swap(&first, &second);
    }
    if(list_len(first) != list_len(second))
    {
        int n = list_len(first) - list_len(second);
        int i;
        for(i = 0; i < n; i++)
            add_to_e(&second, 0);
    }
    int carry = 0,sub;
    while(first && second)
    {
      sub = ((first->digit) - (second->digit)) + carry;
      if(sub < 0)
      {
          sub += 10;
          carry = -1;
      }
      else
      {
          carry = 0;
      }
      add_to_e(&res, sub);
      first = first->next_digit;
      second = second->next_digit;
    }
    free_list(&f);
    free_list(&s);
    eliminate_zeroes(&res);
    //res -> sign = s_res;
    push(stack, res);
    (*stack) -> sign = s_res;
    return stack;

}
Bignumber *division_sub(Bignumber **f, Bignumber **s)
{
    Bignumber *res = NULL;
    //Bignumber *secondfree = second;
    Bignumber *first = *f;
    Bignumber *second = *s;
    if(comparator(first, second) == 0)
    {
        free_list(f);
        free_list(s);
        add_to_e(&res, 0);
        return res;
    }
    if(list_len(first) != list_len(second))
    {
        int n = list_len(first) - list_len(second);
        int i;
        for(i = 0; i < n; i++)
            add_to_e(&second, 0);
    }
    //Bignumber *firstfree = first;
    int carry = 0,sub;
    while(first && second)
    {
      sub = ((first->digit) - (second->digit)) + carry;
      if(sub < 0)
      {
          sub += 10;
          carry = -1;
      }
      else
      {
          carry = 0;
      }
      add_to_e(&res, sub);
      first = first->next_digit;
      second = second->next_digit;
    }
    free_list(f);
    free_list(s);
    eliminate_zeroes(&res);
    return res;

}
Bignumber *division_multiply(Bignumber **first, int i)
{
    Bignumber *res = NULL;
    Bignumber *f = *first;
    int factor;
       int carry = 0;
       while(f)
       {
           factor = (f -> digit) * i + carry;
           //carry = factor / 10;
           add_to_e(&res,(factor %10));
           carry = factor / 10;
           f = f -> next_digit;

       }
       if(carry > 0) add_to_e(&res, carry);
    return res;
}

Stack **division(Stack **stack)
{
	char s2 = (*stack) -> sign;
    char s1 = (*stack)->next_number->sign;
    Bignumber *res = NULL;
    Bignumber *second = pop(stack);
    Bignumber *first = pop(stack);
    //int lens = list_len(second);
    if((list_len(second) == 1)&&(second ->digit == 0))
    {
    	free_list(&first);
    	free_list(&second);
        printf("Division by 0");
        exit(1);
    }
    if(comparator(first, second)== -1)
    {
        free_list(&first);
        free_list(&second);
        add_to_e(&res, 0);
        push(stack,res);
        return stack;
    }
    reverse(&first);
    Bignumber *tmp = NULL;
    Bignumber *fpointer = first;
    add_digit(&tmp, fpointer -> digit);
    while(comparator(tmp, second) == -1)
    {
        fpointer = fpointer -> next_digit;
        add_digit(&tmp, fpointer -> digit);
    }
    int i = 1;
    int comp;
    Bignumber *tmp_res = division_multiply(&second, i);
    while(((comp = comparator(tmp_res,tmp)) == -1) || (comp == 0))
          {
              i++;
              free_list(&tmp_res);
              tmp_res = division_multiply(&second, i);
          }
    i -=1;
    free_list(&tmp_res);
    tmp_res = division_multiply(&second, i);
    add_to_e(&res, i);
    //Bignumber *tmp_tmp = list_copy(&tmp_res);
    //for(j = 0; j < n; j++)
    //{
      //  add_digit(&tmp_res, 0);
    //}
    tmp = division_sub(&tmp, &tmp_res);
    eliminate_zeroes(&tmp);
    fpointer = fpointer -> next_digit;
    while(fpointer)
    {
        while(fpointer)
        {
            add_digit(&tmp, fpointer->digit);
            //print_number(tmp);
            if(comparator(tmp, second) == -1)
            {
                add_digit(&res, 0);
                fpointer = fpointer->next_digit;
                eliminate_zeroes(&tmp);
            }
            else
            {
                fpointer = fpointer -> next_digit;
                eliminate_zeroes(&tmp);
                break;
            }
        }
        i = 1;
        tmp_res = division_multiply(&second, i);
        while(((comp = comparator(tmp_res,tmp)) == -1) || (comp == 0))
            {
                i++;
                free_list(&tmp_res);
                tmp_res = division_multiply(&second, i);
            }
        i -=1;
        free_list(&tmp_res);
        if (i != 0)
        {
            tmp_res = division_multiply(&second, i);
            add_digit(&res, i);
        }
        tmp = division_sub(&tmp, &tmp_res);
        eliminate_zeroes(&tmp);
    }
    free_list(&tmp);
    reverse(&first);
    free_list(&first);
    free_list(&second);
    push(stack,res);
    (*stack) -> sign = (s1 == s2) ? 0:1;
    return stack;


}

Bignumber *get_number(int c)
{
    Bignumber *number = NULL;
    add_digit(&number, c - '0');
    while(((c = fgetc(stdin)) >= '0') && (c <= '9'))
    {
        add_digit(&number, c - '0');
    }
    return number;
}

int main(void) {
Bignumber *res = NULL;
Stack *stack = NULL;
int c;
while(1)
{
    c = fgetc(stdin);
    switch(c)
    {
    case'+':
       if(stack && stack -> next_number)
       {
        if(stack->sign == stack->next_number->sign)
        {
           sum_of(&stack);
        }
        else
        {
            substraction(&stack);
        }
       }
       else{
        printf("Not enough operands\n");
        break;
       }
        break;
    case'*':
    if(stack->number && stack->next_number)
        {
        	multiply_of(&stack);
        }
    else{
    	printf("Not enough operands\n");
    }    
        break;
    case'-':
        if(((c = fgetc(stdin))!= ' ') && (c != '\n'))
        {
           push(&stack, get_number(c));
           stack -> sign = 1;
           break;
        }
        if(stack && stack -> next_number)
        {
            if(stack->sign != stack->next_number->sign)
            {
                sum_of(&stack);
                    if(c == '\n')
                    {
                        if(stack->sign == 1)
                        {
                            printf("-");
                        }
                    res = pop(&stack);
                    print_number(res);
                    free_list(&res);
                    printf("\n");
                    return 0;
                    }
              break;
            }
            else
            {
                substraction(&stack);
                if(c == '\n')
                    {
                    if(stack->sign == 1)
                    {
                    printf("-");
                    }
                    res = pop(&stack);
                    print_number(res);
                    free_list(&res);
                    printf("\n");
                    return 0;
                    }
                break;
            }
        }
        else
        {
            printf("Not enough operands");
            break;
        }
    case'/':
        if(stack->number && stack->next_number)
        {
            division(&stack);
        }
        else{
        	printf("Not enough operands\n");
        }
        break;
    case'\n':
    if(stack)
      {  if(stack->sign == 1)
        {
            printf("-");
        }
        res = pop(&stack);
        print_number(res);
        printf("\n");
        free_list(&res);
        free_stack(stack);
        return 0;
    }
    else 
    {
    	printf("Bye");
    	return 0;
    }
    case ' ':
        break;
    default:
        push(&stack, get_number(c));
        stack -> sign = 0;
        break;


    }


}
}

