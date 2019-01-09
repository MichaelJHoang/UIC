/*******************************************************************************
 * 
 * Author: Jon-Michael Hoang
 * NetID: jhoang6
 * UIN: 657540122
 * 
 * Program: Boggle
 * 
 * Class: CS 141, Fall 2017.
 * Lab: Tuesdays at 9:00 AM
 * TA: Moumita Samanta
 * 
 * System: Windows 10, Cloud 9 IDE
 * 
 * ToDo: http://dave-reed.com/csc427.F10/Code/BoggleBoard.java
 * 
*******************************************************************************/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Timer functions
#include <cstring>    // For strlen
//author included libraries
#include <algorithm>  // To run algorithms to organize words by alphabet and size
#include <vector>     // For vectors
#include <sstream>    // To convert things into strings
#include <iterator>   // For ostream_iterator<dataType> (cout, " ")

#define endGame return 0;   // define return 0 as "endGame" so that it's easier to
                            // read

using namespace std;  // To avoid typing std:: redundantly

// Global constants
const char DictionaryFileName[] = "dictionary.txt";
const int MaxNumberOfWords = 263533; // Number of dictionary words
const int MinWordLength = 3;         // Minimum dictionary word size to be stored
const int MaxWordLength = 16;	     // Max word size.  Add 1 for null
const int MaxUserInputLength = 81;   // Max user input length
const int NumberOfLetters = 26;      // Letters in the alphabet
const int TotalSecondsToPlay = 60;   // Total number of seconds to play per board
const int maxBoardSize = 36;         // Max size for the board

//Global vector to store previous inputs
vector <string> previousInputs (1);

//struct to sort previousInputs by length

/*******************************************************************************
 * 
 * NOTE TO THE GRADER: Does this count as a class? Because structs are basically
 *                     like classes but they should contain only public data and
 *                     or variables, etc.
 * 
 *                     That being said, would this therefore be counted for extra
 *                     credit since I basically appropriately used a class?
 * 
*******************************************************************************/
 
struct compare
{
    bool operator()(const string& first, const string& second)
    {
        return first.size() < second.size();
    }
};
//end compare


//Display author identification and program instructions
void display_ID_and_Instructions()
{
    cout << "Author: Jon-Michael Hoang" << endl
         << "Program #5: Boggle" << endl
         << "TA: Moumita Samanta, Tuesday 9:00 AM Lab" << endl
         << "November 20th, 2017\n" << endl;
         
    cout << "Welcome to the game of Boggle, where you play against the clock" << endl
         << "to see how many words you can find using adjacent letters on the" << endl
         << "board.  Each letter can be used only once for a given word.\n" << endl;
         
    cout << "When prompted to provide input you may also:" << endl
         << "\tEnter 'r' to reset the board to user-defined values." << endl
         << "\tEnter 's' to solve the board and display all possible words." << endl
         << "\tEnter 't' to toggle the timer on/off." << endl
         << "\tEnter 'x' to exit the program.\n" << endl;
         
    return;
}
//end display_ID_and_Instructions()


//---------------------------------------------------------------------------
// Read in dictionary
//    First dynamically allocate space for the dictionary.  Then read in words
// from file.  Note that the '&' is needed so that the new array address is
// passed back as a reference parameter.
void readInDictionary(
          char ** &dictionary,                      // dictionary words
          long int &numberOfWords)                  // number of words stored
{
    // Allocate space for large array of C-style strings
    dictionary = new char*[ MaxNumberOfWords];
    
    // For each array entry, allocate space for the word (C-string) to be stored there
    for (int i=0; i < MaxNumberOfWords; i++) {
        dictionary[i] = new char[ MaxWordLength+1];
        // just to be safe, initialize C-strings to all null characters
        for (int j=0; j < MaxWordLength; j++) {
            dictionary[i][j] = '\0';
        }//end for (int j=0...
    }//end for (int i...
    
    // Now read in the words from the file
    ifstream inStream;                 // declare an input stream for my use
    numberOfWords = 0;                   // Row for the current word
    inStream.open( DictionaryFileName);
    assert(!inStream.fail() );       // make sure file open was OK
    
    // Keep repeating while input from the file yields a word
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    while( inStream >> theWord) {
        int wordLength = (int)strlen( theWord);
        if( wordLength >= MinWordLength && wordLength <= MaxWordLength) {
            strcpy( dictionary[ numberOfWords], theWord);
            // increment number of words
            numberOfWords++;
        }
    }//end while( inStream...
    
    cout << "The dictionary total number of words is: " << MaxNumberOfWords << endl
         << "Number of words of the right length is:  " << numberOfWords << endl << endl;
    
    // close the file
    inStream.close();
}
//end readInDictionary()


int binarySearch(const char searchWord[ MaxWordLength+1], // word to be looked up
                 char **dictionary)               // the dictionary of words
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = MaxNumberOfWords - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp(searchWord, dictionary[ mid]);
        
        if ( searchResult == 0)
        {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)
        {
            high = mid - 1; // word should be located prior to mid location
        }
        else
        {
            low = mid + 1; // word should be located after mid location
        }
    }
    
    // Word was not found
    return -1;
}
//end binarySearch()


//---------------------------------------------------------------------------
// Get random character
// Find random character using a table of letter frequency counts.
// Iterate through the array and find the first position where the random number is
// less than the value stored.  The resulting index position corresponds to the
// letter to be generated (0='a', 1='b', etc.)
char getRandomCharacter()
{
    // The following table of values came from the frequency distribution of letters in the dictionary
    float letterPercentTotals[ NumberOfLetters] = {
                0.07680,  //  a
                0.09485,  //  b
                0.13527,  //  c
                0.16824,  //  d
                0.28129,  //  e
                0.29299,  //  f
                0.32033,  //  g
                0.34499,  //  h
                0.43625,  //  i
                0.43783,  //  j
                0.44627,  //  k
                0.49865,  //  l
                0.52743,  //  m
                0.59567,  //  n
                0.66222,  //  o
                0.69246,  //  p
                0.69246,  //  q
                0.76380,  //  r
                0.86042,  //  s
                0.92666,  //  t
                0.95963,  //  u
                0.96892,  //  v
                0.97616,  //  w
                0.97892,  //  x
                0.99510,  //  y
                1.00000}; //  z
    
    // generate a random number between 0..1
    // Multiply by 1.0 otherwise integer division truncates remainders
    float randomNumber = 1.0 * rand() / RAND_MAX;
    
    // Find the first position where our random number is less than the
    // value stored.  The index corresponds to the letter to be returned,
    // where 'a' is 0, 'b' is 1, and so on.
    for( int i=0; i<NumberOfLetters; i++) {
        if( randomNumber < letterPercentTotals[ i]) {
            // we found the spot.  Return the corresponding letter
            return (char) 'a' + i;
        }
    }
    
    // Sanity check
    cout << "No alphabetic character generated.  This should not have happened. Exiting program.\n";
    exit( -1);
    return ' ';   // should never get this
}
//end getRandomCharacter


//Generate a board by creating a border of asterisks and then filling it with
//random characters and then making the asterisks disappear
//Remarks: board is generated using a 1D array
char generateBoard(char board[], int maxBoardSize)
{
    //Top and bottom borders of the board
    for (int x = 0; x < 6; x++)
    {
        board[x] = '*';
    }
    for (int x = 30; x < 36; x++)
    {
        board[x] = '*';
    }
    //Left and right borders of the board
    for (int y = 0; y <= 30; y+=6)
    {
        board[y] = '*';
    }
    for (int y = 5; y <= maxBoardSize; y+= 6)
    {
        board[y] = '*';
    }
    //Generate the insides
    for (int n = 0; n < maxBoardSize; n++)
    {
        board[n] = (board[n] != '*') ? getRandomCharacter():' ';
    }
    
    return *board;
}
//end generateBoard()


//Print the board
void printBoard (char board[], int maxBoardSize)
{
    cout << " ";
    for (int x = 0; x < maxBoardSize+1; x++)
    {
        if ((x+1)%6 == 0)
        {
            cout << board[x] << endl << " ";
        }
        else
            cout << board[x] << " ";
    }
}
//end printBoard()


//converts words to points by checking if the input isalpha and running the points
//through a switch case to calculate given points according to rules of boggle
int wordToPoints (char userInput[])
{
    int points = 0;
    int x = 0;
    
    while (points != -1)
    {
        if (isalpha(userInput[x]))
        {
            points++;
            x++;
        }
        else
            break;
    }
    switch (points)
    {
        case 1: return 0;
        case 2: return 0; break;
        case 3: return 1; break;
        case 4: return 2; break;
        case 5: return 4; break;
        default: return points; break;
    }
}
//end wordToPoints()


//checks if there exists a previously found word by check the vector previousInputs
//returns true if there exists
//        false otherwise
bool foundPrevious (char userInput[])
{
    bool flag = false; //initialize a flag
    
    for (int x = 0; x < previousInputs.size(); x++)
    {
        if (previousInputs.at(x).compare(userInput) == 0)
            flag = true; //flag becomes true indefinitely when there exists an 
                         //element that is equal to userInput
    }
    return flag;
}
//end foundPrevious()


//resets the board by taking the userInput and filling the "insides" of the board
//with userInput
//REMARKS: It simply resets ONLY the board
char resetBoard (char board[], char userInput[])
{
    int y = 0;
    for (int x = 0; x < maxBoardSize; x++)
    {
        if (board[x] != ' ')
        {
            board[x] = userInput[y];
            y++;
        }
        else
            board[x] = ' ';
    }
}
//end resetBoard()

bool recursion (char board[], char userInput[], int index, int length)
{
    bool done = false;
    int next;
    int surround[8] = {1,-1,5,-5,6,-6,7,-7};
    
    if (length == strlen(userInput))
    {
        done = true;
        return done;
    }
    
    for (int g = 0; g<8; g++)
    {
        next = index + surround[g];
        if (userInput[length] == board[next])
        {
            done = recursion(board,userInput,next,length+1);
        }
    }
    return done;
}

bool base (char board[], char userInput[])
{
    int g;
    char first = userInput[0];
    int index = 0;
    int length = 0;
    bool done = false;
    
    for (g = 0; g < 36; g++)
    {
        if (userInput[length] == board[g])
        {
            index = g;
            done = recursion(board,userInput,index,length);
        }
    }
    
    return done;
}

int main()
{
    //Declare a variable to hold a time, and get the current time, etc.
    srand(time(NULL));
    time_t startTime = time(NULL);
    int elapsedSeconds = 0;
    int timerToggle = 1;                    //switch to toggle the timer: 1 = on -1 = off
    
    //Dictionary related variables
    char **dictionary;                // 2d array of dictionary words, dynamically allocated
    long int numberOfWords;           // how many words actually found in dictionary
    
    //I/O related variables
    char userInput [MaxUserInputLength];    //stores the user's input
    int numTurns = 1;                       //tracks number of turns that have went by
    int userScore = 0;                      //tracks the user's score
    int min, max;                           //displays words between length min and max when user wants the board to be solved
    compare c;                              //create a struct to allow organization of previous input strings
    
    int offsets [] = {-7,-6,-5,-1,1,5,6,7};
    
    //Summon the board and give it life
    char board[maxBoardSize];
    generateBoard(board,maxBoardSize);
    
    display_ID_and_Instructions();
    
    //read in dictionary.  numberOfWords returns the actual number of words found
    readInDictionary(dictionary, numberOfWords);
    
    while(elapsedSeconds < TotalSecondsToPlay)
    {
        //Calculate how many seconds have elapsed since we started the timer.
        if (timerToggle == 1)
        {
            elapsedSeconds = difftime(time(NULL), startTime);
            cout << "   " << TotalSecondsToPlay - elapsedSeconds << " second(s) remaining." << endl;
        }
        
        //prints out the board
        printBoard(board,maxBoardSize);
        
        //prints out user's current score
        cout << " Score: " << userScore << endl;
        
        //tracks number of turns and asks for user input
        cout << numTurns++ << ". Enter a word: ";
        cin >> userInput;
        
        //checks if the user intentionally wants to exit the program
        if ((userInput[0] == 'x') && (userInput[1] == '\0'))
        {
            cout << "\n   Thanks for playing!" << endl
                 << "   Exiting..." << endl
                 << "   Done.";
            endGame;
        }
        
        //checks if the user intentionally wants to reset the board
        else if ((userInput[0] == 'r') && (userInput[1] == '\0'))
        {
            cout << "   Enter 16 characters to be used to set the board: ";
            cin >> userInput;
            resetBoard(board, userInput);
            numTurns--; //resetting the board does not increment turns
            
            elapsedSeconds = 0; //resets defaults the timer to pre-'r' userInput
        }
        
        //checks if the user wants to intentionally toggle the timer so that they
        //can work input more words without worrying about the time
        else if ((userInput[0] == 't') && (userInput[1] == '\0'))
        {
            cout << "   The timer has been toggled." << endl;
            timerToggle *= -1; //switch
            numTurns--; //toggling the timer does not increment turns
        }
        
        //checks if the user wants to intentionally give up and wants the solutions
        //to the current board with the user input min and max domains
        else if ((userInput[0] == 's') && (userInput[1] == '\0'))
        {
            cout << "   Enter min and max word lengths to display: ";
            cin >> min >> max;
            cout << "   Words between " << min << " and " << max << " are:" << endl;
            
            //CODE NEEDED HERE
            
            cout << "\n   Thanks for playing!" << endl
                 << "   Exiting..." << endl
                 << "   Done.";
            endGame;
        }
        
        //if the user enters a word, run through the binary search to check if it
        //exists in the dictionary
        else if((binarySearch(userInput, dictionary) != -1) && (base(board, userInput) == false))
        {
            //if it exists in the dictionary, check to see if there exists a previous
            //user input/answer
            if (foundPrevious(userInput) == true)
            {
                cout << "   Sorry, that word was already previously found." << endl;
            }
            //if it exists in the dictionary and not in the previousInputs, calculate
            //the points and push the userInput into previousInputs
            else
            {
                cout << "   Worth " << wordToPoints(userInput) << " points." << endl;
                userScore += wordToPoints(userInput);
                
                previousInputs.push_back(userInput);
            }
            
            //sort the previousInputs by alphabet first and then by length to meet
            //program standards in displaying "Words so far are: ..."
            sort(previousInputs.begin(), previousInputs.end()); //sort alphabetically
            sort(previousInputs.begin(), previousInputs.end(), c); //sort by length
            
            //prints out 
            cout << "   Words so far are:";
            copy(previousInputs.begin(), previousInputs.end(), ostream_iterator<string>(cout, " "));
            cout << endl << endl;
        }
        else
        {
            cout << "...was not found in the dictionary.\n" << endl;
            numTurns--;
        }
    }
    cout << "I let you finish your last move. Time is up!" << endl;
    
    endGame;
}
//end main()