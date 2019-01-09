/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the header for the environment in which it alters the map
 * and its population
 * 
*******************************************************************************/

#ifndef ENVIRONMENT_CLASS
#define ENVIRONMENT_CLASS

#include <cstdio>
#include "GridDisplay.h"

class Environment
{
    // PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE
    private:
        
        GridDisplay *grid;
        char **position;
        int rows;
        int cols;
        
    
    // PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC
    public:
    
	    /*******************************************************************************
        * 
        * Class constructor
        * 
        *******************************************************************************/
        Environment (GridDisplay *g);
        
        
        /*******************************************************************************
        * 
        * Getter functions
        * 
        *******************************************************************************/
        int getRows ();
        int getCols ();
        char getCharAtPosition (int r, int c);
        
        
        /*******************************************************************************
        * 
        * Existence functions
        * 
        *******************************************************************************/
        bool isValid (int r, int c);
        bool isOccupied (int r, int c);
        
        
        /*******************************************************************************
        * 
        * Functions that manipulate a Creature
        * 
        *******************************************************************************/
        bool addCreature (char type, int r, int c);
        bool moveCreature (int initR, int initC, int finalR, int finalC);
        bool deleteCreature (int r, int c);
        
        
        /*******************************************************************************
        * 
        * Displays the map
        * 
        *******************************************************************************/
        void showGridWorld ();
};

#endif
