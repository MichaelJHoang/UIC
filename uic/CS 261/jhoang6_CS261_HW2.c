/***********************************
 * 
 * Name: Jon-Michael Hoang
 * NetID: jhoang6
 * 
 * Class: CS 261
 * 
 * Due Date: February 5th, 2018
 * 
***********************************/


#include <stdio.h>

int anyEvenBit();

/***********************************
 * 
 * PROBLEM NUMBER 1
 * 
***********************************/
int main()
{
    long int val= 83162457113523645; //Part 1
    int result= 0;                   //Part 2
    
    for(;val > 0; val = val/2)       //Part 3 & 4
        result += (val & 1);         //Part 5
        
    printf("ans %d\n",result);
}
//END PROBLEM NUMBER 1


/***********************************
 * 
 * PROBLEM NUMBER 2
 * 
***********************************/
int anyEvenBit (unsigned long int x)
{
                                                                                //ToDo: 01010101 01010101 01010101 01010101 01010101 01010101 01010101 01010101
    unsigned long int MASK_A = 0x55 | (0x55 << 8);                              //produces the first two of the ToDo list
    unsigned long int MASK_B = MASK_A | (MASK_A << 16);                         //produces the next two of the ToDo list
    unsigned long int theMask = MASK_B | (MASK_B << 32);                        //produces the last four of the ToDo list
    unsigned long int masked = (x & theMask);                                   //given an input of 110111, it produces 10101
    
    return !!(masked);                                                          //return masked, which is [return 1] IFF there exists a one (1) in an even-numbered list
}
//END PROBLEM NUMBER 2
