#include <stdlib.h>
#include <stdio.h>
#include "big_number.h"
#include "long_math.h"
#include "stack.h"

int main()
{
	Stack *stack = NULL;
	char c;
	while((c = fgetc(stdin))!=EOF)
	{
    	//c = fgetc(stdin);
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
        		printf("Not enough operands || empty stack\n");
        		break;
       		}
        	break;
    		case'*':
    		if(stack->number && stack->next_number)
        	{
        		multiply_of(&stack);
        	}
    		else{
    			printf("Not enough operands || empty stack\n");
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
              		break;
            	}
            	else
            	{
                	substraction(&stack);
                	break;
            	}
        	}
        	else
        	{
            	printf("Not enough operands || empty stack");
            	break;
        	}
    	case'/':
        	if(stack->number && stack->next_number)
        	{
            	division(&stack);
        	}
        	else{
        		printf("Not enough operands || empty stack\n");
        	}
        	break;
    	case'\n':
        	break;
    	case ' ':
        	break;
    	case'=':
    	if(stack->sign == 1)
    	{
    		printf("-");
    	}
    	print_number(stack->number);
        	break;
    	case'q':
        	free_stack(stack);
        	return 0;        
    	default:
        	push(&stack, get_number(c));
        	stack -> sign = 0;
        	break;


    	}
    }
    free_stack(stack);	
	return 0;    		
}
