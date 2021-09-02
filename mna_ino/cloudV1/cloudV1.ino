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

int location = 0;
String readString;
String input="0";


void setup() {
  Serial.begin(9600);  //시리얼 초기화
  bt.begin(9600);       //소프트웨어 시리얼 통신
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}



void loop() {
  while(bt.available()){
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

  if( input == "1" ){
    setColor(255,0,0);
    delay(5000);
    setColor(0,0,0);
    delay(5000);
    
  } else if( input == "2"){
    setColor(0,255,0);
    delay(5000);
    setColor(0,0,0);
    delay(5000);
    
  }else if( input == "3"){
    setColor(0,0,255);
    delay(5000);
    setColor(0,0,0);
    delay(5000);
    
  }else if( input == "4"){
    setColor(255,255,0);
    delay(5000);
    setColor(0,0,0);
    delay(5000);
    
  }else{
    
  }
//  Serial.println(input);



  
}


void setColor(int red, int green, int blue)
{

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
