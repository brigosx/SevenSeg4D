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

#define latchPin 2
#define dataPin 3
#define clockPin 4

int counter = 0;
unsigned long last_out = 0;
char* buf;

SevenSeg4D disp(dataPin, clockPin, latchPin, Anode);

//D1 = 128, D2 = 256, D3 = 512, D4 = 1024
void setup() {
  buf = new char[5];
  sprintf(buf, "%04d", counter);
}

void loop() {
  disp.shiftOutMsg(buf);

  unsigned long tms = millis();

  if ((tms - last_out) > 500) {
    last_out = tms;
    
    if ((++counter) > 9999) {
     counter = 0;
    }

    sprintf(buf, "%04d", counter);
  }
}
