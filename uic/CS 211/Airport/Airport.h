#include <cstdio>
#include <cstring>
#include <cstdlib>

class DestinationNode {
    private:
        int              dest;
        DestinationNode* nextDest;
        
    public:
        //constructors
        DestinationNode(int destination);
        DestinationNode(int destination, DestinationNode* next);
        
        //getters and setters
        void    setDest(int destination);
        int     getDest();
        void    setNext(DestinationNode* next);
        DestinationNode* getNext();
};

class MyList {
    private:
        DestinationNode*    head;
        
    public:
        //constructor
        MyList();
        
        //getters and setters
        DestinationNode* getHead();
        
        //insert a DestinationNode at the end of the linked list
        void insert (int v1);
        //remove node with same value as specified in parameter from linked list
        void remove (int v1);
        //remove all nodes from linked list
        void removeAll();
        //show all items in output
        void showItems();
        //checks if a node with the specified dest is in the linked list
        bool isMember(int v1);
};

class Airport {
    private:
        bool            visited;
        MyList*         adjacency;
    public:
        //constructor
        Airport();
        
        //getters and setters
        void setVisited(bool status);
        bool getVisited();
        MyList* getAdjacency();
};