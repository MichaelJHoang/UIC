/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the header file for [ANTS], child class to [CREATURES]
 * 
*******************************************************************************/

#ifndef ANT_CLASS
#define ANT_CLASS

#include "Creature.h"

class Ant : public Creature
{
    public:
        
        // ant constructor
        Ant(int r, int c, Environment* environ);
        
        // ant constructor
        Ant(Environment* environ);
        
        // function to determine whether or not the ant is eligible to spawn a child
        int getEligibility();
};

#endif
