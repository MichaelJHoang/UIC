/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the .cpp file for [CREATURES]. Here, is where most of the
 * implementation takes place
 * 
*******************************************************************************/

#include "Creature.h"
#include <ctime>
#include <stdlib.h>


/*******************************************************************************
 * 
 * Creature constructors
 * 
*******************************************************************************/
Creature::Creature (char t, Environment *environ, int days) : row(0), column(0), daysSurvived(0), type(t), world(environ), eligibleToSpawn(false), daysToSpawn(days) { }

Creature::Creature (int r, int c, char t, Environment *environ, int days) : row(r), column(c), daysSurvived(0), type(t), world(environ), eligibleToSpawn(false), daysToSpawn(days) { }


/*******************************************************************************
 * 
 * Returns the Creature's type, be it an Ant or Doodlebug
 * 
*******************************************************************************/
char Creature::getType ()
{
    return type;
}
// end getType ()


/*******************************************************************************
 * 
 * Move the Creature to some arbitrary location
 * 
*******************************************************************************/
void Creature::move ()
{
  srand(time(0));
  
  int randomInt;
  int newCol = column;
  int newRow = row;
  
  bool up = false, down = false, left = false, right = false;
  
  /*******************************************************************************
  * 
  * Algorithm for random movements 
  * 
  *******************************************************************************/
  while (randomInt != -999 && (!up|| !left || !right || !down))
  {
    newRow = row;
    newCol = column;
    randomInt = (rand() % 3) + 0;
    
    switch (randomInt)
    {
      // go up
      case 0:
        newRow++;
        up = true;
        break;
        
      // go down
      case 1:
        newRow--;
        down = true;
        break;
        
      // go left
      case 2:
        newCol--;
        left = true;
        break;
      // go right
      case 3:
        newCol += 1;
        right = true;
        break;
    }
    
    randomInt = (world -> isValid(newRow, newCol) && !world -> isOccupied(newRow, newCol)) ? -999 : randomInt;
  }
  
  row = (world -> moveCreature(row, column, newRow, newCol)) ? newRow : row;
  column = (world -> moveCreature(row, column, newRow, newCol)) ? newCol : column;
  
  return;
}
// end move ()


/*******************************************************************************
  * 
  * Move the Creature to a specific point
  * 
*******************************************************************************/
void Creature::move (int r, int c)
{
  row = (world -> isValid(r, c) && world -> moveCreature(row, column, r, c) && !world -> isOccupied(r, c)) ? r : row;
  column = (world -> isValid(r, c) && world -> moveCreature(row, column, r, c) && !world -> isOccupied(r, c)) ? c : column;
  
  return;
}
// end move ()


/*******************************************************************************
  * 
  * Spawn a Creature within the map
  * 
*******************************************************************************/
Creature* Creature::spawn ()
{
  srand(time(0));
  
  int r = getRow();
  int c = getCol();
  int newR = r + 1;
  int newC = c;
  int i, j;
  
  /*******************************************************************************
  * 
  * Check surroundings
  * 
  *******************************************************************************/
  int randomInts[4];
    
  for(i = 0; i <= 3; i++) 
  {
    bool validDir;
    
    do
    {
      validDir = false;
        
      randomInts[i] = rand() % 4;
        
      for(j = 0; j < i; j++)
        validDir = (randomInts[j] == randomInts[i]) ? true : validDir;
        
    } while (validDir);
  }
  
  int randomInt; 
  bool done = false;
  
  for(int i = 0; i< 4; i++)
  {
    if(done)
      break;
    
    randomInt = randomInts[i];
    
    switch(randomInt)
    {
      case 0:
        newC = (world -> isValid(r, c - 1) && !world -> isOccupied(r, c - 1)) ? c - 1 : newC;
        break;
        
      case 1:
        newR = (world -> isValid(r + 1,c) && !world -> isOccupied(r + 1, c)) ? r + 1 : newR;
        break;

      case 2:
        newC = (world -> isValid(r, c + 1) && !world -> isOccupied(r, c + 1)) ? c + 1 : newC;
        break;
        
      default:
        newR = (world -> isValid(r - 1, c) && !world -> isOccupied(r - 1, c)) ? r - 1 : newR;
        break;
    }
  }
    
    /*******************************************************************************
    * 
    * Spawn in random surrounding
    * 
    *******************************************************************************/
    if((newR != r || newC != c) && world -> isValid(newR, newC) && !world -> isOccupied(newR, newC))
    {
        Creature* child = new Creature(newR, newC, getType(), world, getDaysToSpawn());
          
        return child;
    }
    
    
    return NULL;
}
// end spawn ()


/*******************************************************************************
* 
* Produce a random position within the domain
* 
*******************************************************************************/
void Creature::generateNewPosition ()
{
  //srand (time(0));
  
  bool valid = false;
  while (!valid) 
  {
    row = rand() % 20;
    column = rand() % 20;
    
    valid = (world -> isValid(row, column) && !world -> isOccupied(row, column)) ? true : valid;
  }
  
  return;
}
// end generateNewPosition ()


/*******************************************************************************
* 
* Returns the Creature's row
* 
*******************************************************************************/
int Creature::getRow ()
{
  return (row > -1 && row < 20) ? row : -999;
}
// end getRow ()


/*******************************************************************************
* 
* Returns the Creature's column
* 
*******************************************************************************/
int Creature::getCol ()
{
  return (column > -1 && column < 20) ? column : -999;
}
// end getCol ()


/*******************************************************************************
* 
* Set the Creature's row
* 
*******************************************************************************/
void Creature::setRow (int r)
{
  row = (r > -1 && r < 20) ? r : row;
  
  return;
}
// end setRow ()


/*******************************************************************************
* 
* Set the Creature's column
* 
*******************************************************************************/
void Creature::setCol (int c)
{
  column = (c > -1 && c < 20) ? c : column;
  
  return;
}
// end setCol ()


/*******************************************************************************
* 
* Returns the flag of whether or not the Creature moved
* 
*******************************************************************************/
bool Creature::getMoved ()
{
  return moved;
}
// end getMoved ()


/*******************************************************************************
* 
* Set the Creature into motion
* 
*******************************************************************************/
void Creature::setMoved (bool m)
{
	moved = m;
	
	return;
}
// end setMoved ()


/*******************************************************************************
* 
* Increase the number of days the Creature has survived
* 
*******************************************************************************/
void Creature::incrementSurvived ()
{
  daysSurvived++;
  
  return;
}
// end incrementSurvived ()


/*******************************************************************************
* 
* Returns the number of days the Creature survived
* 
*******************************************************************************/
int Creature::getSurvivedDays ()
{
  return daysSurvived;
}
// end getSurvivedDays ()


/*******************************************************************************
* 
* When the Creature dies, reset the number of days it has survived
* 
*******************************************************************************/
void Creature::resetSurvivedDays ()
{
  daysSurvived = 0;
  
  return;
}
// end resetSurvivedDays ()


/*******************************************************************************
* 
* Returns the flag to indicate whether or not a Creature is able to breed
* 
*******************************************************************************/
bool Creature::isEligible ()
{
  return eligibleToSpawn;
}
// end isEligible ()


/*******************************************************************************
* 
* Returns the number of days left for a Creature to give breed
* 
*******************************************************************************/
int Creature::getDaysToSpawn ()
{
  return daysToSpawn;
}
// end getDaysToSpawn ()


/*******************************************************************************
* 
* Returns the world that is currently existing
* 
*******************************************************************************/
Environment* Creature::getWorld()
{
  return world;
}
// end getWorld ()
