#ifndef GRIDDISPLAY_CLASS
#define GRIDDISPLAY_CLASS

#include "GridDisplay.h"

#include <ctime>

GridDisplay::GridDisplay()
  : rowCount(20), colCount(20), dispVals (new char[400])
{
 init (20, 20);
}

GridDisplay::GridDisplay(int rows, int cols)
  : rowCount(rows), colCount(cols), dispVals (new char[rows * cols])
{
 init ( rows , cols );
}

void GridDisplay::init (int r, int c)
{
  init (r, c, '.');
}

void GridDisplay::init (int r, int c, char ch)
{
  if (r != rowCount || c != colCount)
  {
    delete[] dispVals;
    rowCount = r;
    colCount = c;
    dispVals = new char[r * c];
  }


  int max = r * c;
  for (int i = 0 ; i < max ; i++ )
  {
    dispVals[i] = ch;
  }
}

void GridDisplay::setChar ( int r, int c, char ch)
{
 if ( ( r >= 0 && r < rowCount ) && ( c >= 0 && c < colCount ) )
 { 
    int pos = r * colCount + c;
    dispVals[pos] = ch;
 }
}

void GridDisplay::clr1()
{
 int i;
 for ( i = 0 ; i < 10 ; i++ )
   printf ("\n\n\n\n\n\n\n\n\n\n");
}

void GridDisplay::showGrid()
{
 clr1();
 int r, c;

 for ( r = 0 ; r < rowCount ; r++ )
 {
    for ( c = 0 ; c < colCount ; c++ )
    {
       int pos = r * colCount + c;
       printf ("%c ", dispVals[pos]);
    }
    printf ("\n");
 }
}

void GridDisplay::mySleep ( int milliseconds )
{
 // written for usleep() which takes microseconds
 //int param = milliseconds * 1000;
 //usleep ( param );
    
 // written for C++ 2011 standard
 //std::this_thread::sleep_for ( std::chrono::seconds(1) );


 // written for use with time.h
 clock_t t;
 t = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
 while ( clock() < t ) 
 { } 
}
    
#endif