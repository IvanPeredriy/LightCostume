#pragma once

/* Lib for HC-12 and costume module. 
A module is activated by creating an instance of the HC-12 class.			(TODO: HC-12 or costume? Decide!!!)
In constructor you can choose method - RX, TX or both. 
If TX - you should connect only RXD pin on HC-12 to your TX Arduino pin.
If RX - TXD pin on HC-12 -> RX Arduino pin.
By default HC-12 istance creates an another instance of the <SoftwareSerial> class.
Also you can connect /SET pin to some of your Arduino pin. It'll let you to choose mods of HC-12.

NOTE: Lib wes written for Arduino Nano V3. It may not work on another Arduino devices.

The methods are:

RX:
Costume - class for manipulating costume;

RX() - receive data if you work in RX-mode;
XOR(byte) - compare name_byte of your device and each byte of transition. If byte == name_byte, method returns 0;

TX(byte) - send data if you work in TX-mode;

lightOn(pin) - HIGH level on pin;
lightOff(pin) - LOW level on pin;

blinkOn(pin, delay) - Fast changing from HIGH to LOW on pin with delay;
blinkOff(pin) - deactivate blink;

SlowRise(pin, delay) - Slow rising of voltage in PIN with delay. NOTE: works only if your Arduino pin is: 3, 5, 6, 9, 10, 11

TODO: SlowFall(pin, delay) - Similar to SlowRise, but fall 
*/

#include <Arduino.h>
#include <SoftwareSerial.h>


class Costume
{
public:
	Costume(char RXpin, char TXpin, char SETpin, char nameOfModule);
	Costume(char RXpin, char TXpin, char nameOfModule);
	Costume(SoftwareSerial *ss, long baudrate, char RXpin, char nameOfModule);
	Costume(SoftwareSerial *ss, long baudrate, char TXpin);
	char RX();								// Receive data from UART
	char XOR(char byte);					// Compare received byte and name of module. If they equals, it returns 0;
	void TX(char send_byte);					// Send data byte
	void lightOn(char pin);					// HIGH on pin
	void lightOff(char pin);					// LOW on pin
	void blinkOn(char pin, char delay);	// Fast changing from HIGH to LOW on pin with delay
	void blinkOff(char pin); 				// Similar to lightOff
	void SlowRise(char pin, char delay);	// Slow rising on voltage in PIN with DELAY
private:
	char val_received;
  Stream *mySerial;
  SoftwareSerial *swSerial;
};
