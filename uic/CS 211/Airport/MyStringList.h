#include <cstdio>
#include <cstring>
#include <cstdlib>

class StringNode {
    private:
        char*       filename;
        StringNode* nextFile;
        
    public:
        //constructor
        StringNode (char* fname);
        //constructor with next ptr
        StringNode (char* fname, StringNode* next);
        
        //sets filename data field
        void    setFilename(char* filename);
        //retrieves filename data field
        char*     getFilename();
        //sets next ptr data field
        void    setNext(StringNode* next);
        //retrieves next ptr data field
        StringNode* getNext();
};

class MyStringList {
    private:
        StringNode*    head;
        
    public:
        //Constructor 
        MyStringList();
        
        //retrieves the head data field
        StringNode* getHead();
        //Insert a StringNode at the end of the linkedlist
        void insert (char* v1);
        //remove Node from list with the same cstring as the parameter
        void remove (char* v1);
        //removes all nodes from the linkedlist
        void removeAll();
        //checks if the parameter is in one of the nodes
        bool isMember(char* v1);
};
