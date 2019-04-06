/*
 * 
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 4: Photoresistor Lab
 * 
 * Desc: Using an LCD screen and a photoresistor, display how much light the photoresistor
 *       detects onto the LCD screen
 *       
 * Assumptions: The setup was annoying but other than that, the whole lab was pretty much easy
 * 
 * References: https://www.arduino.cc/en/tutorial/AnalogInput
 * 
 */

// libraries used
#include <LiquidCrystal.h>

// initialize the pins to the lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// simple setup
void setup() 
{ 
  lcd.begin(16, 2);
  lcd.clear();
}

// loop
void loop()
{
  // clear the buffer otherwise the words will overwrite on top of each other
  // e.g. [Dark Light]
  lcd.clear();
  
  // read in the photoresitor sensor value, which had analog values
  double sensorValue = analogRead(A0);

  // use the sensor value to create "levels of brightness"
  int level = (sensorValue/1023)*100;

  // set the cursor to the top left of the lcd display
  lcd.setCursor(0, 0);

  // using the level, indicate how bright it is
  // pretty self-explanatory on what this part is
  if (level <= 10)
  {
    lcd.print("dark"); 
  }
  else if (level <= 20 && level > 10)
  {
    lcd.print("partially dark"); 
  }
  else if (level <= 30 && level > 20)
  {
    lcd.print("medium"); 
  }
  else if (level <= 40 && level > 30)
  {
    lcd.print("partially light"); 
  }
  else
  {
    lcd.print("fully lit");
  }

  // delay by half a second so it won't constantly change
  delay(500);
}
