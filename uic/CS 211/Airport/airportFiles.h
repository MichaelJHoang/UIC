#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

class destinationNode
{
    private:
    
        int dest;
        
        destinationNode *nextDest;
        
    public:
    
        //constructors
        destinationNode (int destination);
 
        destinationNode (int destination, destinationNode *next);

        //getters and setters
        void setDest (int destination);
        
        int getDest ();
        
        void setNext (destinationNode *next);
        
        destinationNode *getNext ();
        
        destinationNode* getHead ();
    
};


class MyList
{
    private:
    
        destinationNode *head;
        
    public:
        //constructor
        MyList ();
        
        //insert a destinationNode at the end of the linked list
        void insert (int v1);

        //remove node with same value as specified in parameter from linked list
        void remove (int v1);

        //remove all nodes from linked list
        void removeAll ();
        
        //show all items in output
        void showItems ();
        
        //checks if a node with the specified dest is in the linked list
        bool isMember (int v1);
        
        //getters and setters
        destinationNode *getHead ();
        
        MyList* getAdjacency ();
    
};


class Airport
{
    public:
    
        //constructor
        Airport ();
        
        //getters and setters
        void setVisited(bool status);
        
        bool getVisited ();
        
        MyList *getAdjacency ();

    private:
    
        MyList *adjacency;
        
        bool visited;
};

/*******************************************************************************
 * 
 * dsa
 * 
*******************************************************************************/

class StringNode
{
    public:
        //constructor
        StringNode (char* fname);
        
        
        //constructor with next ptr
        StringNode (char* fname, StringNode* next);
        
        //sets filename data field
        void setFilename(char* fname);
        
        //retrieves filename data field
        char *getFilename();
        
        //sets next ptr data field
        void setNext(StringNode* next);
        //retrieves next ptr data field
        StringNode *getNext();
        
    private:
    
        char *filename;
        
        StringNode *nextFile;
};

class MyStringList
{
    public:
    
        
        MyStringList();
        
        StringNode *getHead();
        
        void insert (char *v1);
        
        void remove (char *v1);
    
        
        void removeAll ();
        
        bool isMember (char *v1);
        
    private:
    
        StringNode *head;
};
