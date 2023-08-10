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

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/

#include "proj5Tokens.h"

Token::Token()
{
    type = ERROR;
    op = '$';
    val = -999;
}

// initialize to a specific TokenType
Token::Token (TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// set to a specific TokenType
void Token::setToType (TokenType t)
{
    type = t;
    op = '$';
    val = -999;
}

// set to an OPERATOR TokenType with specific operator values
void Token::setToOperator (char c)
{
    type = OPERATOR;
    op = c;
    val = -999;
}

// set to a VALUE TokenType with a specific numeric value
void Token::setToValue (int v)
{
    type = VALUE;
    op = '$';
    val = v;
}

// return true if the Current Token is of the given TokenType
bool Token::equalsType (TokenType t)
{
    if (type == t)
        return true;
    return false;
}

// return true if the current token is of the OPERATOR TokenType
// and contains the given operator character
bool Token::equalsOperator (char c)
{
    if (type == OPERATOR && op == c)
        return true;
    return false;
}

// return the operator for the current Token
// and verify if the current Token is of the OPERATOR TokenType
char Token::getOperator ()
{
    if (type == OPERATOR)
        return op;
    return '$'; // using $ to indicate an error value
}

// return the value for the current token
// verify the current token is of the value TokenType
int Token::getValue()
{
    if (type == VALUE)
        return val;
    return -999;
}

// initialize the TokenReader class to read from standard input
TokenReader::TokenReader()
{
    // set to read from standard input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
}

// force the next getNextToken to read in a line of input
void TokenReader::clearToEoln()
{
    needline = true;
}

// return the next token from the input line
Token TokenReader::getNextToken()
{
    char *endCheck;
    
    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);
    
    // get a new line of input from the user
    if (needline)
    {
        endCheck = fgets(inputline, 300, stdin);
        
        if (endCheck == NULL)
        {
            printf ("Error in reading");
            Token t(EOFILE);
            return t;
        }
        
        for (int i = 0; i < strlen(inputline); i++)
            if (inputline[i] == '\n')
        
        strcat (inputline, " "); // add a space at end to help deal with digit calculation
        needline = false;
        pos = 0;
    }
    
    // skip over any white space characters in the beginning of the input
    while (pos < strlen(inputline) && isspace(inputline[pos]))
        pos++;
        
    if (pos >= strlen(inputline))
    {
        // at end of line
        needline = true;
        Token t(EOLN);
        return t;
    }
    
    // get the next character from the input line
    char ch = inputline[pos]; pos++;
    
    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ('q' == ch || 'Q' == ch)
        return Token (QUIT);
    
    // check if "?" was entered ==> HELP Token
    if ('?' == ch)
        return Token (HELP);
    
    // check for the Operator values of: + - * / ( ) ==> OPERATOR Token
    if (('+' == ch) ||
        ('-' == ch) ||
        ('*' == ch) ||
        ('/' == ch) ||
        ('(' == ch) ||
        (')' == ch))
    {
        Token t;
        t.setToOperator(ch);
        return t;
    }
    
    // check for a number ==> VALUE token
    if (isdigit(ch))
    {
        int number = int(ch) - int('0'); // subtract ascii value of ch from ascii value of '0'
        ch = inputline[pos]; pos++;
        
        while (isdigit(ch))
        {
            number = number * 10 + int(ch) - int('0');
            ch = inputline[pos]; pos++;
        }
        
        pos--; //since number calculation checks one character after the last digit
        Token t;
        t.setToValue(number);
        return t;
    }
    
    // input is not valid if the code to get to this part ==> ERROR Token
    return Token (ERROR);
}
