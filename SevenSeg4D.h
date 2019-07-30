//****************************************************************
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

#ifndef SevenSeg4D_h
#define SevenSeg4D_h

#include <Arduino.h>
#include <SPI.h>

const unsigned char sevensegset[][2] = {
    {' ', 0x00}, {'!', 0x86}, {'"', 0x22}, {'#', 0x7E}, {'$', 0x2D}, {'%', 0xD2}, {'&', 0x7B}, {'(', 0x39}, {')', 0x0F},
    {'*', 0x63}, {'-', 0x40}, {':', 0x09}, {'/', 0x52}, {'<', 0x58}, {'>', 0x4C}, {'=', 0x48}, {'?', 0xD3}, {'@', 0x5F},
    {'0', 0x3F}, {'1', 0x06}, {'2', 0x5B}, {'3', 0x4F}, {'4', 0x66}, {'5', 0x6D}, {'6', 0x7D}, {'7', 0x07}, {'8', 0x7F}, 
    {'9', 0x6F}, {'A', 0x77}, {'B', 0x7C}, {'C', 0x39}, {'D', 0x5E}, {'E', 0x79}, {'F', 0x71}, {'G', 0x3D}, {'H', 0x76}, 
    {'I', 0x30}, {'J', 0x1E}, {'K', 0x75}, {'L', 0x38}, {'M', 0x37}, {'N', 0x54}, {'O', 0x3F}, {'P', 0x73}, {'Q', 0x67}, 
    {'R', 0x50}, {'S', 0x6D}, {'T', 0x78}, {'U', 0x3E}, {'V', 0x1C}, {'W', 0x2A}, {'X', 0x76}, {'Y', 0x6E}, {'Z', 0x5B}, 
    {'a', 0x77}, {'b', 0x7C}, {'c', 0x58}, {'d', 0x5E}, {'e', 0x79}, {'f', 0x71}, {'g', 0x3D}, {'h', 0x74}, {'i', 0x10}, 
    {'j', 0x1E}, {'k', 0x75}, {'l', 0x38}, {'m', 0x37}, {'n', 0x54}, {'o', 0x5C}, {'p', 0x73}, {'q', 0x67}, {'r', 0x50}, 
    {'s', 0x6D}, {'t', 0x78}, {'u', 0x3E}, {'v', 0x1C}, {'w', 0x2A}, {'x', 0x76}, {'y', 0x6E}, {'z', 0x5B}, {'.', 0x80}
};

enum CommonLedConnection { Anode = 0, Cathode };
enum ScrollDirection { Right2Left = 0, Left2Right };

class SevenSeg4D 
{
    private:
        int _dataPin, _clockPin, _latchPin;
        CommonLedConnection _connection;
        bool _spi_logic, _allow_float;

        void init(int dataPin, int clockPin, int latchPin, CommonLedConnection connection);
        void initSPI(int latchPin, CommonLedConnection connection);
        
        byte getSevenSegChar(unsigned char c);
        void softDelay(long delayTime);
        
    public:
        SevenSeg4D();
        SevenSeg4D(int dataPin, int clockPin, int latchPin);
        SevenSeg4D(int dataPin, int clockPin, int latchPin, CommonLedConnection connection);
        
        // SPI constructors
        SevenSeg4D(int latchPin);
        SevenSeg4D(int latchPin, CommonLedConnection connection);

        void shiftOutMsg(char *msg);
        void shiftOutChar(unsigned char c, byte digitpos);

        void scrollMsg(char *msg, ScrollDirection direction, long delayTime);
        void setAllowFloat(bool value);
};

#endif