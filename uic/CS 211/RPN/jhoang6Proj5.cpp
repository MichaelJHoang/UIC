/**************************************************
 * 
 * This file contains the user interface code for
 * the Infix Evaluation Project.
 * 
 * Project 5: Infix Evaluation
 * 
 * CS 211 with Patrick Troy
 * 
 * Jon-Michael Hoang | jhoang6
 * 
**************************************************/
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>

using namespace std;

#include "proj5Tokens.h"
#include "proj5Stack.cpp"

bool debugMode = false;

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

// evaluate a given x and y provided an operation
int eval (int x, int y, int op)
{
    switch (op)
    {
        case '+':
            return (x + y);
        case '-':
            return (x - y);
        case '*':
            return (x * y);
        case '/':
            return (x / y);
            
        // base case
        default:
            puts("\noperation error");
            return -999;
    }
}
// end eval ()


// pops the stacks and utilizes the function above to simulate Reverse Polish Notations
int popAndEval (STACK *ops, STACK *vals)
{
    int theOP = ops -> top();
    ops -> pop();
    int y = vals -> top();
    vals -> pop();
    int x = vals -> top();
    vals -> pop();
    if (x != -999 && y != -999)
    {
        int z = eval(x, y, theOP);
        vals->push(z);
    }
    else
        puts("operation error");
}
// end popAndEval ()


// takes in input and runs algorithms to convert infix to postfix so that
// Reverse Polish Notations can be computed
void processExpression(Token inputToken, TokenReader *tr)
{
    /**********************************************/
    /* Declare both stack head pointers here      */
    STACK *operatorStack = new STACK();
    STACK *valueStack = new STACK();
    
    /* Loop until the expression reaches its End */
    while (inputToken.equalsType(EOLN) == false)
    {
        /* The expression contain a VALUE */
        if (inputToken.equalsType(VALUE))
        {
            /* make this a debugMode statement */
            
            if (debugMode)
                printf ("Val: %d, ", inputToken.getValue());
            
            // add code to perform this operation here
            
            // push a value into the valueStack
            valueStack -> push(inputToken.getValue());
            
            //valueStack -> toString();
        }
        
        /**********************************************
         * 
         * Below these comments and until the end of the
         * function follows the "Second and Third" step of
         * the algorithm provided on the rubric. What this
         * algorithm really is is the [Shunting-Yard Algorithm],
         * which allows the conversion of infix to postfix
         * notations as exactly described in the rubric.
         * 
         * More information on the following link:
         * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
         * 
         *********************************************/
        else if (inputToken.equalsType(OPERATOR)) //The expression contains an OPERATOR
        {
            /* make this a debugMode statement */
            if (debugMode)
                printf ("OP: %c, ", inputToken.getOperator());
            
            // add code to perform this operation here
            
            
            if (inputToken.getOperator() == '(')
                operatorStack -> push ('(');
            else if (inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
            {
                while (!operatorStack -> isEmpty() && 
                        operatorStack -> top() == '+' ||
                        operatorStack -> top() == '-' ||
                        operatorStack -> top() == '*' ||
                        operatorStack -> top() == '/')
                    popAndEval(operatorStack, valueStack);
                
                operatorStack -> push (inputToken.getOperator());
            }
            else if (inputToken.getOperator() == '*' || inputToken.getOperator() == '/')
            {
                while (!operatorStack -> isEmpty() && 
                        operatorStack -> top() == '*' ||
                        operatorStack -> top() == '/')
                    popAndEval(operatorStack, valueStack);
                
                operatorStack -> push (inputToken.getOperator());
            }
            else if (inputToken.getOperator() == ')')
            {
                while (!operatorStack -> isEmpty() &&
                        operatorStack -> top() != '(')
                    popAndEval(operatorStack, valueStack);
                
                if (operatorStack -> isEmpty())
                    cout << "THIS IS AN ERROR INDICATING THAT SOMETHING IS WRONG HERE" << endl;
                else
                {
                    operatorStack -> pop();
                }
            }
            
            //operatorStack -> toString();
        }
        
        /* get next token from input */
        inputToken = tr->getNextToken();
    }
    
    /* The expression has reached its end */
    
    // add code to perform this operation here
    while (!operatorStack -> isEmpty())
        popAndEval(operatorStack, valueStack);
    cout << "\nTHE ANSWER IS: " << "[" << valueStack -> top() << "]";
    valueStack -> pop();
    
    if (!valueStack -> isEmpty())
        puts("\n");
        
    printf ("\n");
    
    // clean the inside of the class to prevent memory leaks
    operatorStack -> clean();
    valueStack -> clean();
    
    // clean the outside of the class to prevent memory leaks
    delete [] operatorStack;
    delete [] valueStack;
}
// end processExpression ()


// main
int main (int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    for (int x = 0; x < argc; x++)
        if (strcmp ("-d", argv[x]) == 0)
        {
            debugMode = true;
            puts("\n**********************************************");
            puts("debugMode Activated: Now Debugging Information");
            puts("**********************************************\n");
        }
        
    Token inputToken;
    TokenReader tr;
    
    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");
    
    inputToken = tr.getNextToken();
    
    while (inputToken.equalsType(QUIT) == false)
    {
        /* Check first token on line of input */
        if (inputToken.equalsType(HELP))
        {
            printCommands();
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(ERROR))
        {
            printf ("Invalid Input - For a list of valid commands, type ?\n");
            tr.clearToEoln();
        }
        else if (inputToken.equalsType(EOLN))
        {
            printf ("Blank Line - Do Nothing\n");
            /* blank line - do nothing */
        }
        else
            processExpression(inputToken, &tr);
        
        printf ("\nEnter Expression: ");
        inputToken = tr.getNextToken();
    }
    
    printf ("Quitting Program\n");
    return 1;
}
// end main ()
