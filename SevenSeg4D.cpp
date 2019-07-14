#include "Arduino.h"
#include "SevenSeg4D.h"

SevenSeg4D::SevenSeg4D(int dataPin, int clockPin, int latchPin) {
    init(dataPin, clockPin, latchPin, Anode);
}

SevenSeg4D::SevenSeg4D(int dataPin, int clockPin, int latchPin, CommonLedConnection connection) {
    init(dataPin, clockPin, latchPin, connection);
}

void SevenSeg4D::init(int dataPin, int clockPin, int latchPin, CommonLedConnection connection) {
    _dataPin = dataPin;
    _clockPin = clockPin;
    _latchPin = latchPin;
    _connection = connection;

    pinMode(_dataPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_latchPin, OUTPUT);
}

void SevenSeg4D::shiftOutMsg(char *msg) {
    // The message length: IMPORTANT ! The message wil be displayed according the number of shift registers and display digits
    int len = strlen(msg);

    for (int i = 0; i < len; i++)
    {
        shiftOutChar(*msg++, i + 1);
        delay(1);
    }
}

void SevenSeg4D::shiftOutChar(unsigned char c, byte digitpos) {
    byte sevseg = getSevenSegChar(c);

    unsigned long value = 0;
    // 1st register MSB = D1, 2nd register LSB = D2 etc
    bitSet(value, 6 + digitpos);

    digitalWrite(_latchPin, LOW);

    // Clear shift registers
    shiftOut(_dataPin, _clockPin, MSBFIRST, (value + 64) >> 8);
    // Pass data to shift registers
    shiftOut(_dataPin, _clockPin, MSBFIRST, value + sevseg);

    digitalWrite(_latchPin, HIGH);
}

byte SevenSeg4D::getSevenSegChar(unsigned char c) {
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