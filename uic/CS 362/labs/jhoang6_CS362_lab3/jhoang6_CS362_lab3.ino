/*
 * 
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * Lab 3 - LCD display
 * Desc: Print out the author's name within the first row of the LCD 
 *       and print out the author's quote in the second row. However, the quote must be
 *       >16 characters long and must loop throughout the second row whereas the author's name
 *       has to remain still within the first row.
 *       
 * Assumptions: The wiring was easy - following the guidelines however the looping the quote part
 *              wasn't that bad but needed me to think for a sec/
 *              
 * References: https://www.arduino.cc/en/Tutorial/LiquidCrystalSetCursor
 * 
 */


#include <LiquidCrystal.h>

// set up the lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// quote to be displayed on the screen
String originalQuote = "I don't live by quotes because I don't live by anyone else's words but mine";

// string to allow the appearence that it loops
String loopQuote;

// display positions from and to
int from = 0;
int to = 16;  // 16 characters available to be displayed

// offset
int offset = 0;

// quote length
int quoteLength = originalQuote.length();

void setup() 
{
  // set cursor position to 0,0
  lcd.begin(2, 16);
  
  loopQuote = originalQuote + originalQuote.substring(0,15);
}

void loop() 
{
  // first row and first column
  lcd.setCursor(0, 0);
  
  // print out name on the first line
  lcd.print("J.Michael Hoang");

  // second row and first column
  lcd.setCursor(0, 1);

  // convert the quote
  lcd.print(convertQuote());

  // delay by half a second to give it a nice loop feel
  delay(500);
}

// function to constantly convert the quote to give it a looping
// characteristic
// aka simulating a loop
String convertQuote()
{
  // reset offset 
  if (offset + 16 == quoteLength)
    offset = 0;

  // get the new quote by taking the loopQuote's substring based on the offset
  String newQuote = loopQuote.substring(from + offset, to + offset);

  // increase the offset so that it can continue the loop
  offset++;

  // return the newQuote
  return newQuote;
}
