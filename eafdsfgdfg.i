#include <SPI.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

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
//SoftwareSerial radio(5, 10); // RX, TX

byte result;

unsigned short int tmp1;       // Used for reading WRAM
unsigned long counter = 0;
bool zero = false, one = false, two = false, three = false,four = false, five = false, six = false, seven = false, eight = false, nine = false;
int check;
int currPosS, currPosM;
bool stopped=0;

char IDs[8] = {0x07, 0x14, 0x28, 0x4F, 0x9E, 0xAE, 0xBA, 0xFF};
char send_data[8] = {1,2,3,4,5,6,7,8};
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(115200);
  //radio.begin(9600);
  result = sd.begin(SD_SEL, SPI_HALF_SPEED);
  result = MP3player.begin();


  digitalWrite(pinStart, HIGH);
  digitalWrite(pinStop,  HIGH);
  digitalWrite(pinLeft,  HIGH);
  digitalWrite(pinRight, HIGH);

  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Hello!");
  lcd.clear();
  lcd.setCursor(0,0);
  
}
/* CurrentPosition - Current position in Ms (actually just in S)
 * pauseMusic() - pause in some place
 * resumeMusic() - Resume music from where it was paused
 */
void loop() {
  if(digitalRead(pinStart) == 0)
  {
    char trackName[] = "try.ogg";
    result = MP3player.playMP3(trackName);
  }
  if(digitalRead(pinStop) == 0)
  { 
    if(MP3player.isPlaying() == 1)
      {
        MP3player.pauseDataStream();
      }
      else
      {
      MP3player.resumeDataStream();
      }
      Serial.println(MP3player.isPlaying());

  }
  if(digitalRead(pinRight) == 0)
  {
    MP3player.skipTo((currPosS + 1) * 1000);
  }
  if(digitalRead(pinLeft) == 0)
  {
    MP3player.skipTo((currPosS - 1) * 1000);
  }
  if(MP3player.isPlaying() == 1)
  {
    currPosS = MP3player.currentPosition()/1000;
    lcd.setCursor(0,0);
   lcd.print(currPosS);
  }
  
}
