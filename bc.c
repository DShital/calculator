#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void addition();
void subtraction();
void calculator_operations();

int main() {
	char calc_oprn;  /*calculator_operations();*/
	scanf("%c", &calc_oprn);
	while(1) {
		printf("\n");
		
		switch(calc_oprn) {
			case '+' : addition();
				   break;
			case '-' : subtraction();
				   break;
			case 'q' : exit(0);
				   break;
			default : break;
		}
		
	}
return 0;
}

/*void calculator_operations() {
	printf("enter + for addition:\n");
	printf("enter - for subtraction:\n");
}*/

void addition() {
	double n, sum = 0, c, value;
	char calc_oprn;  /*calculator_operations();*/
	scanf("%c", &calc_oprn);
	/*printf("Enter the numbers to add\n");*/	
	scanf("%lf", &n);
	printf("\n");
	for (c = 1; c <= n; c++) {
		scanf("%lf", &value);
      		sum = sum + value;
   }
 	printf("%lf\n",sum);
}


/*void calculator_operations();*/


void subtraction() {

double m, sub, d, value;
	/*printf("Enter the numbers you want to substract\n");*/	
	scanf("%lf", &m);
	printf("\n");
	for (d = 1; d <= m; d++) {
		scanf("%lf", &value);
      		sub = sub - value;
   }
 	printf("%lf\n",sub);
	
}


