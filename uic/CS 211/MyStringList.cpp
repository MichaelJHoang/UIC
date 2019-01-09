//Author Shin Imai
//Date: April, 19 2018
#include "MyStringList.h"

///////////////////////////////////////////////IMPLEMENTATION OF METHODS FOR StringNode ///////////////////////////////////////

//constructor
StringNode::StringNode(char* fname)
{
    filename    = fname;
    nextFile    = NULL; 
}

//constructor with next
StringNode::StringNode(char* fname, StringNode* next)
{
    filename    = fname;
    nextFile    = next;
}

//sets filename data field
void StringNode::setFilename(char* fname)
{
    filename = fname;
}

//retrieves filename data field
char* StringNode::getFilename()
{
    return filename;
}

//sets next ptr data field
void StringNode::setNext(StringNode* next)
{
    nextFile = next;
}

//retrieves next ptr data field
StringNode* StringNode::getNext()
{
    return nextFile;    
}

///////////////////////////////////////////////IMPLEMENTATION OF METHODS FOR MyStringList ///////////////////////////////////////

//Constructor 
MyStringList::MyStringList()
{
    head = NULL;
}
        
//Insert a StringNode at the end of the linkedlist
void MyStringList::insert (char* v1)
{
    StringNode* tmp  = new StringNode(v1);
    
    if(head == NULL) { //empty linked list
        head = tmp;
    }
    else {
        StringNode* curr = head;
        while(curr->getNext() != NULL) { //loop until we find last node (the one with next ptr NULL)
            curr = curr->getNext();
        }
        curr->setNext(tmp);
    }
}

//remove Node from list with the same cstring as the parameter
void MyStringList::remove (char* v1)
{
    if(head == NULL) { //empty linked list
        printf("(Empty filename linked list) Could not find filename %s\n", v1);
        return;
    }
    StringNode* curr = head;
    StringNode* prev = NULL;
    while(curr != NULL) {
        if (curr->getFilename() == v1){
            if(prev == NULL) { //head needs to be deleted
                head = curr->getNext();
            } else {            // node was in other positon
                if(curr->getNext() != NULL){ // if the next node is not the last node
                    prev->setNext(curr->getNext()->getNext());
                } else {                    // the node is the last node
                    prev->setNext(NULL);
                }
            }
            delete curr;
            printf("Successfully deleted filename from file linked list.\n");
            return;
        }
        //adjust next pointers for surrounding nodes
        prev = curr;
        curr = curr->getNext();
    }
    printf("Could not find a file named %s\n", v1);
}

//removes all nodes from the linkedlist
void MyStringList::removeAll() {
    StringNode* curr = head;
    StringNode* next = head;
    while(curr != NULL) {
        next = curr->getNext();
        delete curr;
        curr = next;
    }
}

//retrieves the head data field
StringNode* MyStringList::getHead()
{
    return head;
}

//checks if the parameter is in one of the nodes
bool MyStringList::isMember(char* v1) 
{
    StringNode* curr = head;
    while(curr != NULL) {
        if(strcmp(curr->getFilename(),v1)==0) { //check node filename datafield and parameter
            return true; }
        curr = curr->getNext();
    }
    return false;
}