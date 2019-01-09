/* prog5Boggle.cpp
 Play the word-guess game of Boggle.
 
 Running the program looks like the following:

    Author: Dale Reed
    Program: #5, Boggle
    TA: Claude Shannon, Th 4-5
    Nov 1, 2017

    Welcome to the game of Boggle, where you play against the clock
    to see how many words you can find using adjacent letters on the
    board.  Each letter can be used only once for a given word.
 
    When prompted to provide input you may also:
         Enter 'r' to reset the board to user-defined values.
         Enter 's' to solve the board and display all possible words.
         Enter 't' to toggle the timer on/off.
         Enter 'x' to exit the program.
 
    The dictionary total number of words is: 263533
    Number of words of the right length is:  259709

      60 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 0
    1. Enter a word: plain
       Worth 4 points.
    Words so far are: plain

      46 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 4
    2. Enter a word: can
       Worth 1 points.
    Words so far are: can plain

      43 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 5
    3. Enter a word: map
       Worth 1 points.
    Words so far are: can map plain

      41 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 6
    4. Enter a word: can
    Sorry, that word was already previously found.
    Words so far are: can map plain

      41 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 6
    4. Enter a word: acrl
     was not found in the dictionary.

      30 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 6
    4. Enter a word: rail
     cannot be formed on this board.

      25 seconds remaining
    a c r l
    n e a p
    p u i m
    s a a n
       Score: 6
    4. Enter a word: r
    Enter 16 characters to be used to set the board: abcdefghijklmnop

      25 seconds remaining
    a b c d
    e f g h
    i j k l
    m n o p
       Score: 6
    4. Enter a word: s
    Enter min and max word lengths to display: 4 7
    Words between 4 and 7 are:
    bein fink fino glop jink knop koji mink mino nief nife polk ponk knife plonk
    Exiting the program.
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // Allows using the tolower() function
#include <ctime>      // Timer functions
#include <cstring>    // For strlen
using namespace std;

// Global constants
const char DictionaryFileName[] = "dictionary.txt";
const int MaxNumberOfWords = 263533; // Number of dictionary words
const int MinWordLength = 3;         // Minimum dictionary word size to be stored
const int MaxWordLength = 16;	     // Max word size.  Add 1 for null
const int MaxUserInputLength = 81;   // Max user input length
const int BoardArraySide = 6;        // Number of elements per side on board array
const int NumberOfLetters = 26;      // Letters in the alphabet
const int Offsets[] = {-1,-7,-6,-5,1,7,6,5};  // offsets for neighbor squares, given an index
const int NumberOfNeighbors = 8;     // Number of elements in above array
const int TotalSecondsToPlay = 60;   // Total number of seconds to play per board


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Dale Reed          \n");
    printf("Program: #5, Boggle        \n");
    printf("TA: Claude Shannon, Th 4-5 \n");
    printf("Nov 5, 2016                \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
    printf("Welcome to the game of Boggle, where you play against the clock   \n");
    printf("to see how many words you can find using adjacent letters on the  \n");
    printf("board.  Each letter can be used only once for a given word.       \n");
    printf("  \n");
    printf("When prompted to provide input you may also:                      \n");
    printf("     Enter 'r' to reset the board to user-defined values.         \n");
    printf("     Enter 's' to solve the board and display all possible words. \n");
    printf("     Enter 't' to toggle the timer on/off.                        \n");
    printf("     Enter 'x' to exit the program.                               \n");
    printf("  \n");
}//end displayInstructions()


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
    assert( ! inStream.fail() );       // make sure file open was OK
    
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
    
    cout << "The dictionary total number of words is: " << MaxNumberOfWords << endl;
    cout << "Number of words of the right length is:  " << numberOfWords << endl;
    
    // close the file
    inStream.close();
}//end readInDictionary()


//---------------------------------------------------------------------------
// Get random character
//    Find random character using a table of letter frequency counts.
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
}//end getRandomCharacter


//---------------------------------------------------------------------------
// Generate a random board by successively getting random characters.
void generateRandomBoard( char board[])
{
    for(int row=1; row<5; row++) {
        for(int col=1; col<5; col++) {
            // calculate actual board position
            int index = row * BoardArraySide + col;
            // store a random character at that position
            board[ index] = getRandomCharacter();
        }
    }
}//end generateRandomBoard()


//--------------------------------------------------------------------------------
// Display the board, taking the 16 board characters and displaying them
// in a 4x4 grid.
//
// Board is stored as a single dimension array with an extra border of
// characters around the edges to avoid array out-of-bounds coding issues
//       012345
//    0  ******
//    6  *    *
//    12 *    *
//    18 *    *
//    24 *    *
//    30 ******
void displayBoard( char board[], int score)
{
    cout << endl;
    
    for(int row=1; row<5; row++) {
        for(int col=1; col<5; col++) {
            // calculate actual board position
            int index = row * BoardArraySide + col;
            //  display that board character
            cout << board[ index] << " ";
        }
        cout << endl;
    }
    
    cout << "   Score: " << score << endl;
}//end displayBoard()


//---------------------------------------------------------------------------
// Recursively see if the next character in the word is also on the board.
bool nextCharacterFound(
         char theWord[],       // the word to be found on board
         int lengthOfWord,     // length of word
         int wordLetterIndex,  // index of letter in word to be found this time
         char board[],         // the board
         int boardPosition)    // position on board of previous letter examined
{
    // Set the return value to default of false.  If any of the possible adjacent
    // positions on the board find it, then it will be set to true, indicating that
    // the current letter being searched for was found.
    bool wordWasFound = false;
    
    // Extract the character to be found now on this turn
    char c = theWord[ wordLetterIndex];
    
    // Base condition.  For instance for the three-letter word "cat", when the index value
    // reaches 3 (the 4th value) then we know we're done, since the character in position 3
    // is actually the NULL at the end of the string.
    if( wordLetterIndex == lengthOfWord) {
       return true;
    }
    
    // Iterate through each adjacent board neighbor of the current letter
    for( int i=0; i<NumberOfNeighbors; i++) {
        // Get the index of the neighbor
        int neighborIndex = boardPosition + Offsets[ i];
        
        // See if neighbor matches the word character we're looking for
        if( board[ neighborIndex] == c) {
            // The adjacent letter matches the letter we're searching for.
            // First blank out current character, which will be restored
            //     after we return back to this function coming out of the recursion.
            board[ neighborIndex] = '*';
            
            // Here is the recursive call, looking for the next index position letter in theWord
            wordWasFound = nextCharacterFound( theWord, lengthOfWord, wordLetterIndex + 1,
                                               board, neighborIndex);
            
            // Restore the character when we return from the recursion, so we can
            // go on and try a different neighbor as the next letter instead.
            board[ neighborIndex] = c;
        
            // Stop searching if word was found, otherwise after a word is found, a subsequent
            // partial word match can reset the result to false.
            if( wordWasFound) {
                break;
            }
        }//end if( board[ neighborIndex....

    }//end for( int i...
    
    return wordWasFound;     // true or false
}// end nextCharacterFound()


//---------------------------------------------------------------------------
// See if word is on board.  This finds the first character of the word
// on the board, then launches function nextCharacterFound(...) which
// recursively checks the rest of it.
//
// This function is not combined with that function because it steps through each
// starting position on the board, however the subsequent recursive function
// steps through each adjacent neighbor for a given starting position.
//
//    Board is stored as a single dimension array with an extra border of
//    characters around the edges to avoid array out-of-bounds coding issues
//       012345
//    0  ******
//    6  *    *
//    12 *    *
//    18 *    *
//    24 *    *
//    30 ******
// Return true if it is found, false otherwise
bool wordOnBoard(
        char theWord[],   // the word to be found on board
        char board[])     // the board
{
    // set the return value to default of false.  If any of the possible positions
    // on the board find it, then it will be set to true
    int wordWasFound = false;
    
    // Find first character of the user input word
    char c = theWord[ 0];
    // Go through each board character and see if it matches.
    // Skip the surrounding asterisks
    for( int row=1; row<5; row++) {
        for( int col=1; col<5; col++) {
            // calculate actual board position
            int currentIndex = row * BoardArraySide + col;
            
            //  find first user input word character on board
            if( board[ currentIndex] == c) {
                // First character was found.  Blank it out on board so it is not reused.
                // It will be restored below after the next character is checked.
                board[ currentIndex] = '*';
                // Call function that recursively attempts to find remaining characters
                if( nextCharacterFound( theWord, (int)strlen( theWord),
                                        1, board, currentIndex)) {  // indicate which next letter to check
                    wordWasFound = true;
                }
                // Now restore the character that was previously blanked out
                board[ currentIndex] = c;
                // Once the word is found, stop searching.  Otherwise once it is found, if the starting
                // letter is found elsewhere on the board, return values from subsequent character
                // search may mark it as not found.
                if( wordWasFound) {
                    break;
                }
                
            }// end if( board...
            
        }//end for( int col
    }//end for( int row...
    
    return wordWasFound;
}//end wordOnBoard()



//---------------------------------------------------------------------------
// Display the words found by going through the wordsFound array, and for
// every entry marked true, display the word.  Do this successively by
// word length, so all length 3 words are first displayed in order, then
// all word 4 length words, and so on.
void displayWordsFound(
       char **dictionary,       // 2d array of dictionary words
       long int numberOfWords,  // how many words are in the dictionary
       long int wordsFound[],   // boolean array indicating which words were found
       int minimumLength,       // minimum length of words to display
       int maximumLength)       // maximum length of words to display
{
    int outputLineLength = 0;   // Used to print carriage-returns once output line length > 70
    
    // Go through entire dictionary multiple times, displaying the words in ascending length order
    for( int length=minimumLength; length<=maximumLength; length++) {
        for( int i=0; i<numberOfWords; i++) {
            // display the word if it was found and if it is the current length
            if( wordsFound[ i] && strlen( dictionary[ i]) == length) {
                // display the word
                cout << dictionary[ i] << " ";
                // Accumulate the output line length, to break up the output
                outputLineLength += length;
                if( outputLineLength >= 70) {
                    outputLineLength = 0;   // Reset it
                    cout << "\n";
                }
            }
        }//end for( int j...
    }//end for( int length...
    
    cout << endl;
}//end displayWordsFound()


//---------------------------------------------------------------------------
// get board score by accumulating sum of word scores.  Also mark words found
void displayAllPossibleWordsOnBoard(
            char board[],
            char **dictionary,
            long int numberOfWords,
            long int wordsFound[])
{
    // zero out words found array, since it might have values left over from
    // last board checked
    for( int i=0; i<numberOfWords; i++) {
        wordsFound[ i] = 0;
    }
    
    // go through each word of the dictionary and see if it is on the board
    for( int i=0; i<numberOfWords; i++) {
        // wordOnBoard(...) returns a 0 or 1.
        wordsFound[ i] = wordOnBoard( dictionary[ i], board);
    }
    
    // Display words on the board that are in the selected length range
    int minimumLength = 0;
    int maximumLength = MaxWordLength;
    cout << "Enter min and max word lengths to display: ";
    cin >> minimumLength >> maximumLength;
    cout << "Words between " << minimumLength << " and " << maximumLength << " are: " << endl;
    
    displayWordsFound( dictionary, numberOfWords, wordsFound, minimumLength, maximumLength);
    
}//end displayAllPossibleWordsOnBoard()


//---------------------------------------------------------------------------
int getPointsPerWord( int wordLength)
{
    int points = 0;
    
    // Calculate total score.  Score per word is:
    //    Letters  Points
    //      <3        0
    //       3        1
    //       4        2
    //       5        4
    //       6+    #letters
    switch( wordLength) {
        case 0:
        case 1:
        case 2: points = 0; break;
        case 3: points = 1; break;
        case 4: points = 2;  break;
        case 5: points = 4; break;
        default: points = wordLength; break; // for lengths 6+
    }//switch( wordLength)
    
    return points;
}//end getPointsPerWord


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary array, returning index
// if found, -1 otherwise
int binarySearch( const char searchWord[ MaxWordLength+1], // word to be looked up
                  char **dictionary)               // the dictionary of words
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = MaxNumberOfWords - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp( searchWord, dictionary[ mid]);
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
        }
        else  {
            low = mid + 1; // word should be located after mid location
        }
    }
    
    // Word was not found
    return -1;
}//end binarySearch()


//---------------------------------------------------------------------------
// Given a board and index starting position for a row, and userInput along
// with an index starting point there, store the next four userInput values
// into the designated board row.
void setFour( char board[], int boardIndex, char userInput[], int userInputIndex)
{
    for( int i=0; i<4; i++) {
        board[ boardIndex + i] = userInput[ userInputIndex + i];
    }
}


//---------------------------------------------------------------------------
// Reset the board to be whatever is specified by the user, to facilitate testing.
// Board is stored as a single dimension array with an extra border of
// characters around the edges to avoid array out-of-bounds coding issues
//       012345
//    0  ******
//    6  *    *
//    12 *    *
//    18 *    *
//    24 *    *
//    30 ******
void resetBoard( char board[])
{
    cout << "Enter 16 characters to be used to set the board: ";
    char userInput[ 16+1];  // Extra character is for the NULL
    cin >> userInput;
    
    // Set the board characters in groups of 4, one group per line
    setFour( board, 7, userInput, 0);
    setFour( board, 13, userInput, 4);
    setFour( board, 19, userInput, 8);
    setFour( board, 25, userInput, 12);
}


//---------------------------------------------------------------------------
int main()
{
    // declare variables
    // Board is stored as a single dimension array with an extra border of
    // characters around the edges to avoid array out-of-bounds coding issues
    //    012345
    // 0  ******
    // 6  *    *
    // 12 *    *
    // 18 *    *
    // 24 *    *
    // 30 ******
    //                      1         2         3
    //            012345678901234567890123456789012345
    char board[]="*******    **    **    **    *******";
    char **dictionary;                // 2d array of dictionary words, dynamically allocated
    long int numberOfWords;           // how many words actually found
    long int *wordsFound;             // flags index of words found
    int score = 0;                    // score so far
    char userInput[ MaxUserInputLength];
    int moveNumber = 1;               // Counts and displays moves made
    bool timerDisabled = false;       // Used to toggle the timer
    
    // seed the random number generator to be the time of day.  Otherwise
    // the random sequence will be the same each time prog. is run
    // srand( time(NULL));
    srand( 1);   // make it predictable for now
    
    displayIdentifyingInformation();
    displayInstructions();
    
    // read in dictionary.  numberOfWords returns the actual number of words found
    readInDictionary( dictionary, numberOfWords);
    
    // Allocate space to keep track of which words found.  This will be a "parallel array"
    // with the dictionary, where a 1 in a index position means the corresponding
    // dictionary array word was found, with a 0 otherwise.
    wordsFound = new long int[ numberOfWords];
    // Initialize wordsFound array to 0, to avoid spurious words found
    for( int i=0; i<numberOfWords; i++) {
	   wordsFound[ i] = 0;  
	}
    
    // Generate a random board
    generateRandomBoard( board);
    
    // Declare a variable to hold a time, and get the current time
    time_t startTime = time( NULL);
    
    // Loop to play the game while there is still time left
    int elapsedSeconds = 0;
    while( (elapsedSeconds < TotalSecondsToPlay) || timerDisabled) {

        cout << endl;
        if( !timerDisabled) {
           cout << "  " << TotalSecondsToPlay - elapsedSeconds << " seconds remaining";
        }
        displayBoard( board, score);
        
        // Prompt for and get user input
        cout << moveNumber << ". Enter a word: ";
        cin >> userInput;
        
        if( strlen( userInput) == 1) {
            switch( toupper(userInput[0])) {
                case 'R': resetBoard( board);   // Get user input to reset the board
                          continue;
                          break;
                case 'T': timerDisabled = !timerDisabled;   // toggle the timer
                          continue;
                          break;
                case 'S': displayAllPossibleWordsOnBoard( board, dictionary, numberOfWords, wordsFound);
                case 'X': cout << "Exiting the program. \n";
                          exit( 0);
                          break;
            }//end switch(...
        }//end if( strlen...
        
        // Validate word.  If valid add to the score, which depends on the wordlength
        if( wordOnBoard( userInput, board)) {
            int indexOfWordInDictionary = binarySearch( userInput, dictionary);
            
            // Ensure words was not previously already guessed and used for points
            if( wordsFound[ indexOfWordInDictionary]) {
                cout << "Sorry, that word was already previously found. " << endl;
                cout << "Words so far are: ";
                displayWordsFound( dictionary, numberOfWords, wordsFound, MinWordLength, MaxWordLength+1);
                continue;
            }
            
            // Word was not already previously found
            if( indexOfWordInDictionary != -1) {
                // Word is on board and found in dictionary.  Calculate and update points.
                int points = getPointsPerWord( strlen( userInput));
                cout << "   Worth " << points << " points." << endl;
                score += points;
                wordsFound[ indexOfWordInDictionary] = true;
                moveNumber++;
                
                cout << "Words so far are: ";
                displayWordsFound( dictionary, numberOfWords, wordsFound, MinWordLength, MaxWordLength+1);
            }
            else cout << " was not found in the dictionary." << endl;
        }
        else cout << " cannot be formed on this board." << endl;
        
        elapsedSeconds = difftime( time( NULL), startTime);
    }//end while( elapsedSeconds...
    
    return 0;   
}//end main()