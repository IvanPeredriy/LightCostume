/* All description in Costumes.h */
/* 27.11.2019. Khai. Ivan Peredriy */

#include "Costume.h"
#include <Arduino.h>
#include <SoftwareSerial.h>


Costume::Costume(SoftwareSerial *ss, long baudrate, char RXpin, char nameOfModule)
{
	
	swSerial = ss;			// instance of SoftwareSerial
	//Costume.begin(9600);
  swSerial->begin(9600);
};
/*
Costume::Costume(SoftwareSerial *ss, long baudrate, char TXpin)
{
	
	swSerial Costume((TXpin-1), TXpin);
	//Costume.begin(9600);
  swSerial->begin(9600);
}*/
/*
char Costume::RX()
{
	//val_received = Costume.read();

}

void Costume::TX(char send_byte)
{
	//Costume.print(send_byte);
}*/
