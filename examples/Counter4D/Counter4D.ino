//****************************************************************
//  Name    : Counter4D
//  Author  : Bill Rigas
//  Date    : July 15 2019
//  Version : 1.0
//  Notes   : 4 digits counter up display example with the use
//          : of the SevenSeg4D library
//          : display screen through 2 HC595 shift registers
//****************************************************************

#include <SevenSeg4D.h>

const int latchPin = 2;
const int dataPin = 3;
const int clockPin = 4;

int counter = 0;
unsigned long last_out = 0;
char* buf;

// Initiate class with 3 PINs and for COMMON Anode wiring.
// You may change the PIN numbers and the COMMON wiring according to your circuit (e.g. Cathode)
SevenSeg4D disp(dataPin, clockPin, latchPin, Anode);

// Prepare output buffer for 4 digits plus the NULL terminated character
void setup() {
  buf = new char[5];
  sprintf(buf, "%04d", counter);
}

void loop() {
  // Display the message to the 7-segment LED display
  disp.shiftOutMsg(buf);

  unsigned long tms = millis();

  // Refresh counter and output buffer every 500 milliseconds
  if ((tms - last_out) > 500) {
    last_out = tms;
    
    if ((++counter) > 9999) {
     counter = 0;
    }

    sprintf(buf, "%04d", counter);
  }
}
