#include <SoftwareSerial.h>
#include "massiv.h"

SoftwareSerial radio(5, 10); // RX, TX

unsigned int counter = 0;
void setup() {
    Serial.begin(115200); 
    radio.begin(9600);
    pinMode(13, OUTPUT);
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

  }
  Serial.println("___________");
  
  radio.print('1');
  delay(100);
  radio.print('2');
  delay(100);
  radio.print('3');
  delay(100);
  radio.print('4');
  delay(100);
  radio.print('5');
  delay(100);
  radio.print('6');
  delay(100);
  radio.print('7');
  delay(100);
  radio.print('8');
  delay(100);


}
