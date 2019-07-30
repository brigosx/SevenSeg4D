//**************************************************************//
//  Name    : ScrollMsg4DSPI
//  Author  : Bill Rigas
//  Date    : July 29 2019
//  Version : 1.0
//  Notes   : Scrolling text left-to-right and right-to-left by
//          : the use of the SevenSeg4D library and Arduino SPI

//          : display screen through 2 HC595 shift registers
//****************************************************************


#include <SevenSeg4D.h>

const int latchPin = 10;

// The message to be scrolled
const char *buf = "   Hello World!!!";
unsigned long last_out = 0;
// The initial scrolling direction
ScrollDirection sdir = Left2Right;

/ Initiates class with only one PIN (ST_CP or latch)
// and uses the SPI Arduino library. The other 2 PINs (clock and data)
// should be connected to the SPI pins of your board.
SevenSeg4D disp(latchPin, Anode);

// You may apply your initialization code in setup
void setup()
{    
}

void loop()
{
    // Scrolls the message with a delay of 250 milliseconds
    disp.scrollMsg(buf, sdir, 250);

    unsigned long tms = millis();

    // Changes direction every 5 sec
    if ((tms - last_out) > 5000)
    {
        last_out = tms;
        sdir = (sdir == Left2Right) ? Right2Left : Left2Right;
    }
}