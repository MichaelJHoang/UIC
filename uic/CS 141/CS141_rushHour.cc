/* --------------------------------------------------------
 * Traffic.cpp
 *     Text-based version of the game RushHour, where the
 *     object is to move the vehicles such that the small
 *     car can exit the right of the board.
 *
 * Class: Program #2 for CS 141, Fall 2017.  
 * Lab: Tuesdays at 9:00 AM,
 * TA: Moumita Samanta
 * System: Windows 10
 * Author: Jon-Michael Hoang
*/

#include <iostream>
#include <string>
#include <cctype>

#define endGame return 0;

using namespace std;

char  p1, p2, p3, p4, p5, p6,
      p7, p8, p9,p10,p11,p12,
     p13,p14,p15,p16,p17,p18,
     p19,p20,p21,p22,p23,p24,   
     p25,p26,p27,p28,p29,p30,
     p31,p32,p33,p34,p35,p36;
     
int moveCount;

void display_ID_and_Instructions()
{
    cout << "Author: Jon-Michael Hoang" << endl
         << "Lab: Tuesdays at 9:00 AM" << endl
         << "Program: #2, Traffic" << endl << endl;

    cout << "Welcome to the traffic game!" << endl << endl
         << "Move the vehicles so that the RED CAR (RR) can exit" << endl
         << "the board from the right. Each move should be of the form:" << endl
         << "CDN, where:" << endl
         << "C is the vehicle to be moved," << endl
         << "D is the direction (u = up, d = down, l = left, r = right)" << endl
         << "N is the number of squares to move it" << endl
         << "For example, GR2 means move the G vehicle to the right 2 squares." << endl
         << "Lower-case input such as gr2 is also accepted." << endl
         << "Enter '-' to reset the board or 'x' to exit." << endl << endl;
}

void displayBoard()
{
    cout << "   - - - - - - - -" << endl
         << " 1 | " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << p5 << " " << p6 << " |" << endl
         << " 7 | " << p7 << " " << p8 << " " << p9 << " " << p10 << " " << p11 << " " << p12 << " |" << endl
         << "13 | " << p13 << " " << p14 << " " << p15 << " " << p16 << " " << p17 << " " << p18 << " |" << endl
         << "19 | " << p19 << " " << p20 << " " << p21 << " " << p22 << " " << p23 << " " << p24 << " |" << endl
         << "25 | " << p25 << " " << p26 << " " << p27 << " " << p28 << " " << p29 << " " << p30 << " |" << endl
         << "31 | " << p31 << " " << p32 << " " << p33 << " " << p34 << " " << p35 << " " << p36 << " |" << endl
         << "   - - - - - - - -" << endl;
}

int reset()
{
    cout << "You have chosen to reset the board" << endl
         << "Enter 36 characters for the new board:" << endl;
                  
    cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6
        >> p7 >> p8 >> p9 >> p10 >> p11 >> p12
        >> p13 >> p14 >> p15 >> p16 >> p17 >> p18
        >> p19 >> p20 >> p21 >> p22 >> p23 >> p24
        >> p25 >> p26 >> p27 >> p28 >> p29 >> p30
        >> p31 >> p32 >> p33 >> p34 >> p35 >> p36;
            
    p1 = toupper(p1); p2 = toupper(p2); p3 = toupper(p3); p4 = toupper(p4); p5 = toupper(p5); p6 = toupper(p6);
    p7 = toupper(p7); p8 = toupper(p8); p9 = toupper(p9); p10 = toupper(p10); p11 = toupper(p11); p12 = toupper(p12);
    p13 = toupper(p13); p14 = toupper(p14); p15 = toupper(p15); p16 = toupper(p16); p17 = toupper(p17); p18 = toupper(p18);
    p19 = toupper(p19); p20 = toupper(p20); p21 = toupper(p21); p22 = toupper(p22); p23 = toupper(p23); p24 = toupper(p24);
    p25 = toupper(p25); p26 = toupper(p26); p27 = toupper(p27); p28 = toupper(p28); p29 = toupper(p29); p30 = toupper(p30);
    p31 = toupper(p31); p32 = toupper(p32); p33 = toupper(p33); p34 = toupper(p34); p35 = toupper(p35); p36 = toupper(p36);
            
    cout << endl;
    moveCount = 0;
}

bool exist (char vehicle, char p1, char p2, char p3, char p4, char p5, char p6)
{
    int letterCount = 0;
    
    if (vehicle == p1)
        letterCount++;
    if (vehicle == p2)
        letterCount++;
    if (vehicle == p3)
        letterCount++;
    if (vehicle == p4)
        letterCount++;
    if (vehicle == p5)
        letterCount++;
    if (vehicle == p6)
        letterCount++;
        
    if (letterCount > 1)
        return true;
    else
        return false;
}

void swapElements (char &n1, char& n2)
{
    char temp = n1;
    n1 = n2;
    n2 = temp;
}

void moveOneSquare (char vehicle, char direction, char& p1, char& p2, char& p3, char& p4, char& p5, char& p6, bool& errorCheck)
{
    if (direction == 'R' || direction == 'D')
    {
        if (p6 == '.' && p5 == vehicle)
        {
            swapElements(p5, p6);
            errorCheck = false;
        }
        if (p5 == '.' && p4 == vehicle)
        {
            swapElements(p4, p5);
            errorCheck = false;
        }
        if (p4 == '.' && p3 == vehicle)
        {
            swapElements(p3, p4);
            errorCheck = false;
        }
        if (p3 == '.' && p2 == vehicle)
        {
            swapElements(p2, p3);
            errorCheck = false;
        }
        if (p2 == '.' && p1 == vehicle)
        {
            swapElements(p1, p2);
            errorCheck = false;
        }
    }
    
    else if (direction == 'L' || direction == 'U')
    {
        if (p1 == '.' && p2 == vehicle)
        {
            swapElements(p1,p2);
            errorCheck = false;
        }
        if (p2 == '.' && p3 == vehicle)
        {
            swapElements(p2,p3);
            errorCheck = false;
        }
        if (p3 == '.' && p4 == vehicle)
        {
            swapElements(p3,p4);
            errorCheck = false;
        }
        if (p4 == '.' && p5 == vehicle)
        {
            swapElements(p4,p5);
            errorCheck = false;
        }
        if (p5 == '.' && p6 == vehicle)
        {
            swapElements(p5,p6);
            errorCheck = false;
        }
    }
}

void moveOneSquare(char vehicle, char direction, bool& errorCheck)
{
    if (exist(vehicle, p1, p2, p3, p4, p5, p6))
        moveOneSquare(vehicle, direction, p1, p2, p3, p4 ,p5, p6, errorCheck);
    else if (exist(vehicle, p7, p8, p9, p10, p11, p12))
        moveOneSquare(vehicle, direction, p7, p8, p9, p10, p11, p12, errorCheck);
    else if (exist(vehicle, p13, p14, p15, p16, p17, p18))
        moveOneSquare(vehicle, direction, p13, p14, p15, p16, p17, p18, errorCheck);
    else if (exist(vehicle, p19, p20, p21, p22, p23, p24))
        moveOneSquare(vehicle, direction, p19, p20, p21, p22, p23, p24, errorCheck);
    else if (exist(vehicle, p25, p26, p27, p28, p29, p30))
        moveOneSquare(vehicle, direction, p25, p26, p27, p28, p29, p30, errorCheck);
    else if (exist(vehicle, p31, p32, p33, p34, p35, p36))
        moveOneSquare(vehicle, direction, p31, p32, p33, p34, p35, p36, errorCheck);
    
    else if (exist(vehicle, p1, p7, p13, p19, p25, p31))
        moveOneSquare(vehicle, direction, p1, p7, p13, p19, p25, p31, errorCheck);
    else if (exist(vehicle, p2, p8, p14, p20, p26, p32))
        moveOneSquare(vehicle, direction, p2, p8, p14, p20, p26, p32, errorCheck);
    else if (exist(vehicle, p3, p9, p15, p21, p27, p33))
        moveOneSquare(vehicle, direction, p3, p9, p15, p21, p27, p33, errorCheck);
    else if (exist(vehicle, p4, p10, p16, p22, p28, p34))
        moveOneSquare(vehicle, direction, p4, p10, p16, p22, p28, p34, errorCheck);
    else if (exist(vehicle, p5, p11, p17, p23, p29, p35))
        moveOneSquare(vehicle, direction, p5, p11, p17, p23, p29, p35, errorCheck);
    else if (exist(vehicle, p6, p12, p18, p24, p30, p36))
        moveOneSquare(vehicle, direction, p6, p12, p18, p24, p30, p36, errorCheck);
}

bool done()
{
    return p18 == 'R';
}

int main()
{
    char vehicle;
    char direction;
    int distance;
    int numMove = 1;
    bool error = false;
    
    display_ID_and_Instructions();
    
    p1='G'; p2='G'; p3='.'; p4='.'; p5='.'; p6='Y';
    p7='P'; p8='.'; p9='.';p10='B';p11='.';p12='Y';
    p13='P';p14='R';p15='R';p16='B';p17='.';p18='Y';
    p19='P';p20='.';p21='.';p22='B';p23='.';p24='.';
    p25='O';p26='.';p27='.';p28='.';p29='T';p30='T';
    p31='O';p32='.';p33='F';p34='F';p35='F';p36='.';
    
    displayBoard();
    
    do
    {
        cout << numMove << ". Your move -> ";
        cin >> vehicle;
        vehicle = toupper(vehicle);
        if (vehicle == 'X')
            break;
        else if (vehicle == '-')
        {
            reset();
            numMove = 1;
            vehicle = ' ';
            displayBoard();
            continue;
        }
        cin >> direction >> distance;
        direction = toupper(direction);
        
        for (int x = 0; x < distance; x++)
        {
            error = true;
            moveOneSquare(vehicle, direction, error);
            if(error)
            {
                cout << "*** Move was attempted, but couldn't be completed. *** " << endl;
                break;
            }
        }
        
        displayBoard();
        numMove++;
    }while(!done());
    
    if (done())
    {
        cout << "DONE";
        endGame;
    }
}