/*
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 8: Interrupting interupts
 * 
 * Description: There are two buttons that produce and take in interrupt signals and an LCD display.
 *              One button is to interrupt whereas the other resumes and resets the process. The
 *              interrupts basically toggle between states and messages that are also displayed
 *              on the LCD.
 * 
 * Assumptions: The code I assumed was pretty easy as you basically just handle the states of the buttons
 *              and print the state out on the LCD, etc. However, I assumed that the wiring would be a 
 *              complete mess - which it was in the end.
 *              
 * References: https://www.arduino.cc/en/uploads/Tutorial/LCD_Base_bb_Fritz.png
 *             http://shazsterblog.blogspot.com/2011/11/arduino-interrupt-based-led-with-toggle.html
 *             http://playground.arduino.cc/Code/Interrupts
 * 
 */

// inclluded libraries and stuff
#include <Wire.h>
#include <LiquidCrystal.h>

// pins used for the LCD
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

// pins used for interrupt
const int stopButton = 2, resumeButton = 3;

// variable to retain state
bool state = true;

// variable to keep track of time
int t = -1; // start at -1 because we want to see zero (0) first and not one (1)



// simply print the time...
// however, as the time increases, it will take up more space
// so to fix that, when time grows, simply change the index
// in which it starts at
void printTime()
{
  int shift = 0;

  for (int x = t; x > 9; x /= 10)
    shift++;

  lcd.setCursor(7 - shift, 1);
  lcd.print(t);
}



// while the wait is running
void onRun()
{
  // clear the lcd beforehand because when going from the other state
  // to this state, some characters in the buffer are remaining - so
  // simply fix with this.
  lcd.clear();
  
  // while running,

  // increment the time
  t++;

  // print the message indicating how long the thing has
  // been waiting for
  lcd.setCursor(0,0); // first row
  lcd.print("Waited for...");

  lcd.setCursor(8,1); // second row
  lcd.print(" seconds");
  printTime();

  // every 1000 ms = 1 sec
  delay(1000);
}



// while paused, print the message on the lcd
// saying that it's paused
void onPause()
{
  lcd.setCursor(0,0);
  lcd.print("Press Other Btn");

  lcd.setCursor(0,1);
  lcd.print("To resume runnin");
}



// while stopped
void onStop()
{
  // basically change the state to stop
  // and clear the screen so that the other
  // message can be printed
  if (state == true)
  {
    state = !state;
    lcd.clear();
  }
}



// when the user presses the button again...
void onRestart()
{
  if (state == false)
  {
    // reset the time elapsed
    t = -1;

    state = !state;

    // clear the LCD to display the next message
    lcd.clear();
  }
}



void setup() 
{
  // put your setup code here, to run once:

  // 16x2 LCD display
  lcd.begin(16, 2);

  // initialize button pins
  pinMode(stopButton, INPUT_PULLUP);
  pinMode(resumeButton, INPUT_PULLUP);

  // attach the pins to interrupt and pass in functions as
  // parameters to allow interrupts
  attachInterrupt(digitalPinToInterrupt(stopButton), onStop, RISING);
  attachInterrupt(digitalPinToInterrupt(resumeButton), onRestart, RISING);
}



void loop() 
{
  // put your main code here, to run repeatedly:
  if (state == true)
    onRun();
  else
    onPause();
}
