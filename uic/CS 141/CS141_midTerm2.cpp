/* 
 
 You have exactly 50 minutes to do your lab.  No late submissions will be accepted.
 
 The name of your program should be your netid.cpp.  For example if your netid is
 reed, then your program would be called reed.cpp.
 
 You will turn this in to the Blackboard project indicated by your TA.  Blackboard
 submissions will automatically turn off for your lab at the end of the 50 minutes.
 
 After adding the class and the displayList function, then running the given code
 with the input shown would give the following output:
     Enter at least five numbers to be used, followed by -1: 11 3 5 7 9 -1
     List is: 9 7 5 3 11
     Third node has 5
     Next-to-last node has 3
     Tail of list has 11
     
     Exiting program
 
 Add code to the program given below to do the following:
 1. (0 points) Supply the class declaration
 2. (5 points) Fill in the contents for the displayList() function
 3. (10 points) Write code to delete the last node of the list and then display the list.
 4. (10 points) Write code to find the smallest value on the list and display this number.
 
 After adding the code described here, running the program should look like:
     Enter at least five numbers to be used, followed by -1: 1 23 5 7 19 -1
     List is: 19 7 5 23 1
     Third node has 5
     Next-to-last node has 23
     Tail of list has 1
     
     After modification list is now: 19 7 5 23
     Smallest value on the list is: 5
     
     Exiting program
 
  Note that running the program with different inputs would give different outputs.
 */

#include <iostream>
using namespace std;

// Declare your public data members here, so that the rest of the code works
// ...
class Node
{
    public:
    int data;
    Node *pNext;
    
    
};


//-----------------------------------------------------------------
void displayList(Node *pHead)
{
    while (pHead != NULL)
    {
        cout << pHead -> data << " ";
        pHead = pHead -> pNext;
    }
    cout << endl;
}

void displaySmallest(Node *pHead)
{
    int min = 99999;
    
    while (pHead != NULL)
    {
        if (pHead -> data < min)
            min = pHead->data;
        pHead = pHead -> pNext;
    }
    
    cout << "Smallest value on the list is: " << min << endl;
}

//-----------------------------------------------------------------
// Prepend a new node to the beginning of the list, as demonstrated in class.
// Also set the head, third, next-to-last and tail pointers.
void prependNode( Node *&pHead, Node *&pNextToLast, Node *&pTail, int valueToAdd)
{
    static int nodeCounter = 0;    // Counts how many nodes are created.
    // Since it is static, its value remains between calls.
    // Get a new node
    Node *pTemp = new Node;
    nodeCounter++;
    
    // Set the tail pointer if this node is the first one
    if( nodeCounter == 1) {
        pTail = pTemp;
    }
    // Set the nextToLast pointer if this node is the second one to be created
    if( nodeCounter == 2) {
        pNextToLast = pTemp;
    }
    
    // Store values and update pointers
    pTemp->data = valueToAdd;
    pTemp->pNext = pHead;
    pHead = pTemp;
}

void deleteNode(Node* firstNode)
{
    //first check if firstNode is NULL or last node.
    if(firstNode == NULL)
        return;

    if(firstNode->pNext == NULL)
    {
        delete firstNode;
        firstNode = NULL;
        return;
    }

    Node* currNode = firstNode;
    while (currNode->pNext && currNode->pNext->pNext != NULL)
    {
        currNode = currNode->pNext;
    }
    delete currNode->pNext;
    currNode->pNext = NULL;
}

//-----------------------------------------------------------------
int main()
{
    Node *pHead = NULL;
    Node *pThirdNode = NULL;
    Node *pNextToLast = NULL;
    Node *pTail = NULL;
    
    int userInput = 0;
    cout << "Enter at least five numbers to be used, followed by -1: ";
    do {
        cin >> userInput;
        if( userInput != -1) {
            prependNode( pHead, pNextToLast, pTail, userInput);
        }
    } while( userInput != -1);
    
    cout << "List is: ";;
    displayList( pHead);
    // Set third node pointer, counting from the head of the list.
    //    This will crash if there aren't at least 3 nodes on the list.
    pThirdNode = pHead->pNext->pNext;
    cout << "Third node has " << pThirdNode->data << endl;
    cout << "Next-to-last node has " << pNextToLast->data << endl;
    cout << "Tail of list has " << pTail->data << endl;
    
    // Write your code here
    // ...
    cout << "Afte modding this: " << endl;
    deleteNode(pHead);
    displayList(pHead);
    displaySmallest(pHead);
    
    cout << endl << "Exiting program " << endl;
    return 0;
}// end main()