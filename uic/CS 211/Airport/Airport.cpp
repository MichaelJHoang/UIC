//Author: Shin Imai
//Date: April 19, 2018
#include "Airport.h"

///////////////////////////////////////////////IMPLEMENTATION OF METHODS FOR DestinationNode ///////////////////////////////////////
//constructor
DestinationNode::DestinationNode(int destination)
{
    dest        = destination;
    nextDest    = NULL; 
}

//constructor with next ptr
DestinationNode::DestinationNode(int destination, DestinationNode* next)
{
    dest    = destination;
    nextDest= next;
}

//sets the dest data field
void DestinationNode::setDest(int destination)
{
    dest = destination;
}

//retreives the dest data field
int DestinationNode::getDest()
{
    return dest;
}

//sets the next ptr data field
void DestinationNode::setNext(DestinationNode* next)
{
    nextDest = next;
}

//retrieves the next ptr data field
DestinationNode* DestinationNode::getNext()
{
    return nextDest;    
}

///////////////////////////////////////////////IMPLEMENTATION OF METHODS FOR MyList ///////////////////////////////////////

//constructor
MyList::MyList()
{
    head = NULL;
}
        
//insert a DestinationNode at the end of the linked list
void MyList::insert (int v1)
{
    DestinationNode* tmp  = new DestinationNode(v1);
    
    if(head == NULL) { //empty linkedlist
        head = tmp;
    }
    else {
        DestinationNode* curr = head;
        while(curr->getNext() != NULL) { //loop till last node
            curr = curr->getNext();
        }
        curr->setNext(tmp);
    }
}

//remove node with same value as specified in parameter from linked list
void MyList::remove (int v1)
{
    if(head == NULL) { //empty linked list
        printf("Could not find an edge to %d\n", v1);
        return;
    }
    DestinationNode* curr = head;
    DestinationNode* prev = NULL;
    while(curr != NULL) {
        if (curr->getDest() == v1){
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
            printf("Successfully deleted edge.\n");
            return;
        }
        prev = curr;
        curr = curr->getNext();
    }
    printf("Could not find an edge to %d\n", v1);
}

//remove all nodes from linked list
void MyList::removeAll() {
    DestinationNode* curr = head;
    DestinationNode* next = head;
    while(curr != NULL) {
        next = curr->getNext();
        delete curr;
        curr = next;
    }
}

//show all items in output
void MyList::showItems()
{
    DestinationNode* curr = head;
    while(curr != NULL) {
        printf(" -> %d", curr->getDest());
        curr = curr->getNext();
    }
    printf("\n");
}

//retrieves the head data field
DestinationNode* MyList::getHead()
{
    return head;
}

//checks if a node with the specified dest is in the linked list
bool MyList::isMember(int v1) 
{
    DestinationNode* curr = head;
    while(curr != NULL) {
        if(curr->getDest() == v1)
            return true;
        curr = curr->getNext();
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//constructor
Airport::Airport()
{
    visited = false;
    adjacency = new MyList();
}

//set visited data field
void Airport::setVisited(bool status)
{
    visited = status;
}

//retrieve visited data field
bool Airport::getVisited()
{
    return visited;
}

//retrieves adjacency (MyList) data field
MyList* Airport::getAdjacency()
{
    return adjacency;   
}