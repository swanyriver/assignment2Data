#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"
#include <math.h>


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


int isTwoOperands(char *s){
    return(strcmp(s, "+") == 0 ||
           strcmp(s, "-") == 0 ||
           strcmp(s, "/") == 0 ||
           strcmp(s, "x") == 0 ||
           strcmp(s, "^") == 0);
}
int isOneOperands(char *s){
    return(strcmp(s, "^2") == 0 ||
           strcmp(s, "^3") == 0 ||
           strcmp(s, "abs") == 0 ||
           strcmp(s, "sqrt") == 0 ||
           strcmp(s, "exp") == 0 ||
           strcmp(s, "ln") == 0 ||
           strcmp(s, "log") == 0);
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	double lhs,rhs;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

        if (isTwoOperands(s)) {

            if(sizeDynArr(stack)<2){
                printf("the stack has too few operands for the operation:%s",s);
                return 0;
            }

            rhs = topDynArr(stack);
            popDynArr(stack);
            lhs = topDynArr(stack);
            popDynArr(stack);

            if(strcmp(s, "+") == 0)
                pushDynArr(stack,lhs+rhs);
            else if(strcmp(s,"-") == 0)
                pushDynArr(stack,lhs-rhs);
            else if(strcmp(s, "/") == 0)
                pushDynArr(stack,lhs/rhs);
            else if(strcmp(s, "x") == 0)
                pushDynArr(stack,lhs * rhs);
            else if(strcmp(s, "^") == 0)
                pushDynArr(stack,pow(lhs,rhs));
        }
        else if (isOneOperands(s)) {

            if(sizeDynArr(stack)<1){
                printf("the stack has too few operands for the operation:%s",s);
                return 0;
            }

            rhs = topDynArr(stack);
            popDynArr(stack);

            if(strcmp(s, "^2") == 0)
                /* FIXME: replace printf with your own function */
                printf("Squaring\n");
            else if(strcmp(s, "^3") == 0)
                /* FIXME: replace printf with your own function */
                printf("Cubing\n");
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
        }
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
    }   //end for

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
