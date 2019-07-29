//****************************************************************
//  Name    : FloatNum4DSPI
//  Author  : Bill Rigas
//  Date    : July 29 2019
//  Version : 1.0
//  Notes   : Counter displayed as floating number with the use
//          : of the SevenSeg4D library and Arduino SPI

//          : display screen through 2 HC595 shift registers
//****************************************************************


#include <SevenSeg4D.h>

#define latchPin 10

int counter = 0;
unsigned long last_out = 0;
char *buf;

 // SPI contstructor
SevenSeg4D disp(latchPin, Anode);

void setup()
{
    // This will allow the DOT (.) pin of the 7Seg display to also be displayed
    // but requires different wirring.
    disp.setAllowFloat(true);

    buf = new char[5];
    dtostrf(counter * 0.001f, 4, 3, buf);
}

void loop()
{
    disp.shiftOutMsg(buf);

    unsigned long tms = millis();

    if ((tms - last_out) > 500)
    {
        last_out = tms;
        
        if ((++counter) > 9999)
        {
            counter = 0;
        }

        dtostrf(counter * 0.001f, 4, 3, buf);
    }
}
