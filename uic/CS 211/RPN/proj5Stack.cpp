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

//#include <iostream>
//using namespace std;

class STACK
{
    public:
    
        // stack class constructor
        STACK ()
        {
            size = 2; // initial size
            
            data = new int [size]; // allocate memory for the stack array
            
            index = 0; // initialize index to be at 0 to represent an empty stack
                       // keeps track of the stack top
        }
        // end STACK()
        
        
        // I have no idea why and/or how I should use this because I'd rather
        // use the above
        void init ()
        {
            size = 2;
            
            data = new int [size];
            
            index = 0;
        }
        // end init()
        
        
        // checks if the "data array" is empty if its index is at 0 or not
        bool isEmpty ()
        {
            return (index == 0) ? true : false;
        }
        // end isEmpty ()
        
        
        // pushes a value into the stack array
        void push (int val)
        {
            int *temp; // temporary array
            
            // increase the array by two [2] when input and index exceeds a certain
            // threshold
            if (index >= size)
            {
                size = size + 2;
                
                temp = new int[size]; // dynamically allocate memory for the temp stack array
                
                for (int x = 0; x < index; x++) // transfer all the data values into the new stack array
                    temp[x] = data[x];
                    
                delete [] data; // delete data
                
                data = temp; // make data point to temp
            }
            
            data[index++] = val; // push value into stack array and increase the index
        }
        // end push ()
        
        
        // returns what is at the top of the stack provided if any
        int top ()
        {
            return (data != NULL) ? data[index - 1] : -999;
        }
        // end top ()
        
        
        // pop the stack
        void pop ()
        {
            int temp;
            
            if (isEmpty()) // error check for empty stack
            {
                puts("STACK IS EMPTY, SOMETHING IS WRONG HERE");
                return;
            }
            
            temp = data[index-1];
            index--; // decrement index because stack was popped
        }
        // end pop ()
        
        
        // reset the stack so that it can be used again and not cause memory leaks
        void reset ()
        {
            delete [] data;
            
            size = 2;
            
            data = new int [size];
            
            index = 0;
            
        }
        // end reset ()
        
        
        /*
        void toString ()
        {
            for (int x = 0; x < index; x++)
                cout << "\nDATA: " << data[x] << endl;;
                
            return;
        }
        */
        
        
        // clean up the memory as to not cause any leaks
        void clean()
        {
            delete [] data;
        }
        // end clean ()
        
        ~STACK ()
        {
            delete [] data;
        }
        
    private:
        
        int *data;  // to be used to contain operators/values
        int size;   // size to be allocated
        int index;  // position to be popped
    
};
// end class STACK
