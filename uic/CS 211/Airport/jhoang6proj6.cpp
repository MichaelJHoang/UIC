#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "airportFiles.h"

class TravelNetwork
{
 private:
 
   // Create the Data Members for the Travel Network here
   Airport *airport;
   
   MyStringList *filename;
   
   int size;
   
   
   void clean ()
   {
       int x = 0;
       
       for (; x < size; x++)
       {
           MyList *temp = airport[x].getAdjacency();
           
           temp -> removeAll();
           
           delete airport[x].getAdjacency();
       }
       
       delete [] airport;
   }
   
   bool DFS (int x, int y)
   {
       destinationNode *head = airport[x-1].getAdjacency() -> getHead();
       
       while (head)
       {
           int u = head -> getDest();
           
           if (u == y)
                return true;
                
            if (airport[u-1].getVisited() == false)
            {
                airport[u-1].setVisited(true);
                
                if (DFS(u, y) == true)
                    return true;
            }
            
            head = head -> getNext();
       }
       
       return false;
   }
   
   void _DFS (int x, int y)
   {
       int z = 0;
       
       for (; z < size; z++)
            airport[z].setVisited(false);
            
        if (DFS(x, y) == true)
            cout << "You can get from airport " << x << " to airport " << y << " in one or more flights" << endl;
        else
            cout << "You cannot get from airport " << x << " to airport " << y << " in one or more flights" << endl;
   }
 public:
  
 // Use a constructor to initialize the Data Members for Travel Network
 TravelNetwork()
 {
    size = 10;
    airport = new Airport[size];
    filename = new MyStringList();
 }
  
  
 // The main loop for reading in input
 void processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) 
      exit(1);
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
 void showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q - Quit the program.\n");
   printf ("  ? - Display list of commands.\n");
   printf ("  # - Ignore this line of input - treating it as a comment.\n");
   printf ("  t <int1> <int2> - Display a message whether or not a person can travel from <int1> to <int2>.\n");
   printf ("  r <int> - Remove an airport.\n");
   printf ("  i <int1> <int2> - Insert an edge from <int1> to <int2>.\n");
   printf ("  d <int1> <int2> - Delete an edge from <int1> to <int2>\n");
   printf ("  l - List all the items in the travel network.\n");
   printf ("  f <filename> - Open a file with the corresponding name.\n");
 }
 
 int readInt ()
 {
     int val;
     char *next = strtok(NULL, " \n\t");
     
     if (next == NULL)
     {
         puts("ERROR: Integer expected.");
         return 0 << 20;
     }
     
     val = atoi(next);
     
     if (val == 0 && strcmp(next, "0") != 0)
     {
         puts("ERROR: Integer expected.");
         return 0 << 20;
     }
     
     return val;
 }
 
 void doTravel()
 {
   int val1 = readInt();
   int val2 = readInt();
   
   cout << "Performing the travel command from " << val1 << " to " << val2 << endl;
   
   if (val1 != 0<<20 && val2 != 0<<20)
    _DFS(val1,val2);
 }
 
 void doResize()
 {
   int val1 = readInt();
   
   if (val1 != 0<<20)
   {
       if (val1 > 0 && val1 != 0 << 20)
       {
           cout << "Performing the Resize Command with " << val1 << endl;
           clean();
           
           airport = new Airport[val1];
           size = val1;
       }
       else
            puts("The value of the integer must be greater than 0.");
   }
   
   return;
 }
 
 void doInsert()
 {
    int val1 = readInt(), val2 = readInt();
    
    if (val1 != 0 << 20 && val2 != 0 << 20)
    {
        cout << "Performing the Insert Command with " << val1 << " and " << val2 << endl;
        
        if (val1 <= size && val1 != 0 << 20 && val1 > 0 && val2 <= size && val2 != 0 << 20 && val2 > 0)
            airport[val1 - 1].getAdjacency() -> insert(val2);
        else
            puts("Please enter in a valid airport number");
    }
    
    return;
 }
 
 void doDelete()
 {
    int val1 = readInt(), val2 = readInt();
    
    if (val1 != 0 << 20 && val2 != 0 << 20)
    {
        cout << "Performing the Delete Command with " << val1 << " and " << val2 << endl;
        
        if (val1 <= size && val1 > 0)
            airport[val1 - 1].getAdjacency() -> remove(val2);
        else
            cout << "Airport " << val1 << " is not within the travel network. Insertion aborted." << endl;
    }
    
    return;
 }
 
 void doList()
 {
     int x = 0;
     
     puts("AIRPORTS: ");
     
     for (; x < size; x++)
     {
         cout << x+1;
         airport[x].getAdjacency() -> showItems();
     }
     
     puts("Listed all available items within the travel network");
 }
 
 void doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   printf ("Performing the File command with file: %s\n", fname);
   
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
   if (filename -> isMember(fname) == false){
   //  2. open the file using fopen creating a new instance of FILE*
   FILE *file = fopen(fname, "r");
   if (file){
   //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
   filename -> insert(fname);
   processCommandLoop(file);
   filename -> remove(fname);
   //  4. close the file when processCommandLoop() returns
   fclose(file);
   }
   else
   {
       cout << fname << " has already been opened." << endl;
   }
 }
 }
};

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the airport adjcency list
  TravelNetwork airportData;
   
  // call the method that reads and parses the input
  airportData.processCommandLoop (inFile);
   
  printf ("Goodbye\n");
  return 1;
 }