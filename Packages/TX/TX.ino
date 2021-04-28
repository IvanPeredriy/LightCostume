#include <SoftEasyTransfer.h>

#include <SoftwareSerial.h>
#include "massiv.h"


//create object
SoftEasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  uint8_t addr[8];
  uint8_t data[8];
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;


SoftwareSerial radio(5, 10); // RX, TX

unsigned int counter = 0;
void setup() {
    Serial.begin(115200); 
    radio.begin(9600);
    pinMode(13, OUTPUT);
    
    ET.begin(details(mydata), &radio);
}

void loop() {

  /*Serial.println("___________");
  for(unsigned int i = 0; i<8; i++)
  {
  Serial.println(mass[counter][i][0]);
  Serial.println(mass[counter][i][1]);
  }
  Serial.println("___________");*/
  counter++;
  delay(200);
  Serial.println("___________");
  Serial.print("counter = ");
  Serial.println(counter);
  for(int i = 0; i<8; i++)
  {
    
    Serial.print("i = ");
    Serial.println(i);
    Serial.println(pgm_read_byte(&mass[counter][i][0]));
    Serial.println(pgm_read_byte(&mass[counter][i][1]));
    mydata.addr[i] = pgm_read_byte(&mass[counter][i][0]);
    mydata.data[i] = pgm_read_byte(&mass[counter][i][1]);
  }
  Serial.println("___________");

  ET.sendData();


}
