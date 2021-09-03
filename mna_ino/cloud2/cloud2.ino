#include <AltSoftSerial.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

/*
    mode 0: Auto - 조도센서에 따라 자동조절
    mode 1: Manual - hex값에 따라 색상 조절
    mode 2: On - 흰색 온                   //추가 기능
    mode 3 : Off - 끄기
*/

//SoftwareSerial bt(3, 2); // rxPin = 블루투스 tx Pin, txPin = rx Pin
AltSoftSerial bt;
SoftwareSerial MP3Module(4, 5);
DFRobotDFPlayerMini MP3Player;


int redPin = 3;
int greenPin = 10;
int bluePin = 11;

int location = 0;
String readString;
String input = "0";


void setup() {
  Serial.begin(9600);  //시리얼 초기화
  bt.begin(9600);       //소프트웨어 시리얼 통신  MP3Module.begin(9600);
  MP3Module.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  if (!MP3Player.begin(MP3Module)) { // MP3 모듈을 초기화합니다. 초기화에 실패하면 오류를 발생시킵니다.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  delay(1);
  MP3Player.volume(10);

}



void loop() {
  while (bt.available()) {
    delay(10);
    char c = bt.read();
    if (c == ',') {
      input = readString;
      Serial.print(input);
      readString = "";
      break;
    }
    readString += c;
  }

    if ( input == "1" ) {
      MP3Player.play(2);
//      Serial.print("1");
      setColor(255, 0, 0);
      delay(2500);
      setColor(0, 0, 0);
      delay(2500);
      MP3Player.stop();
  
    } else if ( input == "2") {
      MP3Player.play(2);
//      Serial.print("2");
      setColor(255, 0, 0);
      delay(2500);
      setColor(0, 0, 0);
      delay(2500);
      MP3Player.stop();
  
    } else if ( input == "3") {
//      Serial.print("3");
      MP3Player.play(2);
      setColor(255, 0, 0);
      delay(2500);
      setColor(0, 0, 0);
      delay(2500);
      MP3Player.stop();
  
    } else if ( input == "4") {
      MP3Player.play(2);
//      Serial.print("4");
      setColor(255, 255, 0);
      delay(2500);
      setColor(0, 0, 0);
      delay(2500);
      MP3Player.stop();
  
    } else {

    }
  //  Serial.println(input);




}


void setColor(int red, int green, int blue)
{

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
