//#include <SoftwareSerial.h>

#define device 0x38

#define headNbody 3
#define Arms 5
#define Legs 9



char val;

void setup() {
   Serial.begin(9600);
   Serial3.begin(9600);

}

void loop() {

  while(Serial3.available())
    {
    val = Serial3.read();

    if(val == 'f'){
      Serial.println("forw");
    }
    if(val == 'b'){
      Serial.println("backw");
    }
    if(val == 'l'){
      Serial.println("left");
    }
    if(val == 'r'){
      Serial.println("right");
    }
    }

}
