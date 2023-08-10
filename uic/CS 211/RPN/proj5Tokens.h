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

#include <cstdio>
#include <cstring>
#include <cctype>

// Enumarated Type specifying all of the Tokens
enum TokenType
{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};


// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token();

  // Initialize to a specific TokenType
  Token (TokenType t);

  // Set to a specific TokenType
  void setToType(TokenType t);

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c);

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v);

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t);

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c);

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ();

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue();
};


class TokenReader
{
  private:
    char inputline[300];  // this assumes that all input lines are 300 characters or less in length
    bool needline;
    int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader();

  // Force the next getNextToken to read in a line of input
  void clearToEoln();

  // Return the next Token from the input line
  Token getNextToken();
};

