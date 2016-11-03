
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bc.h"

#define VALUE_STATE 0
#define OP_STATE 1
#define MAX 100

double add(double x, double y) {
	//printf("add %f + %f = %f\n", y, x, y+x);
	return y + x;
}

double subtract(double x, double y) {
	//printf("subtract %f - %f = %f\n", y, x, y-x);
	return y - x;
}

double multiply(double x, double y) {
	//printf("multiply %f * %f = %f\n", y, x, y*x);
	return y * x;
}

double divide(double x, double y) {
	//printf("divide %f / %f = %f\n", y, x, y/x);
	return y / x;
}

double mod(double x, double y) {
	//printf("mod %f % %f = %f\n", y, x, y%x);
	return (int)y % (int)x;
}

Operator operators[] = {
	{0, 1, 2, 1, "+", &add},
	{1, 1, 2, 1, "-", &subtract},
	{2, 2, 2, 1, "*", &multiply},
	{3, 2, 2, 1, "/", &divide},
	{4, 2, 2, 1, "%", &mod},
	{0, 0, 0, 0, NULL, NULL}
};


Stack* pushtostack(Stack *s, void* value, size_t size) {
	Stack *news1;
	void * newvalue;

	//printf("pushing %f\n", *((double *)value));
	news1 = (Stack *) malloc(sizeof(Stack));
	newvalue = malloc(size);
	news1->data = memcpy(newvalue, value, size);
	if(s != NULL) {
		news1->prev = s;
	}
	else {
		news1->prev = NULL;
	}
	//printf("pushtostack %f\n", *((double *) news1->data));
	return news1;
}


//Stack* popfromstack(Stack *s, void **value) {
void * popfromstack(Stack **s) {
	Stack *prev;
	void *value;

	if(*s != NULL) {
		value = (*s)->data;
		prev = (*s)->prev;
		free(*s);
		*s = prev;
		//printf("popfromstack %f\n", *(double*)value);
		return value;
	}
	else {
		return NULL;
	}
}


void* peekstack(Stack * s) {
	if(s != NULL) {
		return s->data;
	}
	else {
		return NULL;
	}
}



double evaluateStack(Stack **opstack, Stack **valuestack) {
	double *value_one;
	double *value_two;
	double retval;
	int *operator;

	if(*opstack != NULL) {
		operator = (int*) popfromstack(opstack);
		if(operators[*operator].args == 2) {
			value_one = (double*) popfromstack(valuestack);
			value_two = (double*) popfromstack(valuestack);
		}
		else if(operators[*operator].args == 1 ) {
			value_one = (double*) popfromstack(valuestack);
			value_two = value_one;
		}
		else {
			fprintf(stderr, "strange number of args required. This is a bug\n");
			exit(1);
		}
		retval = operators[*operator].function(*value_one, *value_two);
		*valuestack = pushtostack(*valuestack, &retval, sizeof(double));
	}
	else{ 
		retval=0;
	}
	return retval;
}


#define peekvalue(val) (val ? *((double*)(val)->data): 0)
#define peekop(op) (op ? *((int*)(op)->data) : 0)

Stack* evalAndPush(Stack **opstack, Stack **valuestack, int value) {
	int prevop;

	if(opstack != NULL) {
		while((prevop = peekop(*opstack)) != 0) {
			if(operators[prevop].precedence >= operators[value].precedence) {
				evaluateStack(opstack, valuestack);
			}
			else {
				*opstack = pushtostack(*opstack, &prevop, sizeof(int));
				break;
			}
		}
	}

	*opstack = pushtostack(*opstack, &value, sizeof(int));
	return *opstack;
}


char * strip(char * string) {
	while(*string == ' ') {
		string++;
	}
	return string;
}

// int mystrlen(char *s) {
	//int i =0;
	//while (*s++) i++;
	//return i;
// }


int main(int argc, char* argv[]) {
	char *curr;
	char *endptr;
	double value;
	int operator;
	int i;
	//int j;
	//int len;
	int state = VALUE_STATE;
	Stack *valuestack = NULL;
	Stack *opstack = NULL;

	// if(argc == 1) {
		//printf("usage: %s [expression]\n", argv[0]);
		//exit(1);
	// }

	if(argc > 1) {
		if (strcmp(argv[1], "-h") == 0) {
			printf("usage: bc [options] [file ...]\n  -h  --help  print this usage and exit\n  -i  --interactive  force interactive mode\n  -l  --mathlib  use the predefined math routines\n  -q  --quiet  don't print initial banner\n  -s  --standard  non-standard bc constructs are errors\n  -w  --warn  warn about non-standard bc constructs\n  -v  --version  print version information and exit\n");
			exit(1);
		}
		if (strcmp(argv[1], "-w") == 0) {
			printf("bc 1.06.95\nCopyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.\nThis is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n");
		}
		if (strcmp(argv[1], "-i") == 0) {
			printf("bc 1.06.95\nCopyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.\nThis is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n");
		}
		if (strcmp(argv[1], "-v") == 0) {
			printf("bc 1.06.95\nCopyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.");
		}
		if (strcmp(argv[1], "-q") == 0) {
			printf(" ");
		}
		if (strcmp(argv[1], "-l") == 0) {
			printf("bc 1.06.95\nCopyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.\nThis is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n");
		}
		if (strcmp(argv[1], "-s") == 0) {
			printf("bc 1.06.95\nCopyright 1991-1994, 1997, 1998, 2000, 2004, 2006 Free Software Foundation, Inc.\nThis is free software with ABSOLUTELY NO WARRANTY.\nFor details type `warranty'.\n");
		}
	}

	while (1) {
		char *expr;
		//printf("first scan");
		//int count;
		//for(count=0; count)
		scanf("%s", expr);

		//fgets(expr, sizeof(expr), stdin);
		if(strcmp(expr, "quit") == 0) {
			exit(0);
		}
		//int i2=mystrlen(expr);
		// printf("i2 %d", i2);

		//scanf("%s", expr);
		//printf("%s\n", *expr);
		curr = expr;
		//int i = mystrlen(&expr);
		//while(expr++)i++;
		//printf("i = %d\n", i);
	
		//for(j = 0; j <= i; j++) {
 			//currexpr;
			while (( * curr) != 0) {
				curr = strip(curr);
				if (state == VALUE_STATE) {
					value = strtod(curr, &endptr); //try and read a number
					if (curr == endptr) {
						//fprintf(stderr, "failed to read value at %s\n", curr);
		          			exit(1);
		        		}
		        		valuestack = pushtostack(valuestack, & value, sizeof(double));
		        		curr = endptr;
		        		state = OP_STATE;
				}
				else if(state == OP_STATE) {
					operator = -1;
					i = 0;
					while (operators[i].symbol != NULL) {
						if (strncmp(operators[i].symbol, curr, operators[i].symbol_len) == 0) {
							operator = operators[i].number;
							opstack = evalAndPush( & opstack, &valuestack, operator);
							curr += operators[i].symbol_len;
							break;
						}
						i++;
		        		}
					if (operator == -1) {
						//fprintf(stderr, "invalid operator at %s\n", curr);
						exit(1);
					}
					state = VALUE_STATE;
				} 
				else {
					fprintf(stderr, "unknown state %d\n", state);
					exit(1);
				}
			}
			while ((valuestack != NULL) && (opstack != NULL)) {
				evaluateStack(&opstack, &valuestack);
			}
			printf("%g\n", peekvalue(valuestack));
			valuestack = NULL;
			state = VALUE_STATE;
			opstack = NULL;

		
			//end of else
			//printf("second scan");
			//gets(expr);
			//i2=mystrlen(expr);
			//printf("2nd i2 %d",i2);
		}
	}
