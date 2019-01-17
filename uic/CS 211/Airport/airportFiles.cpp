//Jon-Michael Hoang | jhoang6

#include "airportFiles.h"

using namespace std;

/*******************************************************************************
 * 
 * destinationNode functions
 * 
*******************************************************************************/


destinationNode::destinationNode (int destination)
    {
        dest        = destination;
        nextDest    = NULL; 
    }
    
destinationNode::destinationNode (int destination, destinationNode *next)
        {
            dest = destination;
            nextDest = next;
        }
        
void destinationNode::setDest (int destination)
        {
            dest = destination;
        }
    
int destinationNode::getDest ()
        {
            return dest;
        }
        
void destinationNode::setNext (destinationNode *next)
        {
            nextDest = next;
        }
        
destinationNode * destinationNode::getNext ()
        {
            return nextDest;
        }
        

/*******************************************************************************
 * 
 * myList functions
 * 
*******************************************************************************/

//constructor
MyList::MyList()
        {
            head = NULL;
        }


//insert a destinationNode at the end of the linked list
void MyList::insert (int v1)
        {
            destinationNode *temp = new destinationNode(v1);
            
            if (head)
            {
                destinationNode *current = head;
                
                while (current -> getNext())
                    current = current -> getNext();
                    
                current -> setNext(temp);
                
                return;
            }
            
            head = (head == NULL) ? temp : head;
            
            return;
        }


//remove node with same value as specified in parameter from linked list
void MyList::remove (int v1)
        {
            if (!head)
            {
                cout << "Couldn't find an edge to " << v1 << endl;
                return;
            }
            
            destinationNode *current = head;
            destinationNode *previous = NULL;
            
            while (current)
            {
                if (current -> getDest() == v1)
                {
                    if (previous == NULL)
                        head = current -> getNext();
                    else
                    {
                        if (current -> getNext())
                            previous -> setNext(current -> getNext() -> getNext());
                        else
                            previous -> setNext(NULL);
                    }
                    
                    delete current;
                    
                    puts ("Successfully delted edge.");
                    
                    return;
                }
                
                previous = current;
                current = current -> getNext();
            }
            
            cout << "Could not find an edge to " << v1 << endl;
        }
        

//remove all nodes from linked list
void MyList::removeAll ()
        {
            destinationNode *current = head;
            destinationNode *next = head;
            
            while (current)
            {
                next = current -> getNext();
                
                delete current;
                
                current = next;
            }
            
            return;
        }
        

//show all items in output
void MyList::showItems ()
        {
            destinationNode *current = head;
            
            while (current)
            {
                cout << " -> " << current -> getDest();
                current = current -> getNext();
            }
            
            puts("");
            
            return;
        }
        

//checks if a node with the specified dest is in the linked list
bool MyList::isMember (int v1)
        {
            destinationNode *current = head;
            
            while (current)
            {
                if (current -> getDest() == v1)
                    return true;
                    
                current = current -> getNext();
            }
            
            return false;
        }
        
        //getters and setters
destinationNode* MyList::getHead ()
        {
            return head;
        }


/*******************************************************************************
 * 
 * Airport functions
 * 
*******************************************************************************/
//constructor
Airport::Airport ()
        {
            visited = false;
            
            adjacency = new MyList();
        }
        
//getters and setters
void Airport::setVisited(bool status)
        {
            visited = status;
        }
        
bool Airport::getVisited ()
        {
            return visited;
        }
        
MyList* Airport::getAdjacency ()
        {
            return adjacency;
        }


/*******************************************************************************
 * 
 * StringNode functions
 * 
*******************************************************************************/
//constructor
StringNode::StringNode (char* fname)
        {
            filename = fname;
            
            nextFile = NULL;
        }
        
        
        //constructor with next ptr
StringNode::StringNode (char* fname, StringNode* next)
        {
            filename = fname;
            nextFile = next;
        }
        
        
        //sets filename data field
void StringNode::setFilename(char* fname)
        {
            filename = fname;
            
            return;
        }
        
        
        //retrieves filename data field
char * StringNode::getFilename()
        {
            return filename;
        }
        
        
        //sets next ptr data field
void StringNode::setNext(StringNode* next)
        {
            nextFile = next;
        }
        
        
        //retrieves next ptr data field
StringNode * StringNode::getNext()
        {
            return nextFile;
        }


/*******************************************************************************
 * 
 * MyStringList functions
 * 
*******************************************************************************/

//Constructor 
MyStringList::MyStringList()
        {
            head = NULL;
        }
        
        
        //retrieves the head data field
StringNode * MyStringList::getHead()
        {
            return head;
        }
        
        //Insert a StringNode at the end of the linkedlist
void MyStringList::insert (char *v1)
        {
            StringNode *temp = new StringNode(v1);
            
            if (head)
            {
                StringNode *current = head;
                
                while (current -> getNext() != NULL)
                    current = current -> getNext();
                    
                current -> setNext(temp);
                
                return;
            }
            
            head = (head == NULL) ? temp : head;
            
            return;
        }
        
        
        //remove Node from list with the same cstring as the parameter
void MyStringList::remove (char *v1)
        {
            if (!head)
            {
                cout << "(Empty filename linked list) Couldn't find the filename " << v1 << endl;
                return;
            }
            
            StringNode *current = head;
            StringNode *previous = NULL;
            
            while (current)
            {
                if (current -> getFilename() == v1)
                {
                    if (!previous)
                        head = current -> getNext();
                    else
                    {
                        if (current -> getNext())
                            previous -> setNext(current -> getNext() -> getNext());
                        else
                            previous -> setNext(NULL);
                    }
                    
                    delete current;
                    
                    puts("Successfully deleted the filename from the file linked list.");
                    
                    return;
                }
                
                // adjust next pointers for the surrounding nodes
                previous = current;
                current = current -> getNext();
            }
            
            cout << "Couldn't find a file named " << v1 << endl;
            
            return;
        }
        
        
        //removes all nodes from the linkedlist
void MyStringList::removeAll ()
        {
            StringNode *current = head;
            StringNode *next = head;
            
            while (current)
            {
                next =  current -> getNext();
                
                delete current;
                
                current = next;
            }
            
            return;
        }
        
        
        //checks if the parameter is in one of the nodes
bool MyStringList::isMember (char *v1)
        {
            StringNode *current = head;
            
            while (current)
            {
                if (strcmp(current -> getFilename(), v1) == 0)
                    return true;
                
                current = current -> getNext();
            }
            
            return false;
        }
        