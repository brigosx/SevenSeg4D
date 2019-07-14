# SevenSeg4D
Arduino 7 Segment Library

<h3>Overview</h3>
<pThis library is based on a the great tutorial below which I found in YouTube by Kristian Blåsol. I 've tried many Arduino libraries regarding seven segment display and none of them seem to work or was to complicated to play with more than 1 shift registers (HC595) and 1 7segment LED display with 4 digits.</p>

<p>The code and logic of Kristian was very simple and understandable so the SevenSeg4D class was borned in order to make the things a bit simpler.</p>

<p>The class offers 2 public methods:

<code>void shiftOutMsg(char *msg);</code><br>
<code>void shiftOutChar(unsigned char c, byte digitpos);</code></p>

<p>The first one can take a null terminated buffer of characters and displays them on the 4 digits LED screen and the second one can display only one at the digit position of our choise. Although the library has not been tested with more than 2 shift registers and a 4 digit 7 segment LED screen it could work with no problems, as long as you respect the wiring as per the video below:</p>

https://www.youtube.com/watch?v=ZGzbAd-Aixc&list=LLwUpbzkpNqzFDXJVHNlYP9w

<p>To initiate the class just apply the 3 Arduino pins (data, clock and latch pin) at which you connect your circuit and if you use common cathode or common anode for your 7 segment screen, like the example below:</p>

<code>SevenSeg4D disp(dataPin, clockPin, latchPin, Cathode);</code>
