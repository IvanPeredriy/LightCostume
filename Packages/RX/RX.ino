/* Принимаю массив из 8 байт. 
 * Номер костюма(#define device) вычисляется так: N-1, где N - номер костюма.
 * Соответственно и работать нужно с элементом массива, который записан в device.
 * 
 * 1 - вкл, 0 - выкл.
 * 
 * 1ххх хххх - Вкл\выкл голову + тело;
 * х1хх хххх - вкл\выкл руки;
 * хх1х хххх - вкл\выкл ноги;
 * 
 * ххх1 хххх - вкл\выкл мерцание у головы + тела;
 * хххх 1ххх - вкл\выкл мерцание у рук;
 * хххх х1хх - вкл\выкл мерцание у ног.
 * 
 * Младшие два бита - резерв.
 * 
 * Управляющие выводы должны находится на пинах с шимом - резерв для медленного зажигания\гашения
 */

//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>


#include <SoftEasyTransfer.h>

#include <SoftwareSerial.h>

#define device 1

#define BLINK_DELAY 50

#define headNbody 3
#define Arms 5
#define Legs 9

//LiquidCrystal_I2C lcd(0x3F,16,2);


SoftwareSerial radio(A5, A4); // RX, TX
//SoftwareSerial radio(A2, A3);
uint8_t val;
//int counter = 0;


long timer = 0, time_last = 0;

SoftEasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  //uint8_t addr[8];
  uint8_t data[8];
};

RECEIVE_DATA_STRUCTURE mydata;

void setup() {
   //Serial.begin(115200);
    radio.begin(9600);
    radio.listen();
/*
      pinMode(A3, OUTPUT);
  digitalWrite(A3, LOW);

  delay(100);
  radio.write("AT+C100");    // Set 473 MHz
  delay(100);
  radio.write("AT+B1200");   // Set baudRate 1200
  delay(100);
  radio.begin(1200);      
  delay(100);
  radio.write("AT+P8");       // Set max power output
  delay(100);

  digitalWrite(A3, HIGH);
    */

      //lcd.init();
      // Print a message to the LCD.
      //lcd.backlight();
    
    ET.begin(details(mydata), &radio);
}

void loop() {
    if(radio.available())
    {
      
      ET.receiveData();
  
      // Проверка головы + тела
      if(bitRead(mydata.data[device], 7))
      {
        digitalWrite(headNbody, HIGH);
        //digitalWrite(13, HIGH);
        //counter++;
      }
      else
      {
        digitalWrite(headNbody, LOW);
        //digitalWrite(13, LOW);
      }

      // Проверка рук
      if(bitRead(mydata.data[device], 6))
      {
        digitalWrite(Arms, HIGH);
        //digitalWrite(13, HIGH);
      }
      else
      {
        digitalWrite(Arms, LOW);
        //digitalWrite(13, LOW);
      }

      // Проверка ног
      if(bitRead(mydata.data[device], 5))
      {
        digitalWrite(Legs, HIGH);
        //digitalWrite(13, HIGH);
      }
      else
      {
        digitalWrite(Legs, LOW);
        //digitalWrite(13, LOW);
      }


      // Мерцание головы + тела

      if(bitRead(mydata.data[device],4))
      {
        digitalWrite(headNbody, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(headNbody, LOW);
        delay(BLINK_DELAY);
      }

      // Мерцание рук
      if(bitRead(mydata.data[device], 3))
      {
        digitalWrite(Arms, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(Arms, LOW);
        delay(BLINK_DELAY);
      }

      // Мерцание ног
      if(bitRead(mydata.data[device], 2))
      {
        digitalWrite(Legs, HIGH);
        delay(BLINK_DELAY);
        digitalWrite(Legs, LOW);
        delay(BLINK_DELAY);
      }


      /*lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(counter);
      lcd.setCursor(1, 1);
      lcd.print(timer-000);*/
      //delay(100);
     /* Serial.println("_________");
      Serial.print("Period is: ");
      Serial.print(timer);
      Serial.println(" ms");
      for(int i = 0; i<8; i++)
      {
        Serial.print("Data: ");
        Serial.println(mydata.data[i]);
      }
      Serial.println("_________");
       
         timer = (millis() - time_last);
         time_last = millis();*/
      
    }

}
