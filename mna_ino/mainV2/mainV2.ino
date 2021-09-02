/*
 *  mode 0: Auto - 조도센서에 따라 자동조절
 *  mode 1: Manual - hex값에 따라 색상 조절
 *  mode 2: On - 흰색 온                   //추가 기능
 *  mode 3 : Off - 끄기
 */
#include <SoftwareSerial.h>

SoftwareSerial bt(3, 2); // rxPin = 블루투스 tx Pin, txPin = rx Pin

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

int mode = 0;
String readString;
String color = "";


void setup() {
  Serial.begin(9600);  //시리얼 초기화
  bt.begin(9600);       //소프트웨어 시리얼 통신
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}



void loop() {

  while (bt.available()) {
    delay(10);
    char c = bt.read();
    if (c == ',') {
      break;
    }
    readString += c;
  }

  if (readString.length() > 0) {
    if (readString.length() == 1) {                       // Mode
//      Serial.print(readString.toInt());
      mode = readString.toInt();
    }
    
    if (readString.length() == 7) {
      long number = strtol( &readString[1], NULL, 16);    // hexCode
      long r = number >> 16;
      long g = number >> 8 & 0xFF;
      long b = number & 0xFF;   
      if(mode == 1){
         setColor(r,g,b);
      }
    }
    readString = "";
  }





      
  switch(mode){
    case 0: mode0(); break;
    case 1: break;
    case 2: mode2(); break;
    case 3: mode3(); break;

  }

  
}


void mode0(){

  setColor(0,0,0);
  delay(700);
  setColor(255,0,0);
  delay(700);
  
}

void mode1(){
  setColor(0,0,0);
  delay(300);
  setColor(0,255,0);
  delay(300);
  
}

void mode2(){
  setColor(255,255,255);
  delay(20);
  
}

void mode3(){
  setColor(0,0,0);
}


void setColor(int red, int green, int blue)
{

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
