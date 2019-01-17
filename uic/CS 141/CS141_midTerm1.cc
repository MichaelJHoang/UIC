/*
  CS 141 Midterm #1, Spring 2017, Reed
  
  This midterm exam consists of a single problem.  Partial
  credit will be given for correct output.
  
  You may not communicate with anyone else during the test.  You may
  consult your text, your notes, files archived in your account, and the Web,
  but not chat or any sort of messaging service.
  
  You don't need to comment your code or worry about having meaningful
  variable names.  We will only be grading the output of your program. 
  Please use only the print statements that are provided and do not add
  any others.
  
  You may assume perfect input (i.e. no error checking is necessary) unless
  I specifically state otherwise.
  
  Turn in your solution(s) using Blackboard into the assignment name(s)
  given to you by your TA.
  
  *******************************************************************
  
  Write a program that reads in 4 distinct positive integers into
  4 variables. Find and display the following:
      1. The minimum of the 4 numbers
      2. The maximum of the 4 numbers
      3. The average of the other two numbers (the ones that
         are not min or max).
  Hint: Think about writing a function for min( int x, int y)
  and a function for max( int x, int y) and reuse those!
  
  An example of running this program is:
      Name: Dale Reed, Midterm 1, CS 141, Fall 2017
      Enter 4 integers: 13 6 4 7
      The smallest is: 4
      The largest is: 13
      The average of the other two is: 6.5
      Done.
  
  Running this program again could be:
      Name: Dale Reed, Midterm 1, CS 141, Fall 2017
      Enter 4 integers: 5 7 41 24
      The smallest is: 5
      The largest is: 41
      The average of the other two is: 15.5
      Done.
 
  
  Call this program    netid.cpp   where you  substitute your actual netid.
  (For instance if your netid is reed, then you would turn in reed.cpp)
  Turn this into Blackboard into the project called Midterm_n where n
  is the time your lab starts.  For example if your lab starts at 9 you
  will turn your solution into the project called Midterm_9.
  *******************************************************************
  Start with the following code and add the parts you need to make it work.
  */
 
#include <iostream>
#include <vector>
using namespace std;

int main ()
{
    vector <int> input(4);
    int min = 99999;
    int max = -99999;
    int sum = 0;
     
    cout << "Name: Jon-Michael Hoang, Midterm 1, CS 141, Fall 2017" << endl;
    cout << "Enter 4 integers: " ;
     
    for (int x = 0; x < 4; x++)
        cin >> input.at(x);
    
    for (int x =0; x < input.size(); x++)
        min = (input.at(x) < min) ? input.at(x):min;
    cout << "The smallest is: " << min;
    
    for (int x =0; x < input.size(); x++)
        max = (input.at(x) > max) ? input.at(x):max;
    cout << "\nThe largest is: " << max;
     
    for (int x = 0; x < input.size(); x++)
        sum += input.at(x);
    sum -= (max + min);
    cout << "\nThe average of the other two is: " << (double)&sum/2;
    
    cout << "\nDone. " << endl;
    
    return 0;
}