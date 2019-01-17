/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the header for [DOODLEBUG], child class to [CREATURES]
 * 
*******************************************************************************/

#ifndef DOODLEBUG_CLASS
#define DOODLEBUG_CLASS

#include "Creature.h"

class Doodlebug : public Creature
{
    // PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE
    private:
        int lastDayEat;
    
    
    // PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC
    public:
	
	    /*******************************************************************************
        * 
        * Class constructors
        * 
        *******************************************************************************/
        Doodlebug(Environment *environ); // default
        Doodlebug(int r, int c, Environment *environ); // specified
        
        
        /*******************************************************************************
        * 
        * Determines if the Doodlebug can hunt or not. Returns the prey's position if
        * there exists a successful hunt and -1 otherwise.
        * 
        *******************************************************************************/
	    int hunt();
	    
	    
	    /*******************************************************************************
        * 
        * If the Doodlebug starves for three [3] days, it dies
        * 
        *******************************************************************************/
        bool starve();

	    /*******************************************************************************
        * 
        * Returns the number of days eligible for the Doodlebug to breed
        * 
        *******************************************************************************/
        int getEligibility();
};

#endif
