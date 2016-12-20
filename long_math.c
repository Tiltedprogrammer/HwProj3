#include <stdlib.h>
#include <stdio.h>
#include "long_math.h"
#include "stack.h"


int comparator(Bignumber *f, Bignumber *s)
{
    //if ((list_len(f)) > (list_len(s))) return 1;
    if(f->size > s -> size) return 1;
    //else if ((list_len(f)) < (list_len(s))) return -1;
    else if(f->size < s -> size) return -1;
    else
    {
        Node *f1 = f->tail;
        Node *s1 = s -> tail;
        while(f1)
        {
            if((f1->digit) > (s1 -> digit))
            {
                return 1;
            }
            else if ((f1->digit) < (s1 -> digit))
            { 
                return -1;
            }
            else
            {
                f1 = f1 -> prev_node;
                s1 = s1 -> prev_node;
            }

        }
        return 0;
    }

}
void eliminate_zeroes(Bignumber **res)
{

    Node *tmp;    
    while(((*res)->tail !=NULL) && ((*res)->tail->digit == 0)&&((*res)->head->next_node))
      {
          tmp = (*res)->tail;
          (*res)->tail = (*res) ->tail ->prev_node;
          (*res) ->tail ->next_node = NULL;
          free(tmp);
          (*res)->size--;
      }
}
void sum_of(Stack **stack)
{
    char sign = ((*stack)->next_number->sign == 0) ? 0:1;
    Bignumber *first = pop(stack);
    Bignumber *second = pop(stack);
    Node *f = first -> head, *s = second -> head;
    Bignumber *res = new_Number();
    char carry = 0, sum = 0;
    while(f != NULL || s != NULL)
    {
        sum = carry + (f? f->digit: 0) + (s? s->digit: 0);
        carry = sum / 10;//(sum >= 10)? 1 : 0; // or carry = sum / 10;
        sum = sum % 10;
        add_to_e(&res,sum);
        if(f) free_node(&f);//f = f -> next_node;
        if(s) free_node(&s);//s = s -> next_node;
    }
    if(carry > 0)
    {
        add_to_e(&res, carry);
    }
    free(first);
    free(second);
    push(stack, res);
    (*stack) -> sign = sign;
    
}
Bignumber *sum_factors(Bignumber **first, Bignumber **second)
{
    //Bignumber *first_to_free = (*first), *second_to_free = (*second);
    Node *f = (*first) -> head, *s = (*second) ->head;
    Bignumber *res = new_Number();
    //Bignumber *tmp, *prev = NULL;
    char carry = 0, sum;
    while(f != NULL || s != NULL)
    {
        sum = carry + (f? f->digit: 0) + (s? s->digit: 0);
        carry = (sum >= 10)? 1 : 0;
        sum = sum % 10;
        add_to_e(&res,sum);
        if(f) free_node(&f);
        if(s) free_node(&s);
    }
    if(carry > 0)
    {
        add_to_e(&res, carry);
    }
    free(*first);
    free(*second);
    return res;
}
void multiply_of(Stack **stack)
{
    char s2 = (*stack) -> sign;
    char s1 = (*stack)->next_number->sign;
    Bignumber *first = pop(stack);
    Bignumber *second = pop(stack);
    Bignumber *res = new_Number();
    if((first->tail->digit == 0)||(second->tail->digit == 0))
    {
       add_to_e(&res,0);
       push(stack,res);
       (*stack) -> sign = 0;
       free_list(first);
       free_list(second);
       return;
    }
    Node *f = first ->head;
    Node *s = second -> head;
    add_to_e(&res, 0);
    char factor;
    int n = 0;
    Node *tmp = NULL;
    while(s)
    {
       int carry = 0;
       Bignumber *tmp_res = new_Number();
       tmp = f;
       while(tmp)
       {
           factor = ((s -> digit)*(tmp ->digit)) + carry;
           add_to_e(&tmp_res,factor % 10);
           carry = factor / 10;
           if(!s->next_node) free_node(&tmp);
           else tmp = tmp -> next_node;
       }

       if(carry > 0) add_to_e(&tmp_res, carry);
       int i;
       for(i = 0; i < n; i++)
       {
           add_to_b(&tmp_res,0);
       }
       res = sum_factors(&res, &tmp_res);
       n++;
       s = s -> next_node;
    }
    push(stack, res);
    (*stack) -> sign = (s1 == s2) ? 0:1;
    free(first);
    free_list(second);
}
void substraction(Stack **stack)
{
    Bignumber *res = new_Number();
    char s_res = (*stack)->next_number->sign;
    Bignumber *second = pop(stack);
    Bignumber *first = pop(stack);
    if(comparator(first, second) == 0)
    {
        free_list(first);
        free_list(second);
        add_to_e(&res, 0);
        push(stack, res);
        (*stack) -> sign = 0;
        return;

    }
    if(comparator(first,second) == -1)
    {
        s_res = (s_res == 1) ? 0:1;
        swap(&first, &second);
    }
    int n,m;
    if((n =first -> size) != (m = second -> size))
    {
        int i;
        for(i = 0; i < n-m; i++)
            add_to_e(&second, 0);
    }
    Node *f = first->head, *s = second->head;
    char carry = 0,sub;
    while(f && s)
    {
      sub = ((f->digit) - (s->digit)) + carry;
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
      free_node(&f);
      free_node(&s);
    }
    free(first);
    free(second);
    eliminate_zeroes(&res);
    push(stack, res);
    (*stack) -> sign = s_res;
}
Bignumber *division_sub(Bignumber **f, Bignumber **s)
{
    Bignumber *res = new_Number();
    Bignumber *first = *f;
    Bignumber *second = *s;
    if(comparator(first, second) == 0)
    {
        free_list(*f);
        free_list(*s);
        add_to_e(&res, 0);
        return res;
    }
    int n,m;
    if((n =first -> size) != (m = second -> size))
    {
        int i;
        for(i = 0; i < n-m; i++)
            add_to_e(&second, 0);
    }
    Node *fp = first->head, *sp = second->head;
    char carry = 0,sub;
    while(fp && sp)
    {
      sub = ((fp->digit) - (sp->digit)) + carry;
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
      free_node(&fp);
      free_node(&sp);
    }
    free(first);
    free(second);
    eliminate_zeroes(&res);
    return res;

}
Bignumber *division_multiply(Bignumber **first, char i)
{
    Bignumber *res = new_Number();
    Node *f = (*first)->head;
    char factor;
       char carry = 0;
       while(f)
       {
           factor = (f -> digit) * i + carry;
           add_to_e(&res,(factor %10));
           carry = factor / 10;
           f = f -> next_node;

       }
       if(carry > 0) add_to_e(&res, carry);
    return res;
}
void division(Stack **stack)
{
	char s2 = (*stack) -> sign;
    char s1 = (*stack)->next_number->sign;
    Bignumber *res = new_Number();
    Bignumber *second = pop(stack);
    Bignumber *first = pop(stack);
    if(second ->tail->digit == 0)
    {
    	free_list(first);
    	free_list(second);
        printf("Division by 0");
        exit(1);
    }
    if(comparator(first, second)== -1)
    {
        free_list(first);
        free_list(second);
        add_to_e(&res, 0);
        push(stack,res);
        return;
    }
    Bignumber *tmp = new_Number();
    Node *fpointer = first->tail;
    add_to_b(&tmp, fpointer -> digit);
    while(comparator(tmp, second) == -1)
    {
        fpointer = fpointer -> prev_node;
        add_to_b(&tmp, fpointer -> digit);
    }
    char i = 1;
    int comp;
    Bignumber *tmp_res = division_multiply(&second, i);
    while(((comp = comparator(tmp_res,tmp)) == -1) || (comp == 0))
          {
          
              i++;
              free_list(tmp_res);
              tmp_res = division_multiply(&second, i);
          }
    free_list(tmp_res);            
    i -=1;
    tmp_res = division_multiply(&second, i);
    add_to_e(&res, i);
    tmp = division_sub(&tmp, &tmp_res);
    fpointer = fpointer -> prev_node;
    while(fpointer)
    {
        while(fpointer)
        {
            add_to_b(&tmp, fpointer->digit);
            eliminate_zeroes(&tmp);
            if(comparator(tmp, second) == -1)
            {
                add_to_b(&res, 0);
                fpointer = fpointer->prev_node;
                eliminate_zeroes(&tmp);
            }
            else
            {
                fpointer = fpointer -> prev_node;
                //eliminate_zeroes(&tmp);
                break;
            }
        }
        i = 1;
        tmp_res = division_multiply(&second, i);
        while(((comp = comparator(tmp_res,tmp)) == -1) || (comp == 0))
            {
                i++;
                free_list(tmp_res);
                tmp_res = division_multiply(&second, i);
            } 
        i -=1;
        free_list(tmp_res);
        if (i != 0)
        {
            tmp_res = division_multiply(&second, i);
            add_to_b(&res, i);
            tmp = division_sub(&tmp, &tmp_res);
        }
    }
    free_list(tmp);
    free_list(first);
    free_list(second);
    push(stack,res);
    (*stack) -> sign = (s1 == s2) ? 0:1;


}