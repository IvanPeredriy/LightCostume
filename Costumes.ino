#include <SoftEasyTransfer.h>
#include <SPI.h>
#include <SoftwareSerial.h>
//#include <LiquidCrystal_I2C.h>

#include "massiv.h"

#define pinStart A0
#define pinStop A1
#define pinLeft A2
#define pinRight A3

//Add the SdFat Libraries
#include <SdFat.h>
#include <SdFatUtil.h> 

//and the MP3 Shield Library
#include <SFEMP3Shield.h>

//create and name the library object
SFEMP3Shield MP3player;
SdFat sd;
SdFile file;
SoftwareSerial radio(5, 10); // RX, TX

//create object
SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  //uint8_t addr[8];
  uint8_t data[8];
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

byte result;

unsigned short int tmp1;       // Used for reading WRAM
unsigned long counter = 0;
bool zero = false, one = false, two = false, three = false,four = false, five = false, six = false, seven = false, eight = false, nine = false;
int check;
bool stopped=0;

void setup() {
  //Serial.begin(115200);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  
  radio.begin(9600);
  result = sd.begin(SD_SEL, SPI_HALF_SPEED);
  result = MP3player.begin();
/*
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  delay(100);
  radio.write("AT+C100");    // Set 473 MHz
  delay(100);
  radio.write("AT+B1200");   // Set baudRate 1200
  delay(100);
  radio.begin(1200);   
  delay(100);
  radio.write("AT+P8");       // Set max power output
  delay(100);

  digitalWrite(3, HIGH);
*/
  ET.begin(details(mydata), &radio);
  
}

void loop() {

  
  if(MP3player.isPlaying() == 1)
   {
    
    MP3player.Mp3WriteRegister(SCI_WRAMADDR, 0x1e27);
    tmp1 = MP3player.Mp3ReadRegister(SCI_WRAM);
    check = (tmp1%1000)/100;

  
    if((check == 0) && (zero == false))
    {
      counter++;
      nine = false;
      zero = true;
      //Serial.println("I'm in zero!!! \n\n\n");
      //send_data();
    }
    else if((check == 1) && (one == false))
    {
      //counter++;
      zero = false;
      one = true;
      //send_data();
      //Serial.println("I'm in one!!! \n\n\n");
    }
    else if((check == 2) && (two == false))
    {
      counter++;
      one = false;
      two = true;
      //Serial.println("I'm in two!!! \n\n\n");
      //send_data();

    }
    else if((check == 3) && (three == false))
    {
      //counter++;
      two = false;
      three = true;
      //send_data();
      //Serial.println("I'm in three!!! \n\n\n");
    }
    else if((check == 4) && (four == false))
    {
      counter++;
      three = false;
      four = true;
      //send_data();
           // Serial.println("I'm in four!!! \n\n\n");

    }
    else if((check == 5) && (five == false))
    {
      //counter++;
      four = false;
      five = true;
      //send_data();
           // Serial.println("I'm in five!!! \n\n\n");

    }
    else if((check == 6) && (six == false))
    {
      counter++;
      five = false;
      six = true;
      //send_data();
           // Serial.println("I'm in six!!! \n\n\n");

    }
    else if((check == 7) && (seven == false))
    {
      //counter++;
      six = false;
      seven = true;
      //send_data();
            //Serial.println("I'm in seven!!! \n\n\n");

    }
    else if((check == 8) && (eight == false))
    {
      counter++;
      seven = false;
      eight = true;
      //send_data();
           // Serial.println("I'm in eight!!! \n\n\n");

    }
    else if((check == 9) && (nine == false))
    {
      eight = false;
      nine = true;
      //send_data();
            //Serial.println("I'm in nine!!! \n\n\n");
    }


    if(zero == true && check != 0)
    {
      zero = false;
    }
    if(one == true && check != 1)
    {
      one = false;
    }
    if(two == true && check != 2)
    {
      two = false;
    }
    if(three == true && check != 3)
    {
      three = false;
    }
    if(four == true && check != 4)
    {
      four = false;
    }
    if(five == true && check != 5)
    {
      five = false;
    }
    if(six == true && check != 6)
    {
      six = false;
    }
    if(seven == true && check != 7)
    {
      seven = false;
    }
    if(eight == true && check != 8)
    {
      eight = false;
    }
    if(nine == true && check != 9)
    {
      nine = false;
    }  

    for(int i = 0; i<8; i++)
    {
        //mydata.addr[i] = pgm_read_byte(&mass[counter][i][0]); 
        //mydata.data[i] = 0b11100000;
        mydata.data[i] = pgm_read_byte(&mass[counter][i][1]);
    }
    ET.sendData();

    //delay(500);
   }
    else
   {
      counter = 0;
      //char trackName[] = "try.ogg";
      char trackName[] = "Light.ogg";
      result = MP3player.playMP3(trackName);
      MP3player.setVolume(0x00, 0x00);
   }


}
