/**************************************************
 * 
 * libraries used for the program and global variable
 * used for debugging
 * 
 * ***********************************************/

#include <ctype.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/**************************************************
 * 
 * How the toggle works - think of a light switch:
 * When the lever is up, the lights are on and off when down,
 * there is no inbetween. Now think of a graph with the
 * x-axis intersecting the middle of the switch. When the lever
 * is up, the y-value is 1 and -1 when down. This is simply
 * done by multiplying the switch by -1 to invert it
 * about the axis.
 * 
 * ***********************************************/
int debugMode = -1;



/**************************************************
 * 
 * Prints out identifying information
 * 
 * ***********************************************/
void printID ()
{
    printf ("Author: Jon-Michael Hoang\n");
    printf ("Class: CS 211\n");
    printf ("Lab: Fridays at 10:00 AM\n");
    printf ("Project 2: Balanced Symbol Checker \n\n");
}
//end printID()


/**************************************************
 * 
 * Prints out instructions on how to run the program
 * 
 * ***********************************************/
void printInstructions()
{
    printf ("Simply enter some arbitrary string with parenthesis in them and I will see if they are balanced or not:\n\n");
}
//end printInstructions()


/**************************************************
 * 
 * Create a struct stack defined with size, a top,
 * and pointer to the stack which creates the
 * dynamically allocated arrays
 * 
 * ***********************************************/
typedef struct theStack
{
    int size;
    int top;
    char* pointerToStack;
}stack;
//end theStack


/**************************************************
 * 
 * Create the stack
 * 
 * ***********************************************/
void makeStack (stack* STACK)
{
    STACK -> size = 2;
    STACK -> pointerToStack = (char*) malloc(STACK -> size * sizeof(char));
    STACK -> top = 0;
}
//end makeStack()


/**************************************************
 * 
 * Returns a flag indicating whether or not the
 * stack has something inside it
 * 
 * ***********************************************/
int isEmpty (stack* STACK)
{
    int flag = (STACK == NULL) ? 1 : 0;
    
    return flag;
}
//end isEmpty


/**************************************************
 * 
 * Returns the value of the top of the array
 * 
 * ***********************************************/
char top (stack* STACK)
{
    if (!isEmpty(STACK) && (STACK -> top > 0))
        return (STACK -> pointerToStack[STACK -> top - 1]);
}
//end top()


/**************************************************
 * 
 * Whenever there is no space left for input on the
 * stack, increase the stack space by 2 after allocating
 * some memory for it
 * 
 * ***********************************************/
char increase (stack* STACK)
{
    char *temp = (char*) malloc(STACK -> size * sizeof(char) + sizeof(char) * 2);
    
    for (int x =0; x < STACK -> top; x++)
        temp[x] = STACK -> pointerToStack[x];
    
    free (STACK -> pointerToStack);
    STACK -> pointerToStack = temp;
    STACK -> size = STACK -> size + 2;
}
//end increase()


/**************************************************
 * 
 * Pushes the brackets into the stack
 * 
 * ***********************************************/
void push (stack* STACK, char CHAR)
{
    if (isprint(CHAR))
    {
        if (STACK -> top < STACK -> size)
        {
            STACK -> pointerToStack[STACK -> top] = CHAR;
            STACK -> top++;
            
            if (debugMode == 1)
                printf("\n\nDebugging Information: The character %c was pushed into the stack.\n\n", top(STACK));
        }
    }
    else
    {
        increase(STACK);
        
        if (debugMode == 1)
            printf("\n\nDebugging Information:\nThe array has risen by two with size of %d\n\n", STACK -> size);
            
        push(STACK, CHAR);
    }
}
//end push()


/**************************************************
 * 
 * Pop the stack and reduce its size
 * 
 * ***********************************************/
void pop (stack* STACK)
{
    if (debugMode == 1)
        printf("\n\nDebugging Information: A(n) %c was popped.\n\n", top(STACK));
        
    STACK -> top--;
}
//end pop()


/**************************************************
 * 
 * Reset the stack
 * 
 * ***********************************************/
void reset(stack* STACK)
{
    free(STACK -> pointerToStack);
    makeStack(STACK);
    
    printf ("\nThe stack was resetted and is now ready for use again!\n");
}
//end reset()


/**************************************************
 * 
 * Error checking to see if the string is balanced or not.
 * If not, displays where the error is located.
 * 
 * What it also does is that it utilizes the stack to push
 * and pop brackets inside it so that it can see if it's
 * balanced or not.
 * 
 * ***********************************************/
void isBalanced(stack* STACK, char* input)
{
    int x = 0;
    char current;
    
    while(input[x] != '\0')
    {
        current = input[x];
        if (current == '(' || current == '{' || current == '[' || current == '<')
            push(STACK, current);
        else if (current == ')' || current == '}' || current == ']' || current == '>')
        {
            if(top(STACK) != current - 2 && top(STACK) != current - 1 && STACK -> top != 0)
            {
                for(int y = 0; y < x; y++)
                    printf(" ");
                    
                if(top(STACK) == '(')
                    printf("^ expecting %c\n", top(STACK)+1);
                else
                    printf("^ expecting %c\n", top(STACK)+2);
                
                return;
            }
            else if(STACK -> top == 0)
            {
                for(int y = 0; y < x; y++)
                    printf(" ");
                printf("^ missing ");
                
                if(current == '(')
                    printf("%c", current-1);
                else
                    printf("%c", current-2);
                printf("\n");
                
                return;
            }
            
            pop(STACK);
        }

            if(input[x + 1] == '\0' && STACK -> top != 0)
            {
                for(int y = 0; y < x+1; y++)
                    printf(" ");
                printf("^ missing");

                while(STACK -> top != 0)
                {
                    if(top(STACK) == '(')
                        printf(" %c", top(STACK)+1);
                    else
                        printf(" %c", top(STACK)+2);
                    
                    pop(STACK);
                }
                printf("\n");
                return;
        }
        x++;
    }
    printf("This is balanced\n");
}
//end isBalanced()


/**************************************************
 * 
 * Main function where it is supposed to read in
 * files rather than ask for input directly and
 * sees if the parenthesis provided is balanced or not
 * 
 * ***********************************************/
int main (int userInputValue, char** userInputArray)
{
    printID();
    printInstructions();
    char input [300];
    char something[] = "something\n";
    char SOMETHING[] = "SOMETHING\n";
    
    stack ARRAY;
    
    makeStack(&ARRAY);
    
    for (int x = 0; x < userInputValue; x++)
        if(strcmp ("-d", userInputArray[x]) == 0)
            debugMode *= -1;
            
    do
    {
        fgets(input, 300, stdin);
        if (input[0] != '\0' && ((strcmp(something, input) != 0) && strcmp(SOMETHING, input) != 0))
            isBalanced(&ARRAY, input);
    } while ((strcmp(something, input) != 0) && (strcmp(SOMETHING, input) != 0));
    
    return 0;
}
//end main()