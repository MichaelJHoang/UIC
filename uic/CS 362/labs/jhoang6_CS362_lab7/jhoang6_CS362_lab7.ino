/*
 * Name: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 7: Serial synchronization
 * 
 * Desc: Using two arduinos, two leds, and two buttons, if one arduino's
 *       button is pressed, the other arduino's LED lights up, vice versa.
 *       
 * Assumptions: Wiring for this lab was pretty straightforward however,
 *              programming this whole thing was a pain in the ass which took
 *              me hours to complete.
 *              
 *              I also assumed that each arduino pretty much had the same code -
 *              in which it did.
 *              
 * References:
 * https://iotguider.in/wp-content/uploads/2017/08/Serial-communication-between-Arduino.png
 * https://www.arduino.cc/en/Tutorial/MasterWriter
 * https://www.arduino.cc/en/Serial/write
 * https://diygeeks.org/tutorials/arduino/push-button-and-led-with-arduino-digital-input-output/
 * 
 */

// initialize the led and button pins to their respective pin number
const int LED = 10;
const int button = 8;

// variable to retain the previous led's state
int ledState = 0;

// initialize the inputs and outputs
void setup ()
{
  pinMode (button, INPUT);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // while the serial is breathing
  while (Serial.available())
  {
    // read in the serial input (also used for debugging)
    int input = Serial.read();

    // if the input is 'a' (this [if] part is also used for debugging)
    if (input == 97)
    {
      // if the led was previously turned off, turn it on and save the state
      if (ledState == 0)
      {
        ledState = 1;
        digitalWrite (LED, HIGH);
      }
      // else that means that the led was previously turned on, 
      // so turn it on and save the state
      else
      {
        ledState = 0;
        digitalWrite (LED, LOW);
      }
    }
  }

  // this part here is pretty much used for debugging purposes
  // read in the state of the button
  int buttonValue = digitalRead(button);

  // while the button is not pressed, constantly print out 'a' within
  // the serial monitor
  if (buttonValue == LOW)
  {
    Serial.write(97);
  }

  // delay it by a second so that the serial monitor won't be spammed with 'a''s
  // and that the lights won't go flashing on and off really fast
  // while the button is held
  delay (1000);
}
