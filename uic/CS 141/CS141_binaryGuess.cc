/*---------------------------------------------------------
 * BinaryGuessing.cpp
 *     Text-based version of the game where you guess 0/1
 *     and try to beat the computer.
 *
 * Class: Program #? for CS 141, Fall 2017.  
 * Lab: Tuesdays at 9:00 AM,
 * TA: Moumita Samanta
 * System: Windows 10
 * Author: Jon-Michael Hoang
---------------------------------------------------------*/

/*---------------------------------------------------------
  All the libraries used within this program
---------------------------------------------------------*/
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

/*---------------------------------------------------------
  Redefined return 0 to endGame because it allows for easier
  comprehension.
  
  showHPBar redisplays the Hit Point (HP) Bar when a
  win/loss/draw based on userInput is not detected.
  This occurs when the user wants to reset the board or
  toggle the board or when the user makes an invalid move.
---------------------------------------------------------*/
#define endGame return 0;
#define showHPBar HP(69);

/*---------------------------------------------------------
  using using namespace std; to avoid tedious typing of
  std::
---------------------------------------------------------*/
using namespace std;


/*---------------------------------------------------------
  Initialize a global:
  
  vector arrow of size 21 filled with
  empty spaces. The 21 represents the length of the bar:
  
  x---------x+++++++++x
  
  trackArrowPosition tracks the location of the arrow such
  that when trackArrowPosition == 1, the CPU wins and when
  == 21, the user wins. 11 is the initial location of the
  arrow.
  
  numMove tracks the loop movement in main().
  
  Initializes the global 2D array to keep track of the
  scoreboard. 8x2 (row x column) dimension.
  
  forecast tracks the computer's forecasts.
---------------------------------------------------------*/
vector <char> arrow (21, ' ');
int trackArrowPosition = 11;

int numMove = 1;

const int rows = 8, cols = 2;
int scoreList [rows][cols];

int forecast;


/*---------------------------------------------------------
  Simply display author ID and Instructions for this program
---------------------------------------------------------*/
void display_ID_and_Instructions()
{
    cout << "Author: Jon-Michael Hoang" << endl
         << "Lab: Mondays at 9:00 AM" << endl
         << "Program: #3, 0/1 Guessing Game\n" << endl;

    cout << "Enter 0 or 1, trying to outsmart the computer, which is going to" << endl
         << "attempt to forecast your guesses.  On each move the score indicator" << endl
         << "moves to the right if the computer guesses correctly, and moves" << endl
         << "to the left if the computer does not." << endl
         << "\tEnter 't' to toggle displaying the data table." << endl
         << "\tEnter 'r' to reset the board." << endl
         << "\tEnter 'x' to exit." << endl
         << "Good luck, you'll need it!" << endl;
}//end display_ID_and_Instructions()


/*---------------------------------------------------------
  Hit points (HP) is referred to the bar and arrow. It is
  named that way to avoid confusing with the displayTable() 
  function that toggles the user's previous inputs.
---------------------------------------------------------*/
void HP (int point)
{
    cout << "\nComputer          Human" << endl
         << "x---------x+++++++++x" << endl;
    
    if (point == 0)
    {
        arrow.erase(arrow.begin());
        trackArrowPosition--;
    }
    else if (point == 1)
    {
        arrow.insert(arrow.begin(), ' ');
        trackArrowPosition++;
    }
    copy(arrow.begin(), arrow.end(), ostream_iterator<char>(cout));
    
    if (point == 0)
        cout << "\nComputer gets a point." << endl;
    else if (point == 1)
        cout << "\nHuman gets a point." << endl;
        
    cout << endl;
}//end HP()


/*---------------------------------------------------------
  Displays table of values in respect to the instructions
---------------------------------------------------------*/
void displayTable(int SWITCH, vector<int> previousInputs)
{
    const char seperator = ' ';
    const int binaryColumn = 6;
    const int tallyWidth = 4;
    if (SWITCH == 1)
    {
        cout << "         0   1" << endl
             << "   --- --- ---" << endl;
             
        /*---------------------------------------------------------
          Display the binaryColumn and the 0 and 1 columns in 
          addition to aligning the latter two.
        ---------------------------------------------------------*/
        //first row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   000"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[0][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[0][1] << endl;
             
        //second row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   001"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[1][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[1][1] << endl;
             
        //third row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   010"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[2][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[2][1] << endl;
             
        //fourth row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   011"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[3][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[3][1] << endl;
             
        //fifth row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   100"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[4][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[4][1] << endl;
        
        //sixth row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   101"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[5][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[5][1] << endl;
             
        //seventh row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   110"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[6][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[6][1] << endl;
             
        //eigth row
        cout << left << setw(binaryColumn) << setfill (seperator) << "   111"
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[7][0]
             << right << setw(tallyWidth) << setfill(seperator) << scoreList[7][1] << endl;
             
        //Displays the three previous moves when numMove > 3, which is when there exists
        //three+ elements in the vector.
        if (numMove > 3)
        {
            cout << "   Previous three: " <<
            previousInputs.at(previousInputs.size()-3) << previousInputs.at(previousInputs.size()-2) << previousInputs.at(previousInputs.size()-1) << endl;
            cout << "   Forecast: " << forecast << endl;
        }
    }
}//end displayTable()


/*---------------------------------------------------------
  reset() creates a temporary vector with properties of an
  unchanged vector "arrow" and swaps elements with the
  actual vector and reinitializes the trackArrowPosition.
  Other than also resetting numMove and resetting the table,
  it prompts the user to enter new "weights" for scoreList_track.
---------------------------------------------------------*/
void reset ()
{
            for (int emptyRow = 0; emptyRow < 8; emptyRow++)
                for (int emptyCol = 0; emptyCol < 2; emptyCol++)
                    scoreList[emptyRow][emptyCol] = 0;

            cout << "\nPlease enter 16 single digit numbers: ";
            for (int newRow = 0; newRow < 8; newRow++)
                for (int newCol = 0; newCol < 2; newCol++)
            cin >> scoreList[newRow][newCol];
            
            vector <char> temp (21,' ');
            temp.at(temp.size()/2) = '^';
            arrow.swap(temp);
    
            trackArrowPosition = 11;
            numMove = 0;
    
            cout << "\n**************************" << endl
                 << "Program has been resetted." << endl
                 << "**************************" << endl;
                 
            showHPBar; 
}//end reset()


/*---------------------------------------------------------
  Takes a vector previousInputs and takes the first three
  elements and multiplying .at(0)*100, .at(1)*10, .at(2)*1
  and adding them together and then 1000. The 1000 comes from
  allowing to hold a 0 in the hundreds spot. They are put in
  a switch case to organize where to increase the tally for
  0/1. e.g. {0, 0, 1, 1} would have a category 1001 and the
  '1' column will be increased by one as .at(3) == 1 and that
  the digit after this first three is a '1'.
---------------------------------------------------------*/
void scoreList_track (vector<int> previousInputs)
{
    int category = 1000 + (previousInputs.at(previousInputs.size()-4)*100) + (previousInputs.at(previousInputs.size()-3)*10) + (previousInputs.at(previousInputs.size()-2)*1);
    
    switch (category)
    {
        case 1000:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[0][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[0][1]++;
        break;
        case 1001:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[1][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[1][1]++;
        break;
        case 1010:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[2][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[2][1]++;
        break;
        case 1011:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[3][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[3][1]++;
        break;
        case 1100:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[4][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[4][1]++;
        break;
        case 1101:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[5][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[5][1]++;
        break;
        case 1110:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[6][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[6][1]++;
        break;
        case 1111:
            if (previousInputs.at(previousInputs.size()-1) == 0)
                scoreList[7][0]++;
            else if (previousInputs.at(previousInputs.size()-1) == 1)
                scoreList[7][1]++;
        break;
    }
}//end scoreList_track()


/*---------------------------------------------------------
  AI looks at scoreList and determines what the user is to
  input based on records of previous inputs in scoreList to
  "beat" the player.
---------------------------------------------------------*/
int computerMove (vector<int> previousInputs)
{
    //IFF nothing to record off of
    if (numMove < 4)
        forecast = rand()%2;
    //row1
    else if (scoreList[0][0] > scoreList[0][1])
        forecast = 0;
    else if (scoreList[0][0] < scoreList[0][1])
        forecast = 1;
    //row2
    else if (scoreList[1][0] > scoreList[1][1])
        forecast = 0;
    else if (scoreList[1][0] < scoreList[1][1])
        forecast = 1;
    //row3
    else if (scoreList[2][0] > scoreList[2][1])
        forecast = 0;
    else if (scoreList[2][0] < scoreList[2][1])
        forecast = 1;
    //row4
    else if (scoreList[3][0] > scoreList[3][1])
        forecast = 0;
    else if (scoreList[3][0] < scoreList[3][1])
        forecast = 1;
    //row5
    else if (scoreList[4][0] > scoreList[4][1])
        forecast = 0;
    else if (scoreList[4][0] < scoreList[4][1])
        forecast = 1;
    //row6
    else if (scoreList[5][0] > scoreList[5][1])
        forecast = 0;
    else if (scoreList[5][0] < scoreList[5][1])
        forecast = 1;
    //row7
    else if (scoreList[6][0] > scoreList[6][1])
        forecast = 0;
    else if (scoreList[6][0] < scoreList[6][1])
        forecast = 1;
    //row8
    else if (scoreList[7][0] > scoreList[7][1])
        forecast = 0;
    else if (scoreList[7][0] < scoreList[7][1])
        forecast = 1;
    //if scoreList[0][0] == scoreList[0][1], etc.
    else
    {
        if (previousInputs.at(previousInputs.size()-1) == 0)
            forecast = 1;
        else
            forecast = 0;
    }
    return forecast;
}//end computerMove()


/*---------------------------------------------------------
  Main body of the program
---------------------------------------------------------*/
int main() 
{
    srand(time(0)); //unique seed for each random
    
    char userInput;
    int tableToggle = -1;
    int point;
    
    vector <int> previousInputs (0);
    
    arrow.at(arrow.size()/2) = '^';
    
    display_ID_and_Instructions();
    
    showHPBar;
    
    for (numMove; ;numMove++)
    {
        displayTable(tableToggle, previousInputs);
        
        /*---------------------------------------------------------
          Notifies the user who is going to win
        ---------------------------------------------------------*/
        if (trackArrowPosition == 6)
        {
            cout << ">>> You're going to lose! <<<" << endl;
        }
        else if (trackArrowPosition == 16)
        {
            cout << ">>> You're going to win! <<<" << endl;
        }
        
        /*---------------------------------------------------------
          Displays the winner
        ---------------------------------------------------------*/
        if (trackArrowPosition == 1)
        {
            cout << "\n*************************************" << endl
                 << "THE COMPUTER WINS, AND YOU HAVE LOST." << endl
                 << "*************************************" << endl;
            endGame;
        }
        else if (trackArrowPosition == 21)
        {
            cout << "\n**********************************" << endl
                 << "YOU, THE USER, HAVE WON...FOR NOW." << endl
                 << "**********************************" << endl;
            endGame;
        }
        
        /*---------------------------------------------------------
          Asks the user for input and the input is capitalized
          regardless of case.
        ---------------------------------------------------------*/
        cout << numMove << ". Your input: ";
        cin >> userInput;
        userInput = toupper(userInput);
        
        /*---------------------------------------------------------
          Evaluates the userInput. The program stops running when
          the userInput is 'X', the score board display is
          toggled with 'T', the board resets with an input of 'R',
          the program runs HP(point) IFF userInput is a '0' or '1'.
          Else, it displays an error message.
        ---------------------------------------------------------*/
        if (userInput == 'X')
        {
            cout << "\nThank you for playing!" << endl
                 << "Exiting..." << endl
                 << "Done.";
                 
                 endGame;
        }
        else if (userInput == 'T')
        {
            /*---------------------------------------------------------
              How the toggle works - think of a light switch:
              When the lever is up, the lights are on and off when down,
              there is no inbetween. Now think of a graph with the
              x-axis intersecting the middle of the switch. When the lever
              is up, the y-value is 1 and -1 when down. Therefore, the
              scoreboard is on when tabbleToggle is 1 and off when -1 and
              this is done by multiplying tableToggle by -1.
            ---------------------------------------------------------*/
            tableToggle *= -1;
            showHPBar;
            numMove--;
        }
        else if (userInput == 'R') //resets the game
            reset();
        else if(userInput == '0' || userInput == '1') //IFF userInput is valid, will it run this.
        {
            point = userInput - '0'; //convert char to int
            
            /*---------------------------------------------------------
              Based on previous inputs, return AI attempt to == point.
              HP(0) = AI wins, HP(1) = Human wins.
            ---------------------------------------------------------*/
            if (computerMove(previousInputs) == point)
                HP(0);
            else
                HP(1);
                
            previousInputs.push_back(point);
            
            /*---------------------------------------------------------
              Begin recording 3 previousInputs + the next input for the
              AI to "learn" off of.
            ---------------------------------------------------------*/
            if (numMove > 3)
            {
                scoreList_track(previousInputs);
            }
        }
        else //Checks for invalid moves.
        {
            cout << "\n*************" << endl
                 << "INVALID MOVE." << endl
                 << "*************" << endl;
            numMove--;
            
            showHPBar;
        }
    }
    
    endGame;
}//end main()