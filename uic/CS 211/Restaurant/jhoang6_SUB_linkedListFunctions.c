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
 * -doAdd()
 * -doCallAhead()
 * -doWaiting()
 * -doRetrieve()
 * -doList()
 * -doDisplay()
 * 
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jhoang6_restaurantWaitingListSystem.h"

int debugMode;

/**************************************************
 * 
 * adds the group/customer into the waiting line
 * 
**************************************************/
void doAdd (waitList **list, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    
    if (size < 1)
    {
        puts("ERROR");
        return;
    }
 
    /* get group name from input */
    char *name = getName();
    
    if (NULL == name)
    {
        puts("ERROR");
        return;
    }
    
    if (doesNameExist(list, name))
    {
        puts("NAME ALREADY EXISTS");
        return;
    }
    
    if (debugMode)
        displayListInformation(list);
    
    printf("ADDING GROUP [%s] OF SIZE [%d]\n", name, size);
    addToList(list, name, size, 0);
    
    return;
}
//end doAdd()


/**************************************************
 * 
 * reserves the caller to be within the waitlist 
 * 
**************************************************/
void doCallAhead (waitList **list, int debugMode)
{
    /* get group size from input */
    int size = getPosInt();
    
    if (size < 1)
    {
        puts("ERROR");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    
    if (NULL == name)
    {
        puts("ERROR");
        return;
    }
    
    // add code to perform this operation here
    if (doesNameExist(list, name))
    {
        puts("NAME ALREADY EXISTS");
        return;
    }
    
    if (debugMode)
        displayListInformation(list);
    
    printf("CALL-AHEAD GROUP [%s] OF SIZE [%d]\n", name, size);
    addToList(list, name, size, 1);
    
    return;
}
//end doCallAhead();


/**************************************************
 * 
 * changes the call-ahead group to be now within the
 * restaurant
 * 
**************************************************/
void doWaiting (waitList **list, int debugMode)
{
    /* get group name from input */
    char *name = getName();
    
    if (NULL == name)
    {
        puts("ERROR");
        return;
    }
    
    printf ("CALL-AHEAD GROUP [%s] IS NOW WAITING IN THE RESTAURANT\n", name);
    
    // add code to perform this operation here
    if (!doesNameExist(list, name))
    {
        if (debugMode)
            displayListInformation(list);
        
        puts("NAME ALREADY EXISTS");
        return;
    }
    
    if (updateStatus(list, name, debugMode) == 0)
        return;
        
    updateStatus(list, name, debugMode);
    
    return;
}
//end doWaiting();


/**************************************************
 * 
 * allows the first customer within the waiting
 * line to be seated at a table
 * 
**************************************************/
void doRetrieve (waitList **list, int debugMode)
{
    /* get table size from input */
    int size = getPosInt();
    
    if (size < 1)
    {
        puts("ERROR");
        return;
    }
 
    clearToEoln();
 
    printf ("RETRIEVE AND REMOVE THE FIRST GROUP THAT CAN FIT A TABLE OF SIZE [%d]\n", size);

    // add code to perform this operation here
    retrieveAndRemove (list, size, debugMode);
    
    return;
}
//end doRetrieve();


/**************************************************
 * 
 * displays the groups ahead of group [x]
 * 
**************************************************/
void doList (waitList **list, int debugMode)
{
    /* get group name from input */
    char *name = getName();
    
    if (NULL == name)
    {
        puts("ERROR");
        return;
    }
 
    // add code to perform this operation here
    if (doesNameExist(list, name))
    {
        printf ("THE AMOUNT OF GROUPS AHEAD OF GROUP [%s] is [%d]\n", name, countGroupsAhead(list, name, debugMode));
        
        printf ("GROUP [%s] IS BEHIND:\n", name);
        
        displayGroupSizeAhead(list, countGroupsAhead(list, name, debugMode));
        
        return;
    }
    
    puts("ERROR");
    return;
}
//end doList();


/**************************************************
 * 
 * displays the entire wait-list roster
 * 
**************************************************/
void doDisplay (waitList **list)
{
    clearToEoln();
    
    // add code to perform this operation here
    displayListInformation(list);
}
//end doDisplay();
