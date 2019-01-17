/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the .cpp file for [ANTS], child class to [CREATURES]
 * 
*******************************************************************************/

#include "Ant.h"

// ant constructor
Ant::Ant (int r, int c, Environment *environ) : Creature(r, c, 'A', environ, 3) { }

// another ant constructor
Ant::Ant (Environment *environ) : Creature('A', environ, 3) { }

// function to determine whether or not the ant gets preggers
int Ant::getEligibility()
 {
	 return 3;
 }
