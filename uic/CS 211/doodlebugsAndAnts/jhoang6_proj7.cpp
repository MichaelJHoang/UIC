/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is driver program for Project 7: Doodlebugs and Ants
 * 
*******************************************************************************/

#include "Environment.h"
#include "Ant.h"
#include "Doodlebug.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

int main (int argc, char** argv)
{
 srand(time(0));
 int i;
 int waitTime = 1000;
 Creature **creatureTracker;
 
 /*******************************************************************************
 * 
 * Read in command line arguments
 * 
 *******************************************************************************/
 for(i = 0; i< argc; i++){
  if(argv[i] && argv[i + 1] && strcmp(argv[i], "-d") == 0)
   waitTime = atoi(argv[i + 1]); 
 }
 
 /*******************************************************************************
 * 
 * Create the map
 * 
 *******************************************************************************/
 GridDisplay gd(20, 20);
 Environment env(&gd);
 creatureTracker = new Creature* [20 * 20];
 
 /*******************************************************************************
 * 
 * LET THERE BE DOODLEBUGS
 * 
 *******************************************************************************/
 for (i = 0 ; i < 5 ; i++)
 {
   Creature* DB = new Doodlebug(&env);
   DB -> generateNewPosition();
   env.addCreature(DB -> getType(), DB -> getRow() , DB -> getCol());
   creatureTracker[20 * DB->getRow() + DB -> getCol()] = DB;
 }
 
 /*******************************************************************************
 * 
 * LET THERE BE ANTS
 * 
 *******************************************************************************/
 for (i = 0; i < 150; i++)
 {
   Creature* A = new Ant(&env);
   A -> generateNewPosition();
   env.addCreature(A -> getType(), A -> getRow() , A -> getCol());
   creatureTracker[20 * A -> getRow() + A -> getCol()] = A;
 }
 
 /*******************************************************************************
 * 
 * Display the map. Everythin below here processes a day within the map.
 * 
 *******************************************************************************/
 gd.showGrid();
 
 bool hunted = false; 
 
 while(true)
 {
  gd.mySleep(waitTime);
  for(i = 0; i< 400; i++)
  {
   Creature* crtrTmp = creatureTracker[i];
   
   if(crtrTmp)
   {
    if(crtrTmp->getType() == 'D' && !crtrTmp -> getMoved())
    {
     int prey = ((Doodlebug*)crtrTmp) -> hunt();
     
     hunted = prey + 1;
     
     if (hunted && !crtrTmp -> getMoved())
     {
       delete creatureTracker[prey];
       
       creatureTracker[prey] = NULL; 
       
       creatureTracker[prey] = crtrTmp;
       
       creatureTracker[i] = NULL;
       
       crtrTmp -> setMoved(true);
     }
    
    
      if (!hunted && !crtrTmp -> getMoved())
      {
         crtrTmp -> move();
         crtrTmp -> setMoved(true);
         
         if ((env.isValid(crtrTmp -> getRow(), crtrTmp -> getCol())) && i != (20 * crtrTmp -> getRow() + crtrTmp -> getCol()))
         {
          creatureTracker[20 * crtrTmp -> getRow() + crtrTmp -> getCol()] = crtrTmp;
          creatureTracker[i] = NULL;
         }
      }
     
      crtrTmp->incrementSurvived();
      
      if(crtrTmp->getSurvivedDays() >= crtrTmp->getDaysToSpawn())
      {
       Creature* child = crtrTmp->spawn();
       
       if(child)
       { 
        if(env.addCreature(child -> getType(), child -> getRow(), child -> getCol()))
        {
         creatureTracker[20 * child -> getRow() + child -> getCol()] = child;
         crtrTmp -> resetSurvivedDays();
        }
       }
      }
      
      bool starved = ((Doodlebug*)crtrTmp) -> starve();
      
      if(starved)
      {
       delete crtrTmp;
       creatureTracker[i] = NULL;
      }
    }
   }
   
   hunted = false;
  }
  
  for(i = 0; i< 400; i++)
  {
   Creature* crtrTmp = creatureTracker[i];
   
   if(crtrTmp)
   {
     if(crtrTmp -> getType() == 'A' && !crtrTmp -> getMoved())
     {
       crtrTmp->move();
       crtrTmp->setMoved(true);
       
       if ((env.isValid(crtrTmp -> getRow(), crtrTmp -> getCol())) &&  (i != (20 * crtrTmp -> getRow() + crtrTmp -> getCol())))
       {
        creatureTracker[i] = NULL;
        creatureTracker[20 * crtrTmp -> getRow() + crtrTmp -> getCol()] = crtrTmp;
       }
       
       crtrTmp -> incrementSurvived();
       
       if(crtrTmp -> getSurvivedDays() >= crtrTmp -> getDaysToSpawn())
       {
        Creature* child = crtrTmp -> spawn();
        
        if(env.addCreature(child -> getType(), child -> getRow(), child -> getCol()) && child)
        {
         creatureTracker[20 * child -> getRow() + child -> getCol()] = child;
         crtrTmp -> resetSurvivedDays();
        }
       }
     }
   }
  }
  
  for(i = 0; i< 400; i++)
  {
   if(creatureTracker[i])
     creatureTracker[i] -> setMoved(false);
  }

   gd.showGrid();
   printf("\n");
 }
  
 return 0;
}
