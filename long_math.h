#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "big_number.h"
#include "stack.h"

int comparator(Bignumber *f, Bignumber *s);
void eliminate_zeroes(Bignumber **res);
void sum_of(Stack **stack);
Bignumber *sum_factors(Bignumber **first, Bignumber **second);
void multiply_of(Stack **stack);
void substraction(Stack **stack);
Bignumber *division_sub(Bignumber **f, Bignumber **s);
Bignumber *division_multiply(Bignumber **first, char i);
void division(Stack **stack);

