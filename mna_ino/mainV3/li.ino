
/*
    mode 0: Auto - 조도센서에 따라 자동조절
    mode 1: Manual - hex값에 따라 색상 조절
    mode 2: On - 흰색 온                   //추가 기능
    mode 3 : Off - 끄기
*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <AltSoftSerial.h>
#include <SoftwareSerial.h>
#define PIN 6
#define NUMPIXELS 12

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

AltSoftSerial bt; // rxPin = 블루투스 tx Pin, txPin = rx Pin


int redPin = 3;
int greenPin = 10;
int bluePin = 11;
int cds = A6;

int mode = 0;
String readString;
String color = "";


void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin();
  Serial.begin(9600);  //시리얼 초기화
  bt.begin(9600);       //소프트웨어 시리얼 통신

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  delay(1);

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
      if (mode == 1) {
        setColor(r, g, b);
        //        for (int i = 0; i < NUMPIXELS; i++) {
        //          pixels.setPixelColor(i, pixels.Color(r, g, b));
        //        }
        //        pixels.show();

      }
    }
    readString = "";
  }






  switch (mode) {
    case 0: mode0(); break;
    case 1: break;
    case 2: mode2(); break;
    case 3: mode3(); break;

  }


}


void mode0() {
  int cds_read = analogRead(cds) / 4;
  Serial.println(cds_read);
  if (cds_read < 100) {
    setColor(255, 255, 255);
  } else if (cds_read < 140) {
    setColor(170, 170, 170);
  } else if (cds_read < 170) {
    setColor(100, 100, 100);
  } else if (cds_read < 190) {
    setColor(70, 70, 70);
  } else {
    setColor(10, 10, 10);
  }

  //  setColor(cds_read,cds_read,cds_read);

  //  setColor(0, 0, 0);
  //  delay(700);
  //  setColor(255, 0, 0);
  //  delay(700);

}

void mode1() {
  setColor(0, 0, 0);
  delay(300);
  setColor(0, 255, 0);
  delay(300);

}

void mode2() {
  setColor(255, 255, 255);
  delay(20);

}

void mode3() {
  setColor(0, 0, 0);
}


void setColor(int red, int green, int blue)
{
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
  }
  //  analogWrite(redPin, red);
  //  analogWrite(greenPin, green);
  //  analogWrite(bluePin, blue);
  pixels.show();
}
