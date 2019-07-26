//**************************************************************//
//  Name    : SevenSeg4D library
//  Author  : Bill Rigas
//  Date    : July 15 2019
//  Version : 1.0
//  Notes   : Free library for commercial or not use.
//          : It can display characters on a 4 digit 7segment LED
//	    : display screen through 2 HC595 shift registers
//****************************************************************

/*  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA  
*/

#include "Arduino.h"
#include "SevenSeg4D.h"
#include "SPI.h"

SevenSeg4D::SevenSeg4D() 
{
    init(3, 4, 2, Anode);
}

SevenSeg4D::SevenSeg4D(int dataPin, int clockPin, int latchPin) 
{
    init(dataPin, clockPin, latchPin, Anode);
}

SevenSeg4D::SevenSeg4D(int dataPin, int clockPin, int latchPin, CommonLedConnection connection) 
{
    init(dataPin, clockPin, latchPin, connection);
}

SevenSeg4D::SevenSeg4D(int latchPin) 
{
    initSPI(latchPin, Anode);
}

SevenSeg4D::SevenSeg4D(int latchPin, CommonLedConnection connection) 
{
 initSPI(latchPin, connection);
}

void SevenSeg4D::init(int dataPin, int clockPin, int latchPin, CommonLedConnection connection) 
{
    _spi_logic = false;
    
    _dataPin = dataPin;
    _clockPin = clockPin;
    _latchPin = latchPin;
    _connection = connection;

    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
}

void SevenSeg4D::initSPI(int latchPin, CommonLedConnection connection) 
{
    _spi_logic = true;

    _latchPin = latchPin;
    _connection = connection;
    
    pinMode(_latchPin, OUTPUT);
    
    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
}

void SevenSeg4D::shiftOutMsg(char *msg) 
{
    // The message length: IMPORTANT ! The message wil be displayed according the number of shift registers and display digits
    int len = strlen(msg);

    for (int i = 0; i < len; i++)
    {
        shiftOutChar(*msg++, i + 1);
    }
}

void SevenSeg4D::shiftOutChar(unsigned char c, byte digitpos) 
{
    byte sevseg = getSevenSegChar(c);

    unsigned long value = 0;
    // 1st register MSB = D1, 2nd register LSB = D2 etc
    bitSet(value, 6 + digitpos);

    digitalWrite(_latchPin, LOW);

    if (!_spi_logic) {
      // Clear shift registers
      shiftOut(_dataPin, _clockPin, MSBFIRST, (value + 64) >> 8);
      // Pass data to shift registers
      shiftOut(_dataPin, _clockPin, MSBFIRST, value + sevseg);
      
  }
  else {
      // Clear shift registers
      SPI.transfer((value + 64) >> 8);
      // Pass data to shift registers
      SPI.transfer(value + sevseg);
      
  }

    digitalWrite(_latchPin, HIGH);
    softDelay(1);
}

byte SevenSeg4D::getSevenSegChar(unsigned char c) 
{
    byte result = 0;

    // First get the 7segment binary code
    for (unsigned int i = 0; i < sizeof(sevensegset); i++)
    {
        if (c == sevensegset[i][0])
        {
            result = sevensegset[i][1];
            break;
        }
    }

    if (_connection == Cathode)
    {
        // Get the invertion of the code and clear the MSBit which will be used for light up digit 1
        result = (~result) ^ 0x80;
    }

    return result;
}

void SevenSeg4D::softDelay(long delayTime)
{
    unsigned long tms = millis() + delayTime;

    while (millis() < tms) 
    {
        yield();
    }
}