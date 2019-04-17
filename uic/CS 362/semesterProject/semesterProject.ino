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


#include <SPI.h>
#include <SD.h>

// ToF sensor
#include "Adafruit_VL53L0X.h"

// might want to include the library to use this
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

byte inByte; //byte read from terminal
bool sdInitSuccess = false; //card init status
File myFile;
String readText; //text read from file
char readCharArray[128]; //buffer for reading from file

unsigned long fileSize; //size of opened file
unsigned long filePos = 0;
//---------------------------------------------------------------//
void setup() 
{
  // might want to change this, ronny
  Serial.begin(9600);
  while (!Serial) 
  {
    delay(1); //wait for the serial port to connect.
  }

  Serial.println("Testing sensors and SD card...");

  // testing ToF sensor
  if (!lox.begin()) 
  {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}
//---------------------------------------------------------------//
void loop() 
{
  if (Serial.available() > 0) 
  {
    // ToF stuff
    VL53L0X_RangingMeasurementData_t measure;

    Serial.print("Reading a measurement... ");
    lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
    if (measure.RangeStatus != 4) 
    {  // phase failures have incorrect data
      Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    } 
    else 
    {
      Serial.println(" out of range ");
    }
      
    delay(100);





    // SD CARD STUFF
    inByte = Serial.read();
    if (inByte == 'i' || inByte == 'I')
    {
      if (sdInitSuccess) 
      { //check if card is initialized already
        Serial.println("Already initialized.\n");
      }
      else if (!sdInitSuccess) 
      { //if not already initialized
        Serial.println("Initializing SD Card..");
        if (!SD.begin(10)) 
        { //using pin 10 (SS)
          Serial.println("Initialization failed!\n");
          sdInitSuccess = false; //failure
          return;
        }
        else 
        {
          Serial.println("Intitialization success.");
          Serial.println();
          sdInitSuccess = true;
        }
      }
    }
    else if (inByte == 'n' || inByte == 'N') 
    {
      if (sdInitSuccess) 
      { //proceed only if card is initialized
        myFile = SD.open("TEST.txt", FILE_WRITE);
        if (myFile) 
        {
          Serial.println("File opened successfully.");
          Serial.println("Writing to TEST.text");
          myFile.println("Line 1");
          myFile.close(); //this writes to the card
          Serial.println("Done");
          Serial.println();
        }
        else { //else show error
          Serial.println("Error opeing file.\n");
        }
      }
      else 
      {
        Serial.println("SD Card not initialized.");
        Serial.println("Type \"i\" to initialize.\n");
      }
    }
    else if (inByte == 'r' || inByte == 'R') 
    {
      if (sdInitSuccess) { //proceed only if card is initialized
        myFile = SD.open("TEST.txt");
        if (myFile) 
        {
          Serial.println("File opened successfully.");
          Serial.println("Reading from TEST.text");
          readText = (String) readUntil(myFile, 10); //read until newline
          Serial.print(readText);
          Serial.print(", ");
          Serial.println(filePos); //print current file position
          Serial.println();
          myFile.close();
        }
        else 
        {
          Serial.println("Error opening file.\n");
        }
      }
      else 
      {
        Serial.println("SD Card not initialized.");
        Serial.println("Type \"i\" to initialize.\n");
      }
    }
    else 
    {
      Serial.println("Not recognized.\n"); //unknown cmd
    }
  }
}
//--------------------------------------------------------------//
String readUntil(File &myFile, char n) 
{ //read until n
  int i = 0;
  myFile.seek(filePos); //read from current filepos
  
  do 
  {
    if (myFile.peek() != -1) 
    { //check if file is empty
      readCharArray[i++] = myFile.read(); //read otherwise
      filePos++; //advance the filepos
    }
  } while ((myFile.peek() != -1) && (readCharArray[i - 1] != n)); //if not eof | \n
  
  if (myFile.peek() == -1) 
  { //if eof reached
    filePos = 0; //if eof, reset to start pos
  }
  
  readCharArray[i - 1] = '\0'; //remove the extra \n
  
  return readCharArray;
}
//-------------------------------------------------------------//
