/**************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * Program 4: Restaurant Waiting System
 * CS 211
 * 
**************************************************/

/**************************************************
 * 
 * This file contains functions for:
 * 
 * -addToList()
 * -doesNameExist()
 * -updateStatus()
 * -retrieveAndRemove()
 * -countGroupsAhead()
 * -displayGroupSizeAhead()
 * -displayListInformation()
 * 
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jhoang6_restaurantWaitingListSystem.h"

extern debugMode;

/**************************************************
 * 
 * this operation is to add a new node to the end of the linked list. This is to be
 * used when the a and c commands are given as input.
 * 
**************************************************/
void addToList (waitList **list, char *name, int size, int theStatus)
{
    waitList *LIST = (waitList*) malloc(sizeof(waitList));
    
    LIST -> name = name;
    LIST -> groupSize = size;
    
    LIST -> status = (theStatus == 0) ? 0 : 1;
    
    LIST -> next = NULL;
    
    if (*list == NULL)
    {
        *list = LIST;
        return;
    }
    
    waitList *temp = *list;
    
    while (temp -> next != NULL) 
        temp = temp -> next;
    
    temp -> next = LIST;
    
    return;
}
//end addToList();


/**************************************************
 * 
 * this operation is to return a Boolean value indicating whether a name
 * already exists in the linked list. This is to be used when the a, c, w and l commands are given as
 * input.
 * 
**************************************************/
int doesNameExist (waitList **list, char *name)
{
    waitList *temp = *list;
    
    if(temp == NULL)
        return 0;
    
    while (temp != NULL)
    {
        if(strcmp(temp -> name, name) == 0)
            return 1;
        temp = temp -> next;
    }
    
    return 0;
}
//end doesNameExist();


/**************************************************
 * 
 * this operation is to change the in-restaurant status when a call-ahead group
 * arrives at the restaurant. This operation will return a FALSE value if that group is already
 * marked as being in the restaurant. This is to be used when the w command is given as input
 * 
**************************************************/
int updateStatus (waitList **list, char *name, int debugMode)
{
    int x = 1;
    
    char *theStatus;
    
    waitList *temp = *list;
    
    if (temp == NULL)
    {
        puts("EMPTY LIST - CANNOT UPDATE");
        return 0;
    }
    
    if (debugMode)
    {
        puts("debugMode\n#\tNAME\tSIZE\tSTATUS\n");
        
        while (temp != NULL)
        {
            theStatus = (temp -> status == 0) ? "PRESENT" : "ABSENT";
                
            printf("%d\t%s\t%d\t%s\n", x, temp->name, temp->groupSize, theStatus);
            x++;
        }
    }
        
    while (temp != NULL)
    {
        if (strcmp(temp -> name, name) == 0)
        {
            if (temp -> status == 0)
                return 0;
            temp -> status = 0;
            return 1;
        }
        
        temp = temp -> next;
    }
    
    return 0;
}
//end updateStatus();


/**************************************************
 * 
 * this operation is to find the first in-restaurant group that can fit at a
 * given table. This operation is to return the name of group. This group is to be removed from the
 * linked list. This is to be used when the r command is given as input
 * 
**************************************************/
void retrieveAndRemove (waitList **list, int table, int debugMode)
{
    waitList *temp = *list;
    waitList *p;
    
    char *theStatus;
    
    int x = 1;
    
    if (temp == NULL)
    {
        puts("EMPTY LIST");
        return;
    }
    
    if (temp -> groupSize <= table && temp -> status == 0)
    {
        *list = (*list) -> next;
        
        free(temp);
        
        if (debugMode)
            displayListInformation(list);
            
        return;
    }
    
    if (debugMode)
    {
        puts("debugMode\n#\tNAME\tSIZE\tSTATUS\n");
        
        while (temp != NULL)
        {
            theStatus = (temp -> status == 0) ? "PRESENT" : "ABSENT";
                
            printf("%d\t%s\t%d\t%s\n", x, temp->name, temp->groupSize, theStatus);
            x++;
        }
    }
    
    while (temp -> next != NULL)
    {
        if (temp -> next -> groupSize <= table)
        {
            if (temp -> next -> status == 0)
            {
                p = temp -> next;
                temp -> next = p -> next;
                
                free(p);
                
                return;
            }
        }
        
        temp = temp -> next;
    }
    
    puts("NO VALID GROUP SIZE FOR THE TABLE");
    
    return;
}
//end retrieveAndRemove()


/**************************************************
 * 
 * This operation is to return the number of groups waiting ahead of a
 * group with a specific name. This is to be used when the l command is given as input.
 * 
**************************************************/
int countGroupsAhead (waitList **list, char *name, int debugMode)
{
    waitList *temp = *list;
    
    char *theStatus;
    
    int numAhead = 0;
    int x = 1;
    
    if (temp == NULL)
        return 0;
    
    if (debugMode)
    {
        puts("debugMode\n#\tNAME\tSIZE\tSTATUS\n");
        
        while (temp != NULL)
        {
            theStatus = (temp -> status == 0) ? "PRESENT" : "ABSENT";
                
            printf("%d\t%s\t%d\t%s\n", x, temp->name, temp->groupSize, theStatus);
            x++;
        }
    }
        
    while (temp != NULL)
    {
        if (strcmp(temp -> name, name) == 0)
            return numAhead;
            
        numAhead++;
        
        temp = temp -> next;
    }
    
    return 0;
}
//end countGroupsAhead();


/**************************************************
 * 
 * this operation traverses down the list until a specific group name
 * is encountered. As each node is traversed, print out that node’s group size. This command is to
 * be used when the l command is given
 * 
**************************************************/
void displayGroupSizeAhead (waitList **list, int ahead)
{
    waitList *temp = *list;
    
    int count = 1;
    
    char *theStatus;
    
    if (temp == NULL)
    {
        puts("EMPTY LIST");
        return;
    }
    
    if ((count - 1) == ahead)
    {
        puts("NO GROUPS AHEAD");
        return;
    }
    
    puts("#\tNAME\tSIZE\tSTATUS\n");
    
    while ((count - 1) != ahead && temp != NULL)
    {
        theStatus = (temp -> status == 0) ? "PRESENT" : "ABSENT";
            
        printf("%d\t%s\t%d\t%s\n", count, temp->name, temp->groupSize, theStatus);
        
        temp = temp -> next;
        
        count++;
    }
    
    return;
}
//end displayGroupSizeAhead()


/**************************************************
 * 
 * this operation to traverse down the entire list from beginning to
 * end. As each node is traversed, print out that node’s group name, group size and in-restaurant
 * status. This command is to be used when the d command is given as input.
 * 
**************************************************/
void displayListInformation (waitList **list)
{
    int x = 1;
    waitList *temp = *list;
    char *theStatus;
    
    if (temp == NULL)
    {
        puts("EMPTY LIST");
        return;
    }
    
    puts("#\tNAME\tSIZE\tSTATUS");
    
    while (temp != NULL)
    {
        theStatus = (temp -> status == 0) ? "PRESENT" : "ABSENT";
            
        printf("%d\t%s\t%d\t%s\n", x, temp->name, temp->groupSize, theStatus);
		temp = temp->next;
		x++;
    }
    
    return;
}
//end display ListInformation();
