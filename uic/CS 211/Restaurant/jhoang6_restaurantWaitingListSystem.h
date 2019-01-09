/**************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * Program 4: Restaurant Waiting System
 * CS 211
 * 
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;

/**************************************************
 * 
 * singly linked list used for the waiting line
 * 
**************************************************/
typedef struct node
{
	int status;
	int groupSize;
	char *name;
	struct node *next;
} waitList;
//end node


/**************************************************
 * 
 * functions within userInterface.c, in order
 * 
**************************************************/
void clearToEoln();
int getNextNWSChar();
int getPosInt();
char *getName();
void printCommands();
//int main();
//end userInterface.c


/**************************************************
 * 
 * functions within linkedListFunctions.c, in order
 * 
**************************************************/
void doAdd(waitList **list, int debugMode);
void doCallAhead(waitList **list, int debugMode);
void doWaiting(waitList **list, int debugMode);
void doRetrieve(waitList **list, int debugMode);
void doList(waitList **list, int debugMode);
void doDisplay(waitList **list);
//end linkedListFunctions.c


/**************************************************
 * 
 * functions within linkedListImp.c, in order
 * 
**************************************************/
void addToList(waitList **list, char *name, int size, int theStatus);
int doesNameExist(waitList **list, char *name);
int updateStatus(waitList **list, char *name, int debugMode);
void retrieveAndRemove(waitList **list, int table, int debugMode);
int countGroupsAhead(waitList **list, char *name, int debugMode);
void displayGroupSizeAhead(waitList **list, int ahead);
void displayListInformation(waitList **list);
//end linkedListImp.c
