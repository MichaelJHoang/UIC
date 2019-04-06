/*
 * 
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 6: Reading in user input for dates
 *
 * Desc: Utilize serial to receive user input for a date and time
 *       if the user input is correct, display it on the 16x2 LCD display
 *       otherwise throw an error message on the display.
 *       
 * Assumptions: I assumed that the lab's setup is pretty much as the same as
 *              the one with the potentiometer so I went with that.
 *              Getting the Time library installed and getting it to finally work
 *              was a bit annoying but getting user input was a bit more difficult.
 *              
 *              I also checked the user's input for leap years just in case, too.
 *              
 * References: http://www.pjrc.com/teensy/td_libs_Time.html
 *             http://playground.arduino.cc/Code/Time
 *             https://www.arduino.cc/en/Tutorial/LiquidCrystalDisplay
 * 
 */

// including any necessary libraries to accomplish this lab
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h> 
#include <LiquidCrystal.h>

// telling the OS how the LCD is wired
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// basic variables for date and time
int MONTH, DAY, YEAR;
int HOUR, MIN, SEC;

// basic variables for user input and flag toggling/checking
int userInput = 0;
bool flag = false;

void setup()
{
  // setting up the serial id?
  Serial.begin(9600);

  // begin with a 16x2 lcd display
  lcd.begin(16,2);

  // begin the thing by telling the user on the lcd display to
  // look at the serial monitor
  lcd.setCursor(0,0);
    lcd.print("HEY! LISTEN!");
  lcd.setCursor(0,1);
    lcd.print("@SERIAL MONITOR!");

  // and also on the serial monitor, prompting for user input
  Serial.print ("\nPlease enter in the date (MM DD YYYY) and time (HOUR MIN SEC)");
  Serial.print ("\nExample: 1 1 2019 6 9 18");
}

void loop()
{
  while (Serial.available() > 0)
  {
    // take in the user's input
    // with the format:
    // MM DD YYYY HOUR MIN SEC
    MONTH = Serial.parseInt();
    DAY = Serial.parseInt();
    YEAR = Serial.parseInt();
    HOUR = Serial.parseInt();
    MIN = Serial.parseInt();
    SEC = Serial.parseInt();

    // whole block of code checking whether or not if the user's input is valid.
    // if it is, it Serial.prints a success message and displays the time on the
    // lcd display
    // if it is not, it Serial and lcd prints an error message indicating what the error
    // is on the lcd display until the user makes a valid input.
    // if there was a previously valid input and the user enters in an invalid date or time,
    // it displays an error message for three seconds before going back to the date and time in
    // which the user previously correctly entered.
    if (MONTH >= 1 && MONTH <= 12)
    {
      // months with 31 days
      if (MONTH == 1 || MONTH == 3 || MONTH == 5 || MONTH == 7 || MONTH == 8 || MONTH == 10 || MONTH == 12)
      {
        // check if valid day
        if (DAY >= 1 && DAY <= 31)
        {
          // check if invalid year
          if (YEAR < 1000 || YEAR > 9999)
          {
            lcd.clear();
            Serial.print("\nIncorrect year...");
            lcd.print("Incorrect year");
            delay (3000);
            break;
          }
        }
        else
        {
          lcd.clear();
          Serial.print("Incorrect day...");
          lcd.print("Incorrect day");
          delay (3000);
          break;
        }
      }
      // check for months with 30 days
      else if (MONTH == 4 || MONTH == 6 || MONTH == 9 || MONTH == 11)
      {
        // check if valid day
        if (DAY >= 1 && DAY <= 30)
        {
          // check if invalid year
          if (YEAR < 1000 || YEAR > 9999)
          {
            lcd.clear();
            Serial.print("\nIncorrect year...");
            lcd.print("Incorrect year");
            delay(3000);
            break;
          }
        }
        else
        {
          lcd.clear();
          Serial.print("\nIncorrect day...");
          lcd.print("Incorrect day");
          delay(3000);
          break;
        }
      }
      // check february
      else if (MONTH == 2)
      {
        // check if valid day and if it's also a leap year
        if (DAY >= 1 && DAY <= 28 && (YEAR % 4 != 0))
        {
          // check if invalid year
          if (YEAR < 1000 || YEAR > 9999)
          {
            lcd.clear();
            Serial.print("\nIncorrect year...");
            lcd.print("Incorrect year");
            delay(3000);
            break;
          }
        }
        else if (DAY >= 1 && DAY <= 29 && (YEAR % 4 == 0))
        {
          // check if invalid year
          if (YEAR < 1000 || YEAR > 9999)
          {
            lcd.clear();
            Serial.print("\nIncorrect year...");
            lcd.print("Incorrect year");
            delay(3000);
            break;
          }
        }
        else
        {
          lcd.clear();
          Serial.print("\nIncorrect day...it's also February - so, check for leap year?");
          lcd.print("Incorrect day");
          delay(3000);
          break;
        }
      }
    }
    else
    {
      lcd.clear();
      Serial.print("\nIncorrect month...");
      lcd.print("Incorrect month");
      delay(3000);
      break;
    }
    
    // check for a bad time
    if (HOUR < 0 || HOUR > 23)
    {
      lcd.clear();
      Serial.print("Incorrent hour...");
      lcd.print("Incorrect hour");
      delay(3000);
      break;
    }
    if (MIN < 0 || MIN > 59)
    {
      lcd.clear();
      Serial.print("Incorrent minute...");
      lcd.print("Incorrect min.");
      delay(3000);
      break;
    }
    if (SEC < 0 || SEC > 59)
    {
      lcd.clear();
      Serial.print("Incorrect second...");
      lcd.print("Incorrect sec.");
      delay(3000);
      break;
    }

    // tell the user that their input is a success and tell them to check
    // the lcd display
    Serial.print("\nUser input success! Check the LCD display!");
    setTime(HOUR, MIN, SEC, DAY, MONTH, YEAR);
    flag = true;

  }

  // finally print out the user's input onto the lcd screen
  if (flag == true)
  {
    lcd.clear();

    // date on top first
    lcd.setCursor(0,0);
    lcd.print(month());
    lcd.print("/");
    lcd.print(day());
    lcd.print("/");
    lcd.print(year());

    // print the time on the bottom line
    lcd.setCursor(0,1);
    lcd.print(hour());
    lcd.print(":");
    lcd.print(minute());
    lcd.print(":");
    lcd.print(second());
  }
  
}
