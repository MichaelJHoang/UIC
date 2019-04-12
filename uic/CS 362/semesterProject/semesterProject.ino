/*
 * Author: Jon-Michael Hoang
 * 
 * CS 362 Semester Project: GAS GAS GAS
 * 
 * Desc: This code is used for the time-of-flight (ToF) sensors, the speakers, and the LEDs.
 *       The thing will also communicate with Ronny Recinos' arduino to make the car be able to 
 *       have brake lights, an anti-collision system, and be able to play music.
 * 
 * 
 */


// general libraries
#include <Wire.h>



// device specific libraries
#include "Adafruit_VL53L0X.h"



// TODO: include the other devices
Adafruit_VL53L0X lox = Adafruit_VL53L0X();



// TODO: with whatever's included, set it up
void setup() 
{
  // put your setup code here, to run once:

  // serial communication with the other arduino
  Serial.begin(9600);

  // wait until serial port opens for native devices
  while (!Serial)
  {
    delay(1);
  }

  if (lox.begin())
  {
    // TODO: What to do when it begins, the lox sensor, that is
  }
}




void loop() 
{
  // put your main code here, to run repeatedly:

  /*
   * 
   *  ToF sensor stuff here
   * 
   */
  VL53L0X_RangingMeasurementData_t loxData;

  // read in the measurements. pass in true for debugger
  lox.rangingTest (&loxData, false);

  //
  if (measure.RangeStatus != 4)
  {
    // TODO: Include code where if the sensor detects something close, send
    //       signals to the other arduino - telling it to slow down and stop.
  }

  /*
   * 
   *  TODO: Add code for the speakers here
   * 
   */



   /*
    * 
    *  TODO: Add code for the leds, communications, etc here
    * 
    */
}
