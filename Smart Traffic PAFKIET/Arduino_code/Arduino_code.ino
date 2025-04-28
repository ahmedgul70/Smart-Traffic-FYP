#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LaneA_Red 11
#define LaneA_Yellow 12
#define LaneA_Green 13
#define LaneB_Red A0
#define LaneB_Yellow A1
#define LaneB_Green 7
#define LaneC_Red 8
#define LaneC_Yellow A2
#define LaneC_Green A3
#define LaneD_Red 2
#define LaneD_Yellow 3
#define LaneD_Green 4

int cars = 0, Lane1 = 0, Lane2 = 0, Lane3 = 0, Lane4 = 0;
#define delay_green 2000
#define signal_delay_red  500
#define signal_delay_yellow 1000
uint32_t pmillis = 0;


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ECC Controls");
  lcd.setCursor(0, 1);
  lcd.print("And Automation");

  servo3.attach(9);  // Left
  servo3.write(40);

  servo2.attach(6);  // Top
  servo2.write(40);
  
  servo1.attach(5);  // Right
  servo1.write(40);
  
  servo4.attach(10);  // Bottom
  servo4.write(40);
  delay(1000);

  pins_init();
  delay(250);
  stopAll();

  Serial.println("Check");
  delay(5000);
  pmillis = millis();
}

bool serial = false;
void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('&');
    Lane1 = String_Split(data, ',' , 0).toInt(); // Route D -- right
    Lane2 = String_Split(data, ',' , 1).toInt(); // Route C -- top
    Lane3 = String_Split(data, ',' , 2).toInt(); // Route B -- left
    Lane4 = String_Split(data, ',' , 3).toInt(); // Route A -- bottom
    serial = true;
  }

  if (serial) {
    serial = false;
    lcd.clear();
    if (Lane4 > Lane1 && Lane4 > Lane2 && Lane4 > Lane3) { // Route A
      lcd.setCursor(5, 0);
      lcd.print("Route A");
      lcd.setCursor(5, 1);
      lcd.print("Timer : ");
      LaneA(delay_green, Lane4);
    }
    else if (Lane3 > Lane1 && Lane3 > Lane2 && Lane3 > Lane4) { // Route B
      lcd.setCursor(5, 0);
      lcd.print("Route B");
      lcd.setCursor(5, 1);
      lcd.print("Timer : ");
      LaneB(delay_green, Lane3);
    }
    else if (Lane2 > Lane1 && Lane2 > Lane3 && Lane2 > Lane4) { // Route C
      lcd.setCursor(5, 0);
      lcd.print("Route C");
      lcd.setCursor(5, 1);
      lcd.print("Timer : ");
      LaneD(delay_green, Lane2);
    }
    else if (Lane1 > Lane2 && Lane1 > Lane3 && Lane1 > Lane4) { // Route D
      lcd.setCursor(5, 0);
      lcd.print("Route D");
      lcd.setCursor(5, 1);
      lcd.print("Timer : ");
      LaneC(delay_green, Lane1);
    }
    else if (Lane1 == 0 && Lane2 == 0 && Lane3 == 0 && Lane4 == 0){
      serial = false;
      lcd.setCursor(5, 0);
      lcd.print("No Route");
      LaneA(5000, 1);
      LaneB(5000, 1);
      LaneD(5000, 1);
      LaneC(5000, 1);
    }
    Serial.println("Check");
    delay(5000);
  }
}

//Open

void LaneA(int signal_delay_green, int Lane) {
  //Lane A
  digitalWrite(LaneA_Red, HIGH); delay(signal_delay_red);
  digitalWrite(LaneA_Red, LOW); digitalWrite(LaneA_Yellow, HIGH); delay(signal_delay_yellow);
  digitalWrite(LaneA_Yellow, LOW);
  for (int i = 40; i >= 0; i--) {
    servo4.write(i);
    delay(5);
  }
  digitalWrite(LaneA_Green, HIGH);
  if (serial) {
    for (int i = (Lane * 10); i >= 0; i--) {
      if (i < 10) {
        lcd.setCursor(14, 1);
        lcd.print(" ");
      }
      lcd.setCursor(13, 1);
      lcd.print(i);
      delay(1000);
    }
  } else {
    delay(signal_delay_green);
  }
  for (int i = 0; i <= 40; i++) {
    servo4.write(i);
    delay(5);
  }
  digitalWrite(LaneA_Green, LOW); digitalWrite(LaneA_Red, HIGH);
  //Other Signals
  digitalWrite(LaneB_Red, HIGH);
  digitalWrite(LaneB_Yellow, LOW);
  digitalWrite(LaneB_Green, LOW);
  digitalWrite(LaneC_Red, HIGH);
  digitalWrite(LaneC_Yellow, LOW);
  digitalWrite(LaneC_Green, LOW);
  digitalWrite(LaneD_Red, HIGH);
  digitalWrite(LaneD_Yellow, LOW);
  digitalWrite(LaneD_Green, LOW);
}

void LaneB(int signal_delay_green, int Lane) {
  //Lane B
  digitalWrite(LaneB_Red, HIGH); delay(signal_delay_red);
  digitalWrite(LaneB_Red, LOW); digitalWrite(LaneB_Yellow, HIGH); delay(signal_delay_yellow);
  digitalWrite(LaneB_Yellow, LOW);
  for (int i = 40; i >= 0; i--) {
    servo3.write(i);
    delay(5);
  }
  digitalWrite(LaneB_Green, HIGH);
  if (serial) {
    for (int i = (Lane * 10); i >= 0; i--) {
      if (i < 10) {
        lcd.setCursor(14, 1);
        lcd.print(" ");
      }
      lcd.setCursor(13, 1);
      lcd.print(i);
      delay(1000);
    }
  } else {
    delay(signal_delay_green);
  }
  digitalWrite(LaneB_Green, LOW);
  for (int i = 0; i <= 40; i++) {
    servo3.write(i);
    delay(5);
  }
  digitalWrite(LaneB_Red, HIGH);
  //Other Signals
  digitalWrite(LaneA_Red, HIGH);
  digitalWrite(LaneA_Yellow, LOW);
  digitalWrite(LaneA_Green, LOW);
  digitalWrite(LaneC_Red, HIGH);
  digitalWrite(LaneC_Yellow, LOW);
  digitalWrite(LaneC_Green, LOW);
  digitalWrite(LaneD_Red, HIGH);
  digitalWrite(LaneD_Yellow, LOW);
  digitalWrite(LaneD_Green, LOW);
}

void LaneC(int signal_delay_green, int Lane) {
  //Lane C
  digitalWrite(LaneC_Red, HIGH); delay(signal_delay_red);
  digitalWrite(LaneC_Red, LOW); digitalWrite(LaneC_Yellow, HIGH); delay(signal_delay_yellow);
  digitalWrite(LaneC_Yellow, LOW);
  for (int i = 40; i >= 0; i--) {
    servo1.write(i);
    delay(5);
  }
  digitalWrite(LaneC_Green, HIGH);
  if (serial) {
    for (int i = (Lane * 10); i >= 0; i--) {
      if (i < 10) {
        lcd.setCursor(14, 1);
        lcd.print(" ");
      }
      lcd.setCursor(13, 1);
      lcd.print(i);
      delay(1000);
    }
  } else {
    delay(signal_delay_green);
  }
  digitalWrite(LaneC_Green, LOW);
  for (int i = 0; i <= 40; i++) {
    servo1.write(i);
    delay(5);
  }
  digitalWrite(LaneC_Red, HIGH);
  //Other Signals
  digitalWrite(LaneB_Red, HIGH);
  digitalWrite(LaneB_Yellow, LOW);
  digitalWrite(LaneB_Green, LOW);
  digitalWrite(LaneA_Red, HIGH);
  digitalWrite(LaneA_Yellow, LOW);
  digitalWrite(LaneA_Green, LOW);
  digitalWrite(LaneD_Red, HIGH);
  digitalWrite(LaneD_Yellow, LOW);
  digitalWrite(LaneD_Green, LOW);
}

void LaneD(int signal_delay_green, int Lane) {
  //Lane D
  digitalWrite(LaneD_Red, HIGH); delay(signal_delay_red);
  digitalWrite(LaneD_Red, LOW); digitalWrite(LaneD_Yellow, HIGH); delay(signal_delay_yellow);
  digitalWrite(LaneD_Yellow, LOW);
  for (int i = 40; i >= 0; i--) {
    servo2.write(i);
    delay(5);
  }
  digitalWrite(LaneD_Green, HIGH);
  if (serial) {
    for (int i = (Lane * 10); i >= 0; i--) {
      if (i < 10) {
        lcd.setCursor(14, 1);
        lcd.print(" ");
      }
      lcd.setCursor(13, 1);
      lcd.print(i);
      delay(1000);
    }
  } else {
    delay(signal_delay_green);
  }
  digitalWrite(LaneD_Green, LOW);
  for (int i = 0; i <= 40; i++) {
    servo2.write(i);
    delay(5);
  }
  digitalWrite(LaneD_Red, HIGH);
  //Other Signals
  digitalWrite(LaneB_Red, HIGH);
  digitalWrite(LaneB_Yellow, LOW);
  digitalWrite(LaneB_Green, LOW);
  digitalWrite(LaneC_Red, HIGH);
  digitalWrite(LaneC_Yellow, LOW);
  digitalWrite(LaneC_Green, LOW);
  digitalWrite(LaneA_Red, HIGH);
  digitalWrite(LaneA_Yellow, LOW);
  digitalWrite(LaneA_Green, LOW);
}

void lcdupdate() {
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("LaneA: ");
  lcd.print(Lane1);

  lcd.setCursor(10, 2);
  lcd.print("LaneB: ");
  lcd.print(Lane2);

  lcd.setCursor(0, 3);
  lcd.print("LaneC: ");
  lcd.print(Lane3);

  lcd.setCursor(10, 3);
  lcd.print("LaneD: ");
  lcd.print(Lane4);
}

String String_Split(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length();

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void pins_init() {
  pinMode(LaneA_Red, OUTPUT);
  digitalWrite(LaneA_Red, LOW);
  pinMode(LaneA_Yellow, OUTPUT); digitalWrite(LaneA_Yellow, LOW);
  pinMode(LaneA_Green, OUTPUT); digitalWrite(LaneA_Green, LOW);
  pinMode(LaneB_Red, OUTPUT); digitalWrite(LaneB_Red, LOW);
  pinMode(LaneB_Yellow, OUTPUT); digitalWrite(LaneB_Yellow, LOW);
  pinMode(LaneB_Green, OUTPUT); digitalWrite(LaneB_Green, LOW);
  pinMode(LaneC_Red, OUTPUT); digitalWrite(LaneC_Red, LOW);
  pinMode(LaneC_Yellow, OUTPUT); digitalWrite(LaneC_Yellow, LOW);
  pinMode(LaneC_Green, OUTPUT); digitalWrite(LaneC_Green, LOW);
  pinMode(LaneD_Red, OUTPUT); digitalWrite(LaneD_Red, LOW);
  pinMode(LaneD_Yellow, OUTPUT); digitalWrite(LaneD_Yellow, LOW);
  pinMode(LaneD_Green, OUTPUT); digitalWrite(LaneD_Green, LOW);

}

void stopAll() {
  digitalWrite(LaneA_Red, HIGH);
  digitalWrite(LaneA_Yellow, LOW);
  digitalWrite(LaneA_Green, LOW);
  digitalWrite(LaneB_Red, HIGH);
  digitalWrite(LaneB_Yellow, LOW);
  digitalWrite(LaneB_Green, LOW);
  digitalWrite(LaneC_Red, HIGH);
  digitalWrite(LaneC_Yellow, LOW);
  digitalWrite(LaneC_Green, LOW);
  digitalWrite(LaneD_Red, HIGH);
  digitalWrite(LaneD_Yellow, LOW);
  digitalWrite(LaneD_Green, LOW);
}
