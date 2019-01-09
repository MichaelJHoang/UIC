#include <cstdio>
// for usleep
#include <unistd.h>

class GridDisplay
{
 private:
   int rowCount;
   int colCount;
   char* dispVals;

 public:
   GridDisplay();
   GridDisplay(int rows, int cols);
   void init (int r, int c);
   void init (int r, int c, char ch);
   void setChar ( int r, int c, char ch);
   void clr1();
   void mySleep ( int milliseconds );
   void showGrid ();
};

