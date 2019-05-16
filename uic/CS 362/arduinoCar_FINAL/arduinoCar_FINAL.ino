// Bluetooth Settings
#include <PS4BT.h>
#include <usbhub.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
#include <L298N.h>

/*
 * IN1 = WHITE WIRE
 * IN2 = YELLOW WIRE
 * 
 * IN3 = BLUE WIRE
 * IN4 = PURPLE WIRE
 * 
 * ENA = GRAY WIRE
 * ENB = GREEN WIRE
 */


#define ENA 9
#define IN1 2
#define IN2 8

#define IN3 4
#define IN4 7
#define ENB 3

char speakerOn[] = "option01";
char speakerOff[] = "option02";

USB Usb;
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
PS4BT PS4(&Btd, PAIR);

L298N motorR(ENA, IN1, IN2);
L298N motorL(ENB, IN3, IN4);


uint8_t carTrigger = 99;

int setSpeed = 255;
  
void setup() { 
  Serial.begin(9600);
  #if !defined(__MIPSEL__)
  while (!Serial); 
  #endif
  if (Usb.Init() == -1) {
    while (1); 
    }
    
  motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
  motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
}

void loop() {
  if (Serial.available())
  {
    int tofMeasure = Serial.parseInt();

    if (isdigit(tofMeasure))
    {
      // too close
      if (tofMeasure <= 100)
      {
        setSpeed = 75;
      }
      // close
      else if (tofMeasure <= 250)
      {
        setSpeed = 100;
      }
      // not close
      else
      {
        setSpeed = 255;
      }
      
    }
  }
  
  Usb.Task();
  if (PS4.connected()) {
    if (PS4.getButtonClick(PS)) { 
         PS4.disconnect(); 
    }
    else {
       // Move Car Backwards
       if(carTrigger == 0 ){
           motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorR.backward();
           motorL.backward();
       }  
       // Move Car Forwards
       else if(carTrigger == 1){
           motorR.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorL.setSpeed(setSpeed * .9); // an integer between 0 and 255
           motorR.forward();
           motorL.forward();
       }
       // Stop Car
       else if(carTrigger == 2){
        
           motorR.stop();
           motorL.stop();
       }
       // Move Car Forward Left
       else if(carTrigger == 3){
          motorL.setSpeed(setSpeed);
          motorL.forward();

          motorR.setSpeed(setSpeed * .5);
          motorR.forward();
       }
       //Move Car Forward Right
       else if(carTrigger == 4){
          motorL.setSpeed(setSpeed * .5);
          motorL.forward();

          motorR.setSpeed(setSpeed);
          motorR.forward();
       }

/*
 * CAR MOVEMENT BUTTONS
 */
      // Stops Car
      if (PS4.getButtonPress(L2)) {     
          carTrigger = 2;
      }

      // Moves the car forward
      if (PS4.getButtonPress(R2)) {
          carTrigger = 1;
      }

      // Moves the car backwards
      if (PS4.getButtonPress(R1)) {
         carTrigger = 0;
      }

      // Turns the car Forward Left
      if (PS4.getButtonPress(LEFT)){
         carTrigger = 3;
      }

      // Turns the car Forward Right
      if (PS4.getButtonPress(RIGHT)){
         carTrigger = 4;
      }

/*
 * END OF CAR MOVEMENT BUTTONS
 */


/*
 * SIGNALS TO OTHER ARDUINO BUTTONS
 */


  // Send Signal to turn ON the Speakers
  if (PS4.getButtonClick(SQUARE)){
      Serial.write(speakerOn, 8);
  }


  // Send Signal to turn OFF the Speakers
  if (PS4.getButtonClick(CIRCLE)){
      Serial.write(speakerOff, 8);
  }

  // Send Signal to CHANGE Music choice
  if (PS4.getButtonClick(TRIANGLE)){
    
  }

 // Send Signal to
  if (PS4.getButtonClick(CROSS)){
    
  }






/*
 * END OF SIGNALS TO OTHER ARDUINO BUTTONS
 */

    }
 }


}
