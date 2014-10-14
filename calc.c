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
int isNumber ( char *s , double *num ) {
    char *end;
    double returnNum;

    if ( strcmp( s , "0" ) == 0 ) {
        *num = 0;
        return 1;
    } else {
        returnNum = strtod( s , &end );
        /* If there's anything in end, it's bad */
        if ( (returnNum != 0.0) && (strcmp( end , "" ) == 0) ) {
            *num = returnNum;
            return 1;
        }
    }
    return 0;  //if got here, it was not a number
}

/*  param: lhs, the left hand side of the operation
    param: rhs, the right hand side of the operation
    returns: the result of lhs + rhs
*/
double add ( double lhs , double rhs ) {
    return lhs + rhs;
}

/*  param: lhs, the left hand side of the operation
    param: rhs, the right hand side of the operation
    returns: the result of lhs - rhs
*/
double subtract ( double lhs , double rhs ) {
    return lhs - rhs;
}

/*  param: lhs, the left hand side of the operation
    param: rhs, the right hand side of the operation
    returns: the result of lhs / rhs
*/
double divide ( double lhs , double rhs ) {
    if(rhs==0){
        printf("division by zero not permitted \n");
        exit(1);
    }

    return lhs / rhs;
}

/*  param: lhs, the left hand side of the operation
    param: rhs, the right hand side of the operation
    returns: the result of lhs * rhs
*/
double multiply ( double lhs , double rhs ) {
    return lhs * rhs;
}

/*  param: stack the stack being manipulated
    param: pointer to a math function with two doubles as parameters
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    the result of *operation is pushed back onto the stack.
*/
void twoOperand ( struct DynArr *stack ,
        double (*operation) ( double , double ) ) {

    if ( sizeDynArr( stack ) < 2 ) {
        printf( "the stack has insufficient operands for this operation" );
        exit( 1 );
    }
    double rhs = topDynArr( stack );
    popDynArr( stack );
    double lhs = topDynArr( stack );
    popDynArr( stack );

    pushDynArr( stack , operation( lhs , rhs ) );
}

/*  param: stack the stack being manipulated
    param: pointer to a math function with one double as a parameter
    pre: the stack contains at least one elements
    post: the top element is popped and
    the result of *operation is pushed back onto the stack.
*/
void singleOperand ( struct DynArr *stack , double (*operation) ( double ) ) {

    if ( sizeDynArr( stack ) < 1 ) {
        printf( "the stack has insufficient operands for this operation" );
        exit( 1 );
    }

    double rhs = topDynArr( stack );
    popDynArr( stack );

    pushDynArr( stack , operation( rhs ) );
}

double calculate ( int numInputTokens , char **inputString ) {
    int i;
    double result = 0.0;
    char *s;
    struct DynArr *stack;

    //set up the stack
    stack = createDynArr( 20 );

    // start at 1 to skip the name of the calculator calc
    for ( i = 1; i < numInputTokens ; i++ ) {
        s = inputString[i];

        if ( strcmp( s , "+" ) == 0 )
            twoOperand( stack , add );
        else if ( strcmp( s , "-" ) == 0 )
            twoOperand( stack , subtract );
        else if ( strcmp( s , "/" ) == 0 )
            twoOperand( stack , divide );
        else if ( strcmp( s , "x" ) == 0 )
            twoOperand( stack , multiply );
        else if ( strcmp( s , "^" ) == 0 )
            twoOperand( stack , pow );
        else if ( strcmp( s , "^2" ) == 0 ) {
            pushDynArr( stack , 2 );
            twoOperand( stack , pow );
        } else if ( strcmp( s , "^3" ) == 0 ) {
            pushDynArr( stack , 3 );
            twoOperand( stack , pow );
        } else if ( strcmp( s , "abs" ) == 0 )
            singleOperand( stack , fabs );
        else if ( strcmp( s , "sqrt" ) == 0 )
            singleOperand( stack , sqrt );
        else if ( strcmp( s , "exp" ) == 0 )
            singleOperand( stack , exp );
        else if ( strcmp( s , "ln" ) == 0 )
            singleOperand( stack , log );
        else if ( strcmp( s , "log" ) == 0 )
            singleOperand( stack , log10 );
        else {
            double number;

            if ( strcmp( s , "e" ) == 0 ) {
                pushDynArr( stack , E );
            } else if ( strcmp( s , "pi" ) == 0 ) {
                pushDynArr( stack , PI );
            } else if ( isNumber( s , &number ) ) {
                pushDynArr( stack , number );
            } else {
                printf( "%s is neither a number nor an operand exiting now" ,
                        s );
                exit(1);
            }

        }
    }	//end for

    if ( sizeDynArr( stack ) != 1 ) {
        printf( "there was an imbalance number of operators and operands\n" );
        exit(1);
    } else {
        result = topDynArr( stack );
        printf( "\n%f\n" , result );
    }

    return result;
}

int main ( int argc , char** argv ) {
    // assume each argument is contained in the argv array
    // argc-1 determines the number of operands + operators
    if ( argc == 1 )
        return 0;

    calculate( argc , argv );
    return 0;
}
