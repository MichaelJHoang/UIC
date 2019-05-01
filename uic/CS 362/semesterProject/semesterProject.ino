/*
 *  Authors: Jon-Michael Hoang | jhaong6 | 657540122
 *           Ronny Recinos     | rrecin2 |
 *  
 *  Desc: This program pretty much allows the car to play music at will,
 *        utilizes a time-of-flight (ToF) sensor as an anti-collision system,
 *        and communicates with the other arduino through serial.
 *        
 *  References: https://musescore.com/pieridot/memeophone
 *              https://www.instructables.com/id/Translate-Songs-to-Be-Played-on-Arduino/
 *              https://learn.adafruit.com/adafruit-vl53l0x-micro-lidar-distance-sensor-breakout/arduino-code
 *              https://maker.pro/arduino/projects/arduino-speaker
 *              https://www.arduino.cc/reference/en/language/functions/communication/serial/
 * 
 */
//SD card library
//#include <SD.h>
//#include <SPI.h>

// ToF library
#include "Adafruit_VL53L0X.h"
// ToF object
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
// instantiate measurement object for the ToF sensor
VL53L0X_RangingMeasurementData_t measure;

// buffer to be used for readBytes
char stringBuffer[15];

// notes in GAS GAS GAS by Initial D
int melody[] = 
{ 
  740, 554, 740, 1109, 988, 880, 740, 740, 
  554, 740, 1109, 988, 880, 740, 880, 831, 
  659, 880, 831, 659, 880, 831, 659, 988, 
  831, 659, 740, 554, 740, 1109, 988, 880, 
  740, 740, 554, 740, 1109, 988, 880, 740, 
  880, 880, 880, 831, 831, 880, 1109, 880, 
  1109, 880, 1109, 831, 1047, 831, 1047, 740, 
  554, 740, 1109, 988, 880, 740, 740, 554, 
  740, 1109, 988, 880, 740, 880, 831, 659, 
  880, 831, 659, 880, 831, 659, 988, 831, 
  659, 740, 554, 740, 1109, 988, 880, 740, 
  740, 554, 740, 1109, 988, 880, 740, 1109, 
  1047, 988, 932, 880, 932, 988, 1047, /*0*/
};

// note durations for the corresponding notes above
int noteDurations[] = 
{ 
  108, 108, 108, 108, 108, 108, 216, 108, 
  108, 108, 108, 108, 108, 216, 108, 108, 
  108, 216, 108, 216, 108, 108, 108, 216, 
  108, 216, 108, 108, 108, 108, 108, 108, 
  216, 108, 108, 108, 108, 108, 108, 216, 
  108, 216, 108, 216, 216, 108, 108, 216, 
  216, 108, 108, 216, 216, 216, 216, 108, 
  108, 108, 108, 108, 108, 216, 108, 108, 
  108, 108, 108, 108, 216, 108, 108, 108, 
  216, 108, 216, 108, 108, 108, 216, 108, 
  216, 108, 108, 108, 108, 108, 108, 216, 
  108, 108, 108, 108, 108, 108, 216, 216, 
  216, 216, 216, 216, 216, 216, 216, /*1728*/
};

// flag that can be toggled on and off by the ps4 controller
bool repeatFlag = true;

// basically plays the song
void playSong ()
{
  // read in from the serial
  Serial.readBytes(stringBuffer, 8);

  if (strcmp(stringBuffer, "option01") == 0)
  {
    // flag to act as double security 
    repeatFlag = true;
    for (int thisNote = 0; (thisNote < sizeof(melody) / sizeof(int)) && repeatFlag == true; thisNote++)
    { 
      // this is here because there's no threading for Arduinos
      // so we have to implement the illusion of threading by having the
      // computer quickly switch from one task to another...
      
      // take in a measurement
      lox.rangingTest(&measure, false);
      
      if (measure.RangeStatus != 4) 
      {
        // in range
        Serial.println(measure.RangeMilliMeter);
      } 
      else 
      {
        // out of range
        Serial.println("9001");
      }

      // play this note for this long
      tone(6, melody[thisNote], noteDurations[thisNote] * .7);    
      delay(noteDurations[thisNote] + 10);    
      noTone(6);  // no overlapping sounds
    }
  }
  else if (strcmp(stringBuffer, "option2") == 0)
  {
    repeatFlag = false;
  }
}

void setup() 
{
  Serial.begin (9600);

  // wait until the serial port opens up
  while (!Serial)
    delay(1);

  if (!lox.begin())
    while(1);
}

void loop() 
{
  // no need to repeat the melody.
  playSong();

  // take in a measurement
  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) 
  {
    // in range
    Serial.println(measure.RangeMilliMeter);
  } 
  else 
  {
    // out of range
    Serial.println("9001");
  }

  // need to have some sort of delay or else it'll break.
  delay(1);
}
