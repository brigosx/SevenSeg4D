//****************************************************************
//  Name    : CounterSPI
//  Author  : Bill Rigas
//  Date    : July 22 2019
//  Version : 1.0
//  Notes   : 4 digits counter up display example with the use
//          : of the SevenSeg4D library and Arduino SPI
//          : display screen through 2 HC595 shift registers
//***************************************************************

#include <SevenSeg4D.h>

const int latchPin = 10;

int counter = 0;
unsigned long last_out = 0;

// Output buffer for 4 digits plus the NULL terminated character
char buf[5];

// Initiates class with only one PIN (ST_CP or latch)
// and uses the SPI Arduino library. The other 2 PINs (clock and data)
// should be connected to the SPI pins of your board.
SevenSeg4D disp(latchPin, Anode);

void setup() {
  // Prepare output buffer
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
