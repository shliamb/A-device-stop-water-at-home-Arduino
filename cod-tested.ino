//Water-block created by Saposhnikov A.V. август 2023 1Rmaster.ru

/*
  Device activity mode on click button "Action":
  h=1 - waiting to alert and "ok closed" (2)
  1. ок opened.                     if h=1 and click > close tap, h=2 (mode2)
  2. ok closed.                     if h=2 and click > open tap, h=1 (mode1)
  3. alert to close.                if 1.2.3 sensor... and h=1 > close tap, buzer on, led alert, LCD,  h=4 (mode4)
  4. alert clos-wait buzer on.      if h=4 and click > buzer off, h=5 (mode5)
  5. alert clos-wait open.          if h=5 and click > open tap, h=1 (mode1), s=0, 
*/

/*
  Triggering on sensors:
  s=0 - tap opening counter
  1. if s=0 and sens1 or sens2.. and h=1 (mode1) > led alert, buzer, LCD, close tap, s=s+1, h=4 (mode4)
*/



#include <GyverOLED.h>
GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;

int s;// - tap
int h; // - waiting to alert and "ok closed" (2)
int w =  600; // 600ms   1 tap = 600ms*10*2 - 12sec to motor

void setup() {
s = 0; // - tap opening counter
h = 1; // - waiting to alert and "ok closed" (2)
//BUZER
  pinMode(PA9, OUTPUT);
//BUTTON
  pinMode(PA10, INPUT_PULLUP);//кнопка, поддтягивает в внутренней конфигурации контроллера резистор к пиатнию для высокого уровня
//LCD
//Screensaver
  oled.init();        // инициализация
  oled.clear();       // очистка
  //oled.setScale(1);   // масштаб текста (1..4)
  //oled.home();        // курсор в 0,0
  //oled.print("IS");
  oled.setScale(1);
  oled.setCursor(25, 1);
  oled.print("Developed by");
  oled.setCursor(25, 2);
  oled.print("1Rmaster.ru");
  delay(3000);
//Working Screen
  oled.clear();
  oled.setScale(1);
  oled.home();
  oled.print("IS");
  oled.setScale(3);
  oled.setCursor(15, 0);
  oled.print("OPEN");
//PORT
  Serial.begin(9600);
//WATER SENSOR
  pinMode(PA0, INPUT);//1 sensor
  pinMode(PA1, INPUT);//2 sensor
  pinMode(PA2, INPUT);//3 sensor
  pinMode(PA3, INPUT);//4 sensor
  pinMode(PA4, INPUT);//5 sensor
  pinMode(PA5, INPUT);//6 sensor
  pinMode(PA6, INPUT);//7 sensor
//MOTORS
  pinMode(PC13, OUTPUT);
  pinMode(PB11, OUTPUT);
  pinMode(PB10, OUTPUT);
  pinMode(PB1, OUTPUT);
  pinMode(PB0, OUTPUT);
//BUZER
  digitalWrite(PA9, 1); delay(50); digitalWrite(PA9, 0); delay(40); digitalWrite(PA9, 1); delay(150); digitalWrite(PA9, 0); // звук для внимания при включении
//Led Action off
  digitalWrite(PC13, HIGH);
}


void loop() {
//Button read
  boolean button = !digitalRead(PA10);
//Sensors read
  int rawReading1 = analogRead(PA0); //1 sensor water
  int rawReading2 = analogRead(PA1); //2
  int rawReading3 = analogRead(PA2); //3
  int rawReading4 = analogRead(PA3); //4
  int rawReading5 = analogRead(PA4); //5
  int rawReading6 = analogRead(PA5); //6
  //int rawReading7 = analogRead(PA6); //7
  float volts1 = rawReading1 / 704.6;
  float volts2 = rawReading2 / 704.6;
  float volts3 = rawReading3 / 704.6;
  float volts4 = rawReading4 / 704.6;
  float volts5 = rawReading5 / 704.6;
  float volts6 = rawReading6 / 704.6;
  //float volts7 = rawReading7 / 704.6;


// CLICK BUTTON
// ок opened - click, clos (1)
  if ( button == 1 && h == 1 ) { // close tap
    //LCD
      oled.clear(); oled.setScale(1);
    //MOTOR close
      digitalWrite(PC13, LOW);
      oled.setCursor(0, 3);
      digitalWrite(PB1, HIGH);//in4
      for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
      digitalWrite(PB1, LOW);//in4
      digitalWrite(PB10, HIGH);//in1
      for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
      digitalWrite(PB10, LOW);//in1
      digitalWrite(PC13, HIGH);
    //LCD
      oled.clear(); oled.setScale(1); oled.home(); oled.print("IS"); oled.setScale(3); oled.setCursor(15, 0); oled.print("CLOS");

    h = 6;
  };
//
  if (!button && h == 6  ) { // обработчик отпускания нажатой кнопки
  h = 2;
  };
// ok closed - click, open tap (2)
  if ( button == 1 && h == 2 ) { 
  //LCD
    oled.clear(); oled.setScale(1);
  //MOTOR OPEN
    digitalWrite(PC13, LOW);
    oled.setCursor(0, 3);
    digitalWrite(PB0, HIGH);//in2
    for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
    digitalWrite(PB0, LOW);//in2
    digitalWrite(PB11, HIGH);//in3
    for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
    digitalWrite(PB11, LOW);//in3
    digitalWrite(PC13, HIGH);
  //LCD
    oled.clear(); oled.setScale(1); oled.home(); oled.print("IS"); oled.setScale(3); oled.setCursor(15, 0); oled.print("OPEN");
  h = 1;
  };
// (4)
  if ( button == 1 && h == 4 ) {
  //Buzer
    digitalWrite(PA9, 0); //Buzer off
  //LCD
    oled.clear(); oled.setScale(1); oled.home(); oled.print("IS"); oled.setScale(3); oled.setCursor(15, 0); oled.print("CLOS");
  h = 7;
  };
//
  if (!button && h == 7  ) { // обработчик отпускания нажатой кнопки
  h = 5;
  };
// (5)
  if ( button == 1 && h == 5 ) { 
  //LED Alert
    digitalWrite(PC13, HIGH);
  //LCD
    oled.clear(); oled.setScale(1); oled.setCursor(0, 3);
  //MOTOR OPEN
    digitalWrite(PB0, HIGH);//in2
    for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
    digitalWrite(PB0, LOW);//in2
    digitalWrite(PB11, HIGH);//in3
    for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
    digitalWrite(PB11, LOW);//in3
  //LCD
    oled.clear(); oled.setScale(1); oled.home(); oled.print("IS"); oled.setScale(3); oled.setCursor(15, 0); oled.print("OPEN");
  h = 1;
  s = 0;
  };


//
  if ( volts1 >= 1 or volts2 >= 1 or volts3 >= 1 or volts4 >= 1 or volts5 >= 1 or volts6 >= 1 )  {
    if ( s == 0 && h == 1 ) {
      //Buzer
        digitalWrite(PA9, 1);
      //LED Alert
        digitalWrite(PC13, LOW);
      //LCD
        oled.clear();
        oled.setCursor(10, 0); oled.setScale(2); oled.print("* ALERT *"); oled.setScale(1); oled.setCursor(0, 2); oled.print("sensor:");
      //LCD TAPS
        if (volts1 >= 1 && s == 0) { oled.setCursor(39, 2); oled.print(" 1 "); };
        if (volts2 >= 1 && s == 0) { oled.setCursor(50, 2); oled.print(" 2 "); };
        if (volts3 >= 1 && s == 0) { oled.setCursor(65, 2); oled.print(" 3 "); };
        if (volts4 >= 1 && s == 0) { oled.setCursor(80, 2); oled.print(" 4 "); };
        if (volts5 >= 1 && s == 0) { oled.setCursor(95, 2); oled.print(" 5 "); };
        if (volts6 >= 1 && s == 0) { oled.setCursor(114, 2); oled.print(" 6 "); };
      //MOTOR close
        oled.setCursor(0, 3);
        digitalWrite(PB1, HIGH);//in4
        for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
        digitalWrite(PB1, LOW);//in4
        digitalWrite(PB10, HIGH);//in1
        for (int j = 0; j <10; j++) oled.print("."), delay(w); //по 600мс*10 - 6000мс
        digitalWrite(PB10, LOW);//in1
    };
      s = s+1;
      h = 4;
  };


}
