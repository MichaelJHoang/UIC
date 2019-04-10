/*
 * Name: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 9: Communication b/t Arduino and my laptop
 * 
 * Desc: With two analog sensors (in this case, the photoresistor and potentiometer) connected to
 *       the arduino, take in and parse data from the arduino to my laptop so that the Processing
 *       program can read it and make a pretty graph on the screen.
 * 
 * Assumption: Wiring is easy - especially for the photoresistor and the potentiometer because
 *             there's little to no wires to worry about.
 *             
 *             The coding part was pretty straightforward, too...with the help of guides.
 *             
 * References:  https://www.instructables.com/id/How-to-use-Potentiometer-Arduino-Tutorial/
 *              https://learn.adafruit.com/photocells/using-a-photocell
 *              https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
 *              https://www.youtube.com/watch?v=C_gyGXWIgHY
 * 
 */

// analog input variables - can't use int so might as well #define
// photoresistor
#define photo A0 
// potentiometer
#define pot A1

void setup() 
{
  // put your setup code here, to run once:
  // set serial to 9600 so that processing will connect with the arduino
  Serial.begin(9600);

  // set up the connection between processing and the arduino
  while (Serial.available() <= 0)
  {
    // constantly sends out a "signal" until handshake is established
    Serial.println("X");
    delay (100);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  
  // constantly read in values from both of the devices and convert them into a string for
  // processing to parse
  Serial.println(String(analogRead(photo)) + " " + String(analogRead(pot)));
}
