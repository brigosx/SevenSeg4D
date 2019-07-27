# SevenSeg4D
Arduino 7segment 4 digits display Library

<h3>Overview</h3>
<p>This library is based on a great tutorial I found in YouTube made by <a href="https://www.youtube.com/channel/UC9NeBnf-9pzDC3C86MeOJvA">Kristian Blåsol</a> regardiing driving a 4 digit 7segment LED display screen with 2 <b>HC595</b> shift registers.</p>

<p>I 've tried many Arduino libraries regarding seven segment display and none of them seem to work, or was to complicated for me to play with more than 1 shift registers (HC595) and 1 7segment LED display with 4 digits.</p>

<p>The <a href="http://duinos.net/files/2015/four_digit_595_1234.ino">code and logic</a> of <b>Kristian Blåsol</b> was very simple and understandable so the SevenSeg4D class was borned in order to make the things a bit simpler.</p>

<p>The class offers 3 public methods:

<code>void shiftOutMsg(char *msg);</code><br>
<code>void shiftOutChar(unsigned char c, byte digitpos);</code></p>
<code>void scrollMsg(char *msg, ScrollDirection direction, long delayTime);</code>

<p>The first one takes a null terminated buffer of characters and displays them on the 4 digits LED screen and the second one can display only one character at the digit position of our choise. Although the library has not been tested with more than 2 shift registers and a 4 digit 7 segment LED screen it could work with no problems, as long as you respect the wiring as per the video below:</p>

https://www.youtube.com/watch?v=ZGzbAd-Aixc&list=LLwUpbzkpNqzFDXJVHNlYP9w

<p>The last one may scroll a message from <b>Left2Right</b> or <b>Right2Left</b> and at the given delay in milliseconds. An example was made at the video below:</p>

https://www.youtube.com/watch?v=3K__viiOc5Q&feature=youtu.be

<p>To initiate the class just apply the 3 Arduino pins (data, clock and latch pin) at which you connect your circuit and if you use common cathode or common anode for your 7 segment screen, like the example below:</p>
<code>SevenSeg4D disp(dataPin, clockPin, latchPin, Cathode);</code>
<br><p>or using the <b>SPI</b> contstructror:</p>
<code>SevenSeg4D disp(latchPin, Cathode);</code>
<br><p>where you define only the latch PIN. The data and clock PINs are defined automatically as per the <a href="https://www.arduino.cc/en/Reference/SPI">SPI Arduino reference</a></p>

<p>The default constructor uses dataPin = 3, clockPin = 4, latchPin = 2 and an Anode common connection to the 7segment LED display.</p>

<p>In the examples you can find the <a href="https://youtu.be/4xm0x6XxDis" title="Counter4D project on YouTube">Counter4D sketch</a> which use the SevenSeg4D library and has been tested successfully on an <b>Arduino Uno</b> board. But other boards (like Arduino Mega, Nano or NodeMCU) can be used either.</p>

<p>Currently the library supports English letters from A-Z, a-z, all numbers 0-9 and a few symbols like <b>(,),+,/</b> etc. However, more symbols can be added at the <code>sevensegset</code> array which is defined in the corresponding header file.</p>
