//DIGITAL EUTHANASIA WEARABLE PIECE
//DEATH SWITCH (wearable system for checking if the user is dead or alive)
//Creted by fito_segrera
//April / 2014
//
//When the system detects an abscenc of heart beats it activates an asks for a combination.
//If the combination is correct then it unlocks and nothing happens, otherwise if it is
//incorrect it blocks itself, deactivates and assumes the the user is dead. If this is correct
//it sends an email commiting digital euthanasia...

//////////////////////////////
//COMBINATION KEY = 10, 2, 6//
//////////////////////////////

int pass1 = 10;
int pass2 = 2;
int pass3 = 6;

boolean deathSwitch = false;
boolean comb1 = false;
boolean comb2 = false;
boolean comb3 = false;
boolean error1 = false;
boolean error2 = false;
boolean error3 = false;
int combCount = 0;

int errorCount = 0;
int wait = 1000;
int resetCount = 0;
int resetCountVal = 5;
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC

//Pin definitions RGB LED toggle swith of the encoder
int redPin = 5;  // Encoder's red LED - D5 is PWM enabled
int bluPin = 6;  // Encoder's blue LED- D6 is PWM enabled
int grnPin = 9;  // Encoder's green LED - D9 is PWM enabled
int swhPin = 7;  // Encoder's switch pin

// Pin definitions - Shift registers:
int enPin = 13;  // Shift registers' Output Enable pin
int latchPin = 12;  // Shift registers' rclk pin
int clkPin = 11;  // Shift registers' srclk pin
int clrPin = 10;  // shift registers' srclr pin
int datPin = 8;  // shift registers' SER pin

int rotationSpeed = 5;  // MIN: 0, MAX: 5, 3 is a good value
int encoderPosition;

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

void setup()
{
  /* Setup encoder pins as inputs */
  pinMode(ENC_A, INPUT);
  digitalWrite(ENC_A, HIGH);
  pinMode(ENC_B, INPUT);
  digitalWrite(ENC_B, HIGH);
  Serial.begin (9600);
  Serial.println("Start");

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

  // setup switch pins, set as an input, no pulled up
  pinMode(swhPin, INPUT);
  digitalWrite(swhPin, LOW);  // Disable internal pull-up

  // Setup led pins as outputs, and write their intial value.
  // initial value is defined by the ledValue global variable
  pinMode(redPin, OUTPUT);
  digitalWrite(redPin, LOW);  // Red off
  pinMode(grnPin, OUTPUT);
  digitalWrite(grnPin, LOW);  // Green off
  pinMode(bluPin, OUTPUT);
  digitalWrite(bluPin, LOW);  // Blue off

  // Setup shift register pins
  pinMode(enPin, OUTPUT);  // Enable, active low, this'll always be LOW
  digitalWrite(enPin, LOW);  // Turn all outputs on
  pinMode(latchPin, OUTPUT);  // this must be set before calling shiftOut16()
  digitalWrite(latchPin, LOW);  // start latch low
  pinMode(clkPin, OUTPUT);  // we'll control this in shiftOut16()
  digitalWrite(clkPin, LOW);  // start sck low
  pinMode(clrPin, OUTPUT);  // master clear, this'll always be HIGH
  digitalWrite(clrPin, HIGH);  // disable master clear
  pinMode(datPin, OUTPUT);  // we'll control this in shiftOut16()
  digitalWrite(datPin, LOW);  // start ser low

  // To begin, we'll turn all LEDs on the circular bar-graph OFF
  digitalWrite(latchPin, LOW);  // first send latch low
  shiftOut16(0x0000);
  digitalWrite(latchPin, HIGH);  //

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

}

void loop(){
  //----------------------------------------------------------------//
  if(deathSwitch == false){
    // IF THE BUTTON IS PRESSED
    if (digitalRead(swhPin) == HIGH){
      errorCount++;
      Serial.print("ERROR: ");
      Serial.println(errorCount);
      //check for FIRST number os the combination
      if (encoderPosition == pass1 && comb1 == false && comb2 == false && comb3 == false){
        digitalWrite(redPin, LOW);
        digitalWrite(grnPin, LOW);
        digitalWrite(bluPin, LOW);
        comb1 = true;
        combCount++;
      }
      else{
        digitalWrite(redPin, LOW);
        //digitalWrite(grnPin, LOW);
        //digitalWrite(bluPin, LOW);
      }
      //check for SECOND number os the combination
      if (encoderPosition == pass2 && comb1 == true && comb2 == false && comb3 == false){
        digitalWrite(redPin, LOW);
        digitalWrite(grnPin, LOW);
        digitalWrite(bluPin, LOW);
        comb2 = true;
        combCount++;
      }
      else{
        digitalWrite(redPin, LOW);
        //digitalWrite(grnPin, LOW);
        //digitalWrite(bluPin, LOW);
      }
      //check for THIRD number os the combination
      if (encoderPosition == pass3 && comb1 == true && comb2 == true && comb3 == false){
        digitalWrite(redPin, LOW);
        digitalWrite(grnPin, LOW);
        digitalWrite(bluPin, LOW);
        comb3 = true;
        combCount++;
      }
      else{
        digitalWrite(redPin, LOW);
        //digitalWrite(grnPin, LOW);
        //digitalWrite(bluPin, LOW);
      }

      //IF COMBINATION IS CORRECT
      if(combCount == 3 && comb1 ==true && comb2 ==true && comb3 == true){
        correctComb(20);
        correctSystemReset();

      }// IF COMBINATION IS INCORRECT
      else if(errorCount > 2){
        errorComb(20);
        errorSystemReset();
      }   
      //----------------------------------------------------------------//
      // IF THE BUTTON IS NOT PRESSED
      else if (digitalRead(swhPin) == LOW){
        digitalWrite(redPin, HIGH);
        digitalWrite(grnPin, HIGH);
        digitalWrite(bluPin, HIGH);  
      }
      //----------------------------------------------------------------//
      delay(wait);


      static uint8_t counter = 0;      //this variable will be changed by encoder input
      int8_t tmpdata;
      /**/
      tmpdata = read_encoder();
      if( tmpdata ) {
        //Serial.print("Counter value: ");
        //Serial.println(counter, DEC);
        counter += tmpdata;
        encoderPosition = map(counter, 0, 255, 0, 32);
      }//IF THE USER IS DEAD THE SYSTEM BLOCKS... AND ONLY UNBLOCKS IF THE BUTTON IS PRESSED FOR 5 SECS...
      else { 
        ledRingFillerDeath(500);
        if (digitalRead(swhPin) == HIGH){
          resetCount = millis()%resetCountVal;
          Serial.println(resetCount);
          if(resetCount >= 4){
            ledRingFillerDeath(10);
            deathSwitch = false;
          }
        }
      }

      ledRingFiller(rotationSpeed);  // Update the Bar graph LED
    }
  }
}


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void ledRingFiller(byte rotationSpeed){
  // ledShift stores the bit position of the upper-most LED
  // this value should be between 0 and 15 (shifting a 16-bit vaule)
  unsigned int ledShift = 0;
  // each bit of ledOutput represents a single LED on the ring
  // this should be a value between 0 and 0xFFFF (16 bits for 16 LEDs)
  unsigned int ledOutput = 0;

  // Only do this if encoderPosition = 0, if it is 0, we don't
  // want any LEDs lit up
  // First set ledShift equal to encoderPosition, but we need
  // to compensate for rotationSpeed.
  ledShift = encoderPosition & (0xFF >> (rotationSpeed-1));
  // ledBarFollower()

  ledOutput |= 1<<ledShift;

  Serial.print("ledShift: ");
  Serial.println(ledShift);

  // Now we just need to write to the shift registers. We have to
  // control latch manually, but shiftOut16 will take care of
  // everything else.
  digitalWrite(latchPin, LOW);  // first send latch low
  shiftOut16(ledOutput);  // send the ledOutput value to shiftOut16
  digitalWrite(latchPin, HIGH);  // send latch high to indicate data is done sending 
}

// void ledRingFollower(byte rotationSpeed) - This is one of two
// functions that can be used to update the led ring bar graph thing.
//   This will illuminate a single LED equivalent to the value
// of encoderPosition.
//   The input variable, rotationSpeed, should be some value between
// 1 and 5.
//   This function uses encoderPosition, updated by the readEncoder()
// interrupt handler, to decide what LEDs to illuminate.

void ledRingFollower(byte rotationSpeed){
  // ledShift stores the bit position of the upper-most LED
  // this value should be between 0 and 15 (shifting a 16-bit vaule)
  unsigned int ledShift = 0;
  // each bit of ledOutput represents a single LED on the ring
  // this should be a value between 0 and 0xFFFF (16 bits for 16 LEDs)
  unsigned int ledOutput = 0;

  // Only do this if encoderPosition = 0, if it is 0, we don't
  // want any LEDs lit up
  if (encoderPosition != 0){
    // First set ledShift equal to encoderPosition, but we need
    // to compensate for rotationSpeed.
    ledShift = encoderPosition & (0xFF >> (rotationSpeed-1));
    // Now divide ledShift by 16, also compensate for rotationSpeed

    ledOutput = 1 << ledShift;
  }

  // Now we just need to write to the shift registers. We have to
  // control latch manually, but shiftOut16 will take care of
  // everything else.
  digitalWrite(latchPin, LOW);  // first send latch low
  shiftOut16(ledOutput);  // send the ledOutput value to shiftOut16
  digitalWrite(latchPin, HIGH);  // send latch high to indicate data is done sending 

}

// This function'll call shiftOut (a pre-defined Arduino function)
// twice to shift 16 bits out. Latch is not controlled here, so you
// must do it before this function is called.
//   data is sent 8 bits at a time, MSB first.
void shiftOut16(uint16_t data){
  byte datamsb;
  byte datalsb;

  // Isolate the MSB and LSB
  datamsb = (data&0xFF00)>>8;  // mask out the MSB and shift it right 8 bits
  datalsb = data & 0xFF;  // Mask out the LSB

  // First shift out the MSB, MSB first.
  shiftOut(datPin, clkPin, MSBFIRST, datamsb);
  // Then shift out the LSB
  shiftOut(datPin, clkPin, MSBFIRST, datalsb);
}

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

  /* returns change in encoder state (-1,0,1) */
  int8_t read_encoder(){
    static int8_t enc_states[] = {
      0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0                                            };
    static uint8_t old_AB = 0;
    /**/
    old_AB <<= 2;                   //remember previous state
    old_AB |= ( ENC_PORT & 0x03 );  //add current state
    return ( enc_states[( old_AB & 0x0f )]);
  }

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

  void correctSystemReset(){
    //RESET THE SYSTEM 
    comb1 = false;
    comb2 = false;
    comb3 = false;
    combCount = 0;
    encoderPosition = 0;
    errorCount = 0;
    deathSwitch = true;
    digitalWrite(redPin, HIGH);
    digitalWrite(grnPin, HIGH);
    digitalWrite(bluPin, HIGH);
  }

  void errorSystemReset(){
    //RESET THE SYSTEM 
    comb1 = false;
    comb2 = false;
    comb3 = false;
    combCount = 0;
    encoderPosition = 0;
    errorCount = 0;
    deathSwitch = true;
    digitalWrite(redPin, HIGH);
    digitalWrite(grnPin, HIGH);
    digitalWrite(bluPin, HIGH);
  }

  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////

  //IF THE SYSTEM DETECTS DEATH THEN THE LED REACT:
  void ledRingFillerDeath(int blinkSpeed){
    //unsigned int ledShift = 0;
    unsigned int ledOutput = 0;
    //ledShift = encoderPosition & (0xFF >> (rotationSpeed-1));
    for(int i = 0; i <16; i++){
      ledOutput |= 1<<i;
    }
    if(deathSwitch == true){
      digitalWrite(latchPin, LOW);  // first send latch low
      shiftOut16(ledOutput);  // send the ledOutput value to shiftOut16
      digitalWrite(latchPin, HIGH);  // send latch high to indicate data is done sending 
      delay(blinkSpeed);
      digitalWrite(latchPin, LOW);  // first send latch low
      ledOutput = 0;
      shiftOut16(ledOutput);  // send the ledOutput value to shiftOut16
      digitalWrite(latchPin, HIGH);  // send latch high to indicate data is done sending 
      delay(blinkSpeed);
    }
  }

  void correctComb(int blinkSpeed){
    for(int i = 0; i < 50; i++){
      digitalWrite(redPin, LOW);
      digitalWrite(grnPin, LOW);
      digitalWrite(bluPin, LOW);
      delay(blinkSpeed);
      digitalWrite(redPin, HIGH);
      digitalWrite(grnPin, HIGH);
      digitalWrite(bluPin, HIGH);
      delay(blinkSpeed);

    } 
  }
  void errorComb(int blinkSpeed){
    digitalWrite(redPin, LOW);
    delay(blinkSpeed);
    digitalWrite(redPin, HIGH);
    digitalWrite(grnPin, HIGH);
    digitalWrite(bluPin, HIGH);
    delay(blinkSpeed);
}

















