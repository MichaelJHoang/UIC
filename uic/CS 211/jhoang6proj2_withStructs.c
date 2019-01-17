/***********************************
 * 
 * Name: Jon-Michael Hoang
 * NetID: jhoang6
 * 
 * Class: CS 211
 * 
 * Due Date: February 15th, 2018
 * 
 * https://www.geeksforgeeks.org/check-for-balanced-parentheses-in-an-expression/
 * 
***********************************/

#include <stdio.h>
#include <stdlib.h>

//bool debugMode = false;

/**************************************************
 * 
 * create a struct stack/linked list
 * 
 * ***********************************************/
struct stack
{
    char data;
    struct stack *next;
};


/**************************************************
 * 
 * push data to top of stack
 * 
 * ***********************************************/
void push (struct stack **top, int newData)
{
    //allocate space for stack
    struct stack *list = (struct stack*) malloc (sizeof(struct stack));
    
    if (list == NULL)
    {
        printf("stack overflow");
        getchar();
        exit(0);
    }
    
    //put in new data
    list->data = newData;
    
    //link the old list off the new stack
    list->next = (*top);
    
    //move the head to point to newData
    (*top) = list;
}
//end push()


/**************************************************
 * 
 * pop the stack
 * 
 * ***********************************************/
int pop(struct stack **top)
{
    char temp;
    struct stack *list;
    
    if (*top == NULL)
    {
        printf ("stack overflow");
        getchar();
        exit(0);
    }
    else
    {
        list = *top;
        temp = list->data;
        *top = list->next;
        free(list);
        return temp;
    }
}
//end pop()


/**************************************************
 * 
 * checks if there exists anything in the stack
 * 
 * ***********************************************/
int isEmpty (struct stack **theStack)
{
    if (theStack == NULL)
        return 1; //stack is empty, return 1
    else
        return 0; //stack is not empty, return 0
}
//end isEmpty()


/**************************************************
 * 
 * returns 1 IFF matching parenthesis
 * 
 * ***********************************************/
int match (char first, char second)
{
    if (first == '(' && second == ')')
        return 1;
    else if (first == '{' && second == '}')
        return 1;
    else if (first == '[' && second == ']')
        return 1;
    else if (first == '<' && second == '>')
        return 1;
    else
        return 0;
}
//end match()


/**************************************************
 * 
 * checks if balanced
 * 
 * ***********************************************/
int checkBalance (char array[])
{
    int x = 0;
    
    //temp stack struct
    struct stack *temp = NULL;
    
    //run through arrayay to check for pairs
    while (array[x])
    {
        //if array[x] is a left parenthesis, push it into the stack
        if (array[x] == '(' || array[x] == '{' || array[x] == '[' || array[x] == '<')
            push(&temp, array[x]);
        
        //if array[x] is a right parenthesis, pop from stack and check if popped
        //parenthesis is a matching pair
        if (array[x] == ')' || array[x] == '}' || array[x] == ']' || array[x] == '>')
        {
            //return 0 if no pairs/nothing in the stack to match it with
            if (isEmpty(&temp))
                return 0;
            //pop the stack and if it is not a pair, then there is a mismatch
            else if (!match(pop(&temp), array[x]))
                return 0;
        }
        
        x++;
    }
    
    //if there is something left, then there should exist a left parenthesis
    //without a right one
    if (temp == NULL)
        return 1; //balanced
    else
        return 0; //not balanced
}
//end checkBalance()


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


int main ()
{
    printID();
    
    char input[300] = "<><><><><><><><><><><><><><><><><><><><><><><><><><><><><>";
    
    FILE *pfile;
    
    pfile = fopen ("sometext.txt", "x");
    
    if (pfile == NULL)
        perror ("ERROR");
    else
    {
        if (fgets(input, 300, stdin) != NULL)
            puts (input);
        fclose (pfile);
    }
    
    if (checkBalance(input))
        printf("Hooray, they're balanced! Are you on a balanced diet?");
    else
        printf("They're not balanced!");
    
    return 0;
}
//end main()