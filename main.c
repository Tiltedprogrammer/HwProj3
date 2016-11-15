#include "stdio.h"
#include "malloc.h"

typedef struct Bignumber{
	int digit;
	struct Bignumber *next_digit;
    int sign;
}Bignumber;

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
Bignumber multiply(Bignumber *first, Bignumber *second)
{
    Bignumber *res = NULL;
    Bignumber *tmp, *prev = NULL, *temp1, *buff;
    int carry = 0, multy;
    while(second)
    {
        temp1 = NULL;
        //*first = first;
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

}
int main(void) {
Bignumber *first = NULL;
Bignumber *second = NULL;
Bignumber *res = NULL;
int c,sign1,oper;
while(((c = fgetc(stdin)) >= '0' && (c <= '9')) || c == '-')
{
   if(c == '-')
   {
       sign1 = c;
   }
   else add_digit(&first,c-'0');
}
while((c = fgetc(stdin)) >= '0' && (c <= '9'))
{
   add_digit(&second,c-'0');
}
oper = fgetc(stdin);
switch(oper)
{
    case'+':
        res = sum_of(first, second);
    default:
        res = sum_of(first, second);

}
//res = sum_of(first, second);
while(res != NULL)
{
    printf("%i", res -> digit);
    res = res -> next_digit;
}


return 0;
}
