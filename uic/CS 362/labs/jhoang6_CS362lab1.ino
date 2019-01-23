// Author: Jon-Michael Hoang
// Class: CS 362
// Lab: 1 - blinker

void setup() 
{
  // put your setup code here, to run once:
  pinMode (0, OUTPUT);  // red
  pinMode (7, OUTPUT);  // green
  pinMode (12, OUTPUT); // blue
  pinMode (LED_BUILTIN, OUTPUT);  // builtin 
  
}

void loop() 
{
  for (int x = 0; x < 4; x++)
  {
    // use switch cases to cycle through lights
    switch (x)
    {
      // all off but red
      case 0:
        digitalWrite (0, HIGH);
        digitalWrite (7, LOW);
        digitalWrite (12, LOW);
        digitalWrite (LED_BUILTIN, LOW);
        break;
      // all off but green
      case 1:
        digitalWrite (0, LOW);
        digitalWrite (7, HIGH);
        digitalWrite (12, LOW);
        digitalWrite (LED_BUILTIN, LOW);
        break;
      // all off but blue  
      case 2:
        digitalWrite (0, LOW);
        digitalWrite (7, LOW);
        digitalWrite (12, HIGH);
        digitalWrite (LED_BUILTIN, LOW);
        break;
      // all off but builtin
      case 3:
        digitalWrite (0, LOW);
        digitalWrite (7, LOW);
        digitalWrite (12, LOW);
        digitalWrite (LED_BUILTIN, HIGH);
        break;
    }
    // each one blinks for however many milliseconds defined
    delay (100);
  }
}
