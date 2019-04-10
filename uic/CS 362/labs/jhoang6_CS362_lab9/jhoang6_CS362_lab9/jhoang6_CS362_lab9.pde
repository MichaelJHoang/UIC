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

// imported libraries
import processing.serial.*;

// the port which connects to the arduino
Serial thePort;

// variables to contain the previous and current values for both
// of the devices
float previousPhoto = 0, previousPot = 0, currentPhoto, currentPot;

// variable to keep track of the "x" coordinate of the lines
int x = 1;

// variable to determine whether or not the connection was made
boolean c = false;

void setup ()
{
  // setup window size
  size(1000, 1000);
  
  // and the background
  background(255);
  
  // connect the port
  thePort = new Serial(this, Serial.list()[0], 9600);
  
  // delimiter?
  thePort.bufferUntil('\n');
}

// draw function to draw two lines on a single graph
void draw ()
{
  // draw on the graph the data related to the photoresistor
  stroke(0, 0, 255);
  
  // convert analog into points relative to screen size
  currentPhoto = map(currentPhoto, 0, 1023, 0, height);
  
  // draw the line 
  line(x - 1, height - previousPhoto, x, height - currentPhoto);
  
  // update previous
  previousPhoto = currentPhoto;
  
  // same thing above but with the potentiometer
  stroke(0, 255, 0);
  currentPot = map(currentPot, 0, 1023, 0, height);
  line(x - 1, height - previousPot, x, height - currentPot);
  previousPot = currentPot;
  
  // reset screen when the line goes all the way to the right
  if (x >= width)
  {
    x = 0;
    
    // have this line of code to add another layer on top of the frame buffer
    // to give illusion of "resetting"
    background(255);
  }
  else
    x++;
}

// serial event handler function
void serialEvent (Serial thePort)
{
  // read the string sent from the arduino
  String string = thePort.readStringUntil('\n');
  
  // check for valid string
  if (string != null)
  {
    // connect if not connected already
    if (c == false)
    {
      // clean up the string
      string = trim(string);
      
      // check if data received is valid - if so, setup the connection
      if (string.equalsIgnoreCase("x"))
      {
        c = true;
        thePort.write ('X');
      }
    }
    else
    {
      // parse the data
      int delimiter = string.indexOf(" ");
      int end = string.indexOf ("\n") - 1;
      
      // extract
      currentPhoto = int(trim(string.substring(0, delimiter)));
      currentPot = int(trim(string.substring(delimiter + 1, end)));
    }
  }
}
