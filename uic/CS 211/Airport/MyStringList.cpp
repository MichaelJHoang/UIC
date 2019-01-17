#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

class StringNode
{
    public:
        //constructor
        StringNode (char* fname)
        {
            filename = fname;
            
            nextFile = nullptr;
        }
        
        
        //constructor with next ptr
        StringNode (char* fname, StringNode* next)
        {
            filename = fname;
            nextFile = next;
        }
        
        
        //sets filename data field
        void setFilename(char* fname)
        {
            filename = fname;
            
            return;
        }
        
        
        //retrieves filename data field
        char *getFilename()
        {
            return filename;
        }
        
        
        //sets next ptr data field
        void setNext(StringNode* next)
        {
            nextFile = next;
        }
        
        
        //retrieves next ptr data field
        StringNode *getNext()
        {
            return nextFile;
        }
    
    private:
    
        char *filename;
        
        StringNode *nextFile;
};

class MyStringList
{
    public:
    
        //Constructor 
        MyStringList()
        {
            head = nullptr;
        }
        
        
        //retrieves the head data field
        StringNode *getHead()
        {
            return head;
        }
        
        //Insert a StringNode at the end of the linkedlist
        void insert (char *v1)
        {
            StringNode *temp = new StringNode(v1);
            
            if (head)
            {
                StringNode *current = head;
                
                while (current -> getNext() != nullptr)
                    current = current -> getNext();
                    
                current -> setNext(temp);
                
                return;
            }
            
            head = (head == nullptr) ? temp : head;
            
            return;
        }
        
        
        //remove Node from list with the same cstring as the parameter
        void remove (char *v1)
        {
            if (!head)
            {
                cout << "(Empty filename linked list) Couldn't find the filename " << v1 << endl;
                return;
            }
            
            StringNode *current = head;
            StringNode *previous = nullptr;
            
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
                            previous -> setNext(nullptr);
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
        void removeAll ()
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
        bool isMember (char *v1)
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
        
    private:
    
        StringNode *head;
};
