/*******************************************************************************
 * 
 * Jon-Michael Hoang | jhoang6
 * 
 * The following is the .cpp for the environment in which it alters the map
 * and its population
 * 
*******************************************************************************/

#include "Environment.h"
#include "Creature.h"


/*******************************************************************************
 * 
 * Class constructor
 * 
*******************************************************************************/
Environment::Environment (GridDisplay *g)
{
    int i, j;
    grid = g;
    rows = 20;
    cols = 20;
    position = new char* [rows];
    
	/*******************************************************************************
    * 
    * Creates a 2D array for the map
    * 
    *******************************************************************************/
    for (i = 0 ; i < rows ; i++)
    {
       position[i] = new char[cols];
       for (j = 0 ; j < cols ; j++)
       {
          position[i][j] = '\0';
       }
    }
}
// end Environment ()


/*******************************************************************************
 * 
 * Returns the number of rows that exists within the map
 * 
*******************************************************************************/
int Environment::getRows () 
{
    return rows;
}
// end getRows ()


/*******************************************************************************
 * 
 * Returns the number of columns that exists within the map
 * 
*******************************************************************************/
int Environment::getCols ()
{
    return cols;
}
// end getColumns ()


/*******************************************************************************
 * 
 * Returns whether or not something is within the domain and range of the map
 * 
*******************************************************************************/
bool Environment::isValid (int r, int c)
{
    return (( r >= 0 && r < rows ) && ( c >= 0 && c < cols)) ? true : false;
}
// end isValid ()


/*******************************************************************************
 * 
 * Checks to see if a certain position within the map contains a Creature
 * or not
 * 
*******************************************************************************/
bool Environment::isOccupied (int r, int c)
{
    return (position[r][c] == '\0') ? false : true;
}
// end is Occupied ()


/*******************************************************************************
 * 
 * Adds a Creature to the map
 * 
*******************************************************************************/
bool Environment::addCreature (char type, int r, int c) 
{
    if(this -> isValid(r, c) && !this -> isOccupied(r, c))
    {
        position[r][c] = type;
        grid -> setChar (r,c,type);
        
        return true;
    }
    
    return false;
}
// end addCreature ()


/*******************************************************************************
 * 
 * Moves the Creature within the map
 * 
*******************************************************************************/
bool Environment::moveCreature (int initR, int initC, int finalR, int finalC) 
{
    if(isValid(finalR, finalC) && (!isOccupied(finalR, finalC) || (isOccupied(finalR, finalC) && position[finalR][finalC] == 'A' && position[initR][initC] == 'D')))
    {
        char type = position[initR][initC];
        
        position[finalR][finalC] = type;
        position[initR][initC] = '\0';
        
        grid->setChar (finalR,finalC,type);
        grid->setChar (initR, initC, '.');
        
    }
    
    return false;
}
// end moveCreature ()


/*******************************************************************************
 * 
 * Delete the Creature from the map
 * 
*******************************************************************************/
bool Environment::deleteCreature (int r, int c)
{
    if(isValid(r, c) && isOccupied(r, c))
    {
        position[r][c] = '\0';
        grid->setChar (r, c, '.');
        
        return true;
    }
    
    return false;
}
// end deleteCreature ()


/*******************************************************************************
 * 
 * Returns the Creature type a specific location
 * 
*******************************************************************************/
char Environment::getCharAtPosition (int r, int c) 
{
    return (isValid(r, c) && isOccupied(r, c)) ? position[r][c] : '\0';
}
// end getCharAtPosition ()


/*******************************************************************************
 * 
 * Displays the map
 * 
*******************************************************************************/
void Environment::showGridWorld ()
{
    grid -> showGrid ();
    
    return;
}
