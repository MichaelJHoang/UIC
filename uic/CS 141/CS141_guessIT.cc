/*
    Guess It
    
    Class: CS 141, Fall 2017. Tuesday 9:00 AM lab.
    System: Windows 10, Cloud9
    Author: Jon-Michael Hoang
    
    ToDo: I don't know what to actually put here. So you can watch this:
    https://www.youtube.com/watch?v=Kg-HHXuOBlw
    -Clean up and simplify code to be ready for submission
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() 
{
    char random = 0;
    char special = 0;
    char num = 0;
    char input  = ' ';
    
    
    //initializes a unique seed and generates the special char
    srand(time(0)); 
    special = (rand() % 58) + 65;
    
    
    //identifying info    
    cout << "Author: Jon-Michael Hoang\nLab: Tuesdays at 9:00 AM\nTA: Moumita Samanta\nProgram: #1, Guess It\n" << endl;
    
    
    //provided that the 'special' has a char value equal to a non-roman char, run this loop until it is assigned one
    while (special <= 96 && special >= 91)
        special = (rand() % 58) + 65;
    
    
    //generate a table of chars in respect to rubric guidelines. tableNum refers to the position within the table
    for (int tableNum = 99; tableNum >= 0; tableNum--)
    {
        //generate a random ascii value similar to lines [36->38]. sets random char within ascii range of respective roman characters
        //IFF the below line does not generate a roman-character equivalent ascii value, while loop runs until it is assigned one
        random = (rand() % 58) + 65;
        while (random <= 96 && random >= 91)
            random = (rand() % 58) + 65;
        
        
        //if, else if, and else statements to produce an organized 10x10 table with random characters and a special character in tableNum values that are multiples of 9
        if (tableNum % 10 == 0 && tableNum > 9)
        {
            //sets 'num' to 'special' when condition in parenthesis is true, otherwise is set to 'random'
            //num is to print out its ascii equivalent
            num = (tableNum % 9 == 0) ? special:random;     
            cout << tableNum << ":" << num << endl;         
        }
        else if (tableNum > 9)
        {
            //refer to comment on lines [54->55]
            num = (tableNum % 9 == 0) ? special:random;
            cout << tableNum << ":" << num << " ";
        }
        else
        {
            //refer to comment on lines [54->55]
            num = (tableNum % 9 == 0) ? special:random;
            cout <<  " " << tableNum << ":" << num << " ";
        }
    } //end creation of table
    
    
    //prints out instruction for the reader
    cout << "\n\n1. Choose any two-digit number in the table above (e.g. 73).\n";
    cout << "2. Subtract its two digits from itself (e.g. 73 - 7 - 3 = 63).\n";
    cout << "3. Find this new number (e.g. 63) and remember the letter next to it.\n";
    cout << "4. Now press 'r' and I'll read your mind... ";
    
    
    //user input must == 'r' to get out of loop so that it can run line 83
    while (input != 'r')
        cin >> input;
    
    
    //outputs special char
    cout << "\nYou selected the character: " << special;
    
    return 0;
}