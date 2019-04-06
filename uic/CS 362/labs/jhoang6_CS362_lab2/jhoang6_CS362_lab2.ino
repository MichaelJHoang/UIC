/*
 * 
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * CS 362: Lab 2 - Binary Buttons
 * 
 * Desc: Press two buttons to increment LEDs which represent binary values
 *       since there are 3 LEDs, there are three bits so the max value is 7
 *       whereas the min value is 0.
 *       
 * Assumptions: If you are at 7 and press up, it goes back to 0
 *              If you are at 0 and press down, it goes back to 7
 *              
 *              At first setting up the hardware was a bit...hard but then it got easy
 *              the more I studied the schematics listed below in the references.
 *              
 *              As for the coding part, it took awhile but nonetheless it was easy - 
 *              using knowledge from CS261 for the flags and using razzle dazzle C++ magic code
 *              to make things run well.
 *              
 *              I also assume that the grader not only reads this, but also the comments surrounding the code
 *              as well as it goes in depth in my design process.
 *              
 * References: https://www.arduino.cc/en/tutorial/button
 * 
 *             for this reference, I did not use any of the code. I just used the schematic: 
 *             https://www.instructables.com/id/How-to-use-a-Push-Button-Arduino-Tutorial/
 * 
 * Date: 2/6/2019
 * 
 */

const int b1 = 11;  // count++ button
const int b2 = 12;  // count-- button

// store the previous button states
int oldB1 = LOW, oldB2 = LOW;

// RGB lights to represent the 3-bit binary values
const int R = 7;
const int G = 6;
const int B = 5;

// flags to tell what gets turned on/off
bool redFlag, greenFlag, blueFlag;

// counter to keep track of the user's increments and
// decrements
int count = 0;

void setup() 
{
  // put your setup code here, to run once:
  pinMode (b1, INPUT);
  pinMode (b2, INPUT);

  pinMode (R, OUTPUT);
  pinMode (G, OUTPUT);
  pinMode (B, OUTPUT);
}

void loop() 
{
  // get the current state of the button
  int newB1 = digitalRead (b1);
  int newB2 = digitalRead (b2);

  // increment based on current and previous states
  if (newB1 == HIGH && oldB1 == LOW)
    count++;
  else if (newB2 == HIGH && oldB2 == LOW)
    count--;

  // handle looping back
  // e.g. 0 loops to 7
  //      and 7 loops to 0
  // is count 8? if so, make count 0.
  // if not, is count -1? if so, make count 7.
  // if all cases fail under magical circumstances, go back to count
  count = (count == 8) ? 0 : (count == -1) ? 7 : count;

  // handle flags here
  // each flag handles 1 bit in the 3 bit code
  // how this works: given a value like 7,
  // red = 7%2 = 1 -> __1
  // green = 7/2 % 2 = 1 -> _11
  // blue = 7/2/2 % 2 = 1 -> 111
  // -> 111(base 2) == 7(base 10)
  redFlag = (count%2 == 1) ? true : false;  // handles __X bit
  greenFlag = ((count/2)%2 == 1) ? true : false; // handles _X_ bit
  blueFlag = (((count/2)/2)%2 == 1) ? true : false; // handles X__ bit

  // e.g. "5" would have 101
  // by following the same example above, 
  // 5%2 = 1 -> __1
  // 5/2 = 4 % 2 = 0 -> _01
  // 5/2/2 = 1 % 2 = 1 -> 101
  // 101(base2) == 5(base 10)

  // now that the flags are given values, represent them in binary
  if (redFlag)
    digitalWrite (R, HIGH);
  else
    digitalWrite (R, LOW);

  if (greenFlag)
    digitalWrite (G, HIGH);
  else
    digitalWrite (G, LOW);

  if (blueFlag)
    digitalWrite (B, HIGH);
  else
    digitalWrite (B, LOW);

  // store previous button state to refer to future states
  oldB1 = newB1;
  oldB2 = newB2;
}
