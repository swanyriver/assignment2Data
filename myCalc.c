#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"



const double E = 2.7182818;
const double PI = 3.14159265;



/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anything in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}


double add (double lhs, double rhs)
{
	return lhs + rhs;
}


double subtract(double lhs, double rhs)
{
    return lhs - rhs;
}

double divide(double lhs, double rhs)
{
    return lhs / rhs;
}

double multiply(double lhs, double rhs){
    return lhs * rhs;
}

void twoOperand(struct DynArr *stack, double(*operation)(double,double)){
    double rhs = topDynArr(stack);
    popDynArr(stack);
    double lhs = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack,operation(lhs,rhs));
}
void singleOperand(struct DynArr *stack, double(*operation)(double)){
    double rhs = topDynArr(stack);
    popDynArr(stack);

    pushDynArr(stack,operation(rhs));
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			twoOperand(stack,add);
		else if(strcmp(s,"-") == 0)
		    twoOperand(stack,subtract);
		else if(strcmp(s, "/") == 0)
		    twoOperand(stack,divide);
		else if(strcmp(s, "x") == 0)
			twoOperand(stack,multiply);
		else if(strcmp(s, "^") == 0)
			//twoOperand(stack,pow);
		    pow(1,2);
		/*else if(strcmp(s, "^2") == 0){
			pushDynArr(stack,2);
		    twoOperand(stack,pow);
		}
		else if(strcmp(s, "^3") == 0){
            pushDynArr(stack,3);
            twoOperand(stack,pow);
        }*/
		else if(strcmp(s, "abs") == 0)
			/* FIXME: replace printf with your own function */
			printf("Absolute value\n");
		else if(strcmp(s, "sqrt") == 0)
			/* FIXME: replace printf with your own function */
			printf("Square root\n");
		else if(strcmp(s, "exp") == 0)
			/* FIXME: replace printf with your own function */
			printf("Exponential\n");
		else if(strcmp(s, "ln") == 0)
			/* FIXME: replace printf with your own function */
			printf("Natural Log\n");
		else if(strcmp(s, "log") == 0)
			/* FIXME: replace printf with your own function */
			printf("Log\n");
		else 
		{
		    double number;

		    if(strcmp(s,"e")==0){
		        pushDynArr(stack,E);
		    }
		    else if(strcmp(s,"pi")==0){
		        pushDynArr(stack,PI);
		    }
		    else if(isNumber(s,&number)){
		        pushDynArr(stack,number);
		    }
		    else{
		        printf("%s is neither a number nor an operand exiting now",s);
		        return 0;
		    }
		    printf("stacktop:%f \n",topDynArr(stack)); //todo remove
			
		}
	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	
	if(sizeDynArr(stack)!=1){
	    printf("there was an imbalance number of operators and operands\n");
	    return 0;
	}else{
	    result = topDynArr(stack);
	    printf("\n%f\n",result);
	}

	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	calculate(argc,argv);
	return 0;
}
