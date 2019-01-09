/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the header for [CREATURES]. Here, is where most of the
 * implementation takes place
 * 
*******************************************************************************/

#ifndef CREATURE_CLASS
#define CREATURE_CLASS

#include <cstdio>
#include <unistd.h>
#include "Environment.h"

class Creature
{
    // PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE PRIVATE
    private:
    
        int row;
        int column;
        int daysSurvived;
        const int daysToSpawn;
        bool eligibleToSpawn;
        char type; //'D' for doodlebug 'A' for ant
        bool moved;
        Environment *world;


    // PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC PUBLIC
    public: 
    
        /*******************************************************************************
        * 
        * Creature constructors
        * 
        *******************************************************************************/
        Creature (char t, Environment *environ, int days);
        Creature (int r, int c, char t, Environment *environ, int days);
        
        
        /*******************************************************************************
        * 
        * Move the Creature...
        * 
        *******************************************************************************/
        void move (); // to a random location
        void move (int r, int c); // to a specified point
        
        
        /*******************************************************************************
        * 
        * Spawn a Creature within the map
        * 
        *******************************************************************************/
        Creature* spawn ();
        
        
        /*******************************************************************************
        * 
        * Produce a random position within the domain
        * 
        *******************************************************************************/
        void generateNewPosition ();
        
        
        /*******************************************************************************
        * 
        * Getter functions
        * 
        *******************************************************************************/
        char getType (); // get the Creature's type
        int getRow (); // retireve row
        int getCol (); // retrieve column
        bool getMoved (); // get moved
        int getSurvivedDays (); // get daysSurvived
        int getEligibility (); // get daysToSpawn
        int getDaysToSpawn ();  // get daysToSpawn
        bool isEligible (); // get eligibleToSpawn
        Environment *getWorld (); // get the environment
        
        
        /*******************************************************************************
        * 
        * Setter functions
        * 
        *******************************************************************************/
        void setRow (int r); // set row
        void setCol (int c); // set column
        void setMoved (bool m); // set moved
        
        
        /*******************************************************************************
        * 
        * Increase the number of days the Creature has survived
        * 
        *******************************************************************************/
        void incrementSurvived ();
        
        /*******************************************************************************
        * 
        * When the Creature dies, reset the number of days it has survived
        * 
        *******************************************************************************/
        void resetSurvivedDays ();
};

#endif
