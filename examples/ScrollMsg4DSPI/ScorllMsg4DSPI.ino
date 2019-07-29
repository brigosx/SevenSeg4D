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

#define latchPin 10

const char *buf = "   Hello World!!!";
unsigned long last_out = 0;
ScrollDirection sdir = Left2Right;

 // SPI contstructor
SevenSeg4D disp(latchPin, Anode);

void setup()
{    
}

void loop()
{
    disp.scrollMsg(buf, sdir, 250);

    unsigned long tms = millis();

    // Change direction every 5 sec
    if ((tms - last_out) > 5000)
    {
        last_out = tms;
        sdir = (sdir == Left2Right) ? Right2Left : Left2Right;
    }
}