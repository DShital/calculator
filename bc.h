
/*****************************************************************************
 * Copyright (C) Dhanba Shital dhanbashital@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


#ifndef __BC_H
#define __BC_H
#include <stdlib.h>


typedef struct stack {
	void * data;
	struct stack *prev;
}Stack;

typedef struct operator {
	int number;
	int precedence;
	int args;
	int symbol_len;
	char * symbol;
	double (*function)(double, double);
}Operator;

double add(double x, double y);
double subtract(double x, double y);
double multiply(double x, double y);
double divide(double x, double y);
double mod(double x, double y);
Stack* pushtostack(Stack *s, void* value, size_t size);
void * popfromstack(Stack **s);
void* peekstack(Stack * s);
double evaluateStack(Stack **opstack, Stack **valuestack);


#define peekvalue(val) (val ? *((double*)(val)->data): 0)
#define peekop(op) (op ? *((int*)(op)->data) : 0)

Stack* evalAndPush(Stack **opstack, Stack **valuestack, int value);
char * strip(char * string);
#endif
