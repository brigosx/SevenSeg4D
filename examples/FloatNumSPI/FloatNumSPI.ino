//****************************************************************
//  Name    : FloatNumSPI
//  Author  : Bill Rigas
//  Date    : July 29 2019
//  Version : 1.0
//  Notes   : Counter displayed as floating number with the use
//          : of the SevenSeg4D library and Arduino SPI
//          : display screen through 2 HC595 shift registers
//****************************************************************


#include <SevenSeg4D.h>

const int latchPin = 10;

int counter = 0;
unsigned long last_out = 0;

// Output buffer for 4 digits plus the dot (.) character and the NULL terminated character
char buf[6];

// Initiates class with only one PIN (ST_CP or latch)
// and uses the SPI Arduino library. The other 2 PINs (clock and data)
// should be connected to the SPI pins of your board.
SevenSeg4D disp(latchPin, Anode);

void setup()
{
    // This will allow the DOT (.) pin of the 7Seg display to also be displayed
    // but requires different wirring (e.g. Q7 of the 1st shift register controls the DOT pin
    // D1 of 7-segment display should be connected to Q0 of 2nd shift register etc).
    disp.setAllowFloat(true);

    // Do not use sprintf for floating numbers.
    dtostrf(counter * 0.001f, 4, 3, buf);
}

void loop()
{
  // Display the message to the 7-segment LED display
  disp.shiftOutMsg(buf);

  unsigned long tms = millis();

  // Refresh counter and output buffer every 500 milliseconds
  if ((tms - last_out) > 500)
  {
      last_out = tms;
      
      if ((++counter) > 9999)
      {
          counter = 0;
      }

      // Do not use sprintf for floating numbers.
      dtostrf(counter * 0.001f, 4, 3, buf);
  }
}
