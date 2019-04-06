/*
 * 
 * Author: Jon-Michael Hoang | jhoang6 | 657540122
 * 
 * Lab 5 - Detecting light and making noise with parallel circuitry
 * 
 * Desc: What this code is supposed to do is that at the same time, allow the user to turn the potentiometer to adjust
 *       the buzzer noise and to shine light/cast shade over the photoresistor to play with the LEDs which shows how much
 *       brightness and darkness it detects.
 *       
 * Assumptions: It was pretty tricky to get both of them running at the same time hardware wise. In addition to that, getting the
 *              LEDs and the photoresistor was annoying. However, the coding part of this lab was pretty straightforward. In the
 *              end, though, it did what it did for the lab assignment.
 * 
 * References: http://fritzing.org/projects/photo-resistor-led-scale
 *             https://create.arduino.cc/projecthub/SURYATEJA/use-a-buzzer-module-piezo-speaker-using-arduino-uno-89df45
 */

// contains the analog value from the photoresistor
int lightValue = 0;
// contains the analog value from the potentiometer
int potValue = 0;

// array that represents the 4 LEDs and their pins
int led[4] = {0,1,2,3};

// buzzer pin
int buzzer = 8;
// frequency the buzzer will have
int freq = 0;

void setup()
{
  // set up the photoresistor
  pinMode (A0, INPUT);
  
  // set up the LED pins
  for (int x = 0; x < 4; x++)
    pinMode (led[x], OUTPUT);

  // set up the buzzer
  pinMode (buzzer, OUTPUT);
  // set up the potentiometer
  pinMode (A1, INPUT);
}

void loop()
{
  // read the analog value from the photoresistor
  lightValue = analogRead(A0);
  // read the analog value for the potentiometer
  potValue = analogRead (A1);

  // by default all turned off - clear the states
  // also means that it is by default, detecting super bright
  // things
  for (int x = 0; x < 4; x++)
    digitalWrite (led[x], LOW);

  // determine how many lights are lit based on how dark 
  // lightValue is
  if (!(lightValue >= 300)) // first light on: pretty bright
    digitalWrite (led[0], HIGH);
  if (!(lightValue >= 200)) // first two lights on: somewhat bright
    digitalWrite (led[1], HIGH);
  if (!(lightValue >= 100)) // first three lights on: a bit shady
    digitalWrite (led[2], HIGH);
  if (!(lightValue >= 50))  // all lights on: pretty dark
    digitalWrite (led[3], HIGH);

  // map the frequency to some values including potValue
  freq = map(potValue, 0, 1000, 666, 333);
  // ...and set the tone based on that
  tone (buzzer, freq);
  
  // delay so that it wouldn't constantly flicker
  // and hurt peoples' eyes and ears
  delay (50);
}
