/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the .cpp for [DOODLEBUG], child class to [CREATURES]
 * 
*******************************************************************************/

#include "Doodlebug.h"
#include <stdlib.h>
#include <ctime>

/*******************************************************************************
 * 
 * Class constructors
 * 
*******************************************************************************/
Doodlebug::Doodlebug(Environment *environ) : Creature('D', environ, 8) { } // default

Doodlebug::Doodlebug (int r, int c, Environment *environ) : Creature(r, c, 'D', environ, 8) { } // specified


/*******************************************************************************
 * 
 * Determines if the Doodlebug can hunt or not. Returns the prey's position if
 * there exists a successful hunt and -1 otherwise.
 * 
*******************************************************************************/
int Doodlebug::hunt ()
{
  srand(time(0));
  
  Environment* w = getWorld();
  
  int r = getRow();
  int c = getCol();
  int newR = r;
  int newC = c;
  int move;
  int i, j;
  
  bool validDir;
  bool ate = false;
    
	/*******************************************************************************
  * 
  * Generates arbitrary directions
  * 
  *******************************************************************************/
  int randomInts[4];
    
  for(i =0; i < 4; i++)
  {
    do
    {
      validDir = false;
      randomInts[i] = rand() % 4;
      
      for(j = 0; j < i; j++)
        validDir = (randomInts[j] == randomInts[i]) ? true : validDir;
    } while (validDir == true);
  }
    
  for(move = 0; move < 4; move++)
  {
    if(ate)
      break;
    
    switch (randomInts[move])
    {
      case 0:
        newR = (w -> isValid(r + 1, c) && w -> isOccupied(r + 1, c) && w -> getCharAtPosition(r + 1, c) == 'A') ? r + 1 : newR;
        ate = (w -> isValid(r + 1, c) && w -> isOccupied(r + 1, c) && w -> getCharAtPosition(r + 1, c) == 'A') ? true : ate;
        break;
      
      case 1:
        newC = (w -> isValid(r, c + 1) && w -> isOccupied(r, c + 1) && w -> getCharAtPosition(r, c + 1) == 'A') ? c + 1 : newC;
        ate = (w -> isValid(r, c + 1) && w -> isOccupied(r, c + 1) && w -> getCharAtPosition(r, c + 1) == 'A') ? true : ate;
        break;
      
      case 2:
        newR = (w -> isValid(r - 1, c) && w -> isOccupied(r - 1, c) && w -> getCharAtPosition(r - 1, c) == 'A') ? r - 1 : newR;
        ate = (w -> isValid(r - 1, c) && w -> isOccupied(r-1, c) && w -> getCharAtPosition(r - 1, c) == 'A') ? true : ate;
        break;
      
      case 3:
        newC = (w -> isValid(r, c - 1) && w -> isOccupied(r, c - 1) && w -> getCharAtPosition(r, c - 1) == 'A') ? c - 1 : newC;
        ate = (w -> isValid(r, c - 1) && w -> isOccupied(r, c - 1) && w -> getCharAtPosition(r, c - 1) == 'A') ? true : ate;
        break;
      
      default:
        puts("\nERROR");
        ate = false;
        break;
    }
  }
    
  if(ate)
  {
    w -> deleteCreature(newR, newC);
    
    w -> moveCreature(r, c, newR, newC);
    
    setRow(newR);
    setCol(newC);
    
    lastDayEat = 0;
    
    return (newR * 20 + newC);
  }
    
  return -1;
}
// end hunt ()



/*******************************************************************************
 * 
 * If the Doodlebug starves for three [3] days, it dies
 * 
*******************************************************************************/
bool Doodlebug::starve () 
{
  if (lastDayEat >= 3)
  {
    Environment *w = getWorld();
    
    if (w -> deleteCreature(getRow(),getCol()))
      return true;
  }
  else
    lastDayEat++;
    
  return false;
}
// end starve ()


/*******************************************************************************
 * 
 * Returns the number of days eligible for the Doodlebug to breed
 * 
*******************************************************************************/
int Doodlebug::getEligibility () 
{
  return 8;
}
