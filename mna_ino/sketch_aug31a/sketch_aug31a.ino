#include <SoftwareSerial.h>

SoftwareSerial bt(3, 2); // rxPin = 블루투스 tx Pin, txPin = rx Pin

int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup() {
  Serial.begin(9600);  //시리얼 초기화
  bt.begin(9600);       //소프트웨어 시리얼 통신
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

String readString;
String str = "";
String hexstring;
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
//    Serial.println(readString);

    long number = strtol( &readString[1], NULL, 16);

    long r = number >> 16;
    long g = number >> 8 & 0xFF;
    long b = number & 0xFF;

    setColor(r, g, b);
    readString = "";
  }


  //  String hexstring = "#FF3Fa0";
  //
  //  // Get rid of '#' and convert it to integer
  //  long number = strtol( &hexstring[1], NULL, 16);
  //
  //  // Split them up into r, g, b values
  //  long r = number >> 16;
  //  long g = number >> 8 & 0xFF;
  //  long b = number & 0xFF;
  //
  //  setColor(r,g,b);
  //  Serial.println(r);
  //  Serial.println(g);
  //  Serial.println(b);






  //  if (bt.available()) {
  //    str = bt.readString();
  //    if (str.charAt(0) == '<' and str.charAt(str.length() - 1) == '>') {
  ////      //첫 문자가 <, 끝 문자가 > 이면
  ////      // 만약 작동하지 않는다면 str.length()-1 를 str.length()-2 로 수정하거나
  ////      // 시리얼 모니터 하단에 'line ending 없음'으로 변경하세요.
  ////      int first = str.indexOf(",");
  ////      int second = str.indexOf(",", first + 1);
  ////      //int strlength = str.length(); // 필요 없습니다.
  ////      int third = str.indexOf(">", second); // 처음 '>'가 나타나는 위치 찾기
  ////      String str1 = str.substring(1, first); // 첫 번째 토큰
  ////      String str2 = str.substring(first + 1, second); //두 번째 토큰
  ////      String str3 = str.substring(second + 1, third); //세 번째 토큰
  //
  //      Serial.println(str.charAt(0));
  //
  //    }
  //  }


}


void setColor(int red, int green, int blue)
{
  if ((red == 0) && (green == 0) && (blue == 0)) {
    return;
  }
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
