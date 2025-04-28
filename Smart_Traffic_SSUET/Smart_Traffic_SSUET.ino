#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

const int R1 = 5;
const int Y1 = 6;
const int G1 = 7;

const int R2 = 8;
const int Y2 = 10;
const int G2 = 9;

const int R3 = 11;
const int Y3 = 13;
const int G3 = 12;

const int R4 = A0;
const int Y4 = 2;
const int G4 = 4;

String Data;
String route = " ", carcount = " ";
int Lane1, Lane2, Lane3, Lane4;
//*******************************************************

void setup() {
  Serial.begin(9600);
  initLEDs(); //debug();
  //  debug();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Intelligent Traffic ");
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  delay(5000);
  lcd.clear();
}

void loop() {
  if (Serial.available() > 0)
  {

    Data = Serial.readStringUntil("&");
    //Serial.println(Data);
    Lane1 = String_Split(Data, ',' , 0).toInt();
    Lane2 = String_Split(Data, ',' , 1).toInt();
    Lane3 = String_Split(Data, ',' , 2).toInt();
    Lane4 = String_Split(Data, ',' , 3).toInt();

    //Serial.print(Lane1); Serial.print("\t");
    //Serial.print(Lane2); Serial.print("\t");
    //Serial.print(Lane3); Serial.print("\t");
    //Serial.print(Lane4);

    count();
  }

}

// ******************************************************

void count() {
  if (Lane1 > Lane2 && Lane1 > Lane3 && Lane1 > Lane4) { // Route A
    lcd.setCursor(0, 0);
    lcd.print("Route A  ");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane1);
    Signal_Play(1, 4, 1, Lane1);
  }
  else if (Lane2 > Lane1 && Lane2 > Lane3 && Lane2 > Lane4) { // Route B
    lcd.setCursor(0, 0);
    lcd.print("Route B");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane2);
    Signal_Play(2, 4, 1, Lane2);
  }
  else if (Lane3 > Lane1 && Lane3 > Lane2 && Lane3 > Lane4) { // Route C
    lcd.setCursor(0, 0);
    lcd.print("Route C");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane3);
    Signal_Play(3, 4, 1, Lane3);
  }
  else if (Lane4 > Lane1 && Lane4 > Lane2 && Lane4 > Lane3) { // Route D
    lcd.setCursor(0, 0);
    lcd.print("Route D");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane4);
    Signal_Play(4, 4, 1, Lane4);
  }
  else {
    //    Signal_Play(1, 4, 1, 5);
    //    Signal_Play(2, 4, 1, 5);
    //    Signal_Play(3, 4, 1, 5);
    //    Signal_Play(4, 4, 1, 5);
    digitalWrite(R1, HIGH);
    digitalWrite(Y1, LOW);
    digitalWrite(G1, LOW);
    digitalWrite(R2, HIGH);
    digitalWrite(Y2, LOW);
    digitalWrite(G2, LOW);
    digitalWrite(R3, HIGH);
    digitalWrite(Y3, LOW);
    digitalWrite(G3, LOW);
    digitalWrite(R4, HIGH);
    digitalWrite(Y4, LOW);
    digitalWrite(G4, LOW);
  }
}

void Signal_Play(int Signal_Number, int r, int y, int g)
{
  if (Signal_Number == 1)
  {
    RouteA();
    digitalWrite(R1, HIGH);
    digitalWrite(Y1, LOW);
    digitalWrite(G1, LOW);
    delay(r * 250);
    digitalWrite(R1, LOW);
    digitalWrite(Y1, HIGH);
    digitalWrite(G1, LOW);
    delay(y * 1000);
    digitalWrite(R1, LOW);
    digitalWrite(Y1, LOW);
    digitalWrite(G1, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    for (int i = 1; i <= g; i++) {
      lcd.setCursor(6, 1);
      lcd.print(i);
      delay(i * 1000);
    }
  }

  else if ( Signal_Number == 2)
  {
    RouteB();
    digitalWrite(R2, HIGH);
    digitalWrite(Y2, LOW);
    digitalWrite(G2, LOW);
    delay(r * 250);
    digitalWrite(R2, LOW);
    digitalWrite(Y2, HIGH);
    digitalWrite(G2, LOW);
    delay(y * 1000);
    digitalWrite(R2, LOW);
    digitalWrite(Y2, LOW);
    digitalWrite(G2, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    for (int i = 1; i <= g; i++) {
      lcd.setCursor(6, 1);
      lcd.print(i);
      delay(i * 1000);
    }
  }
  else if ( Signal_Number == 3)
  {
    RouteC();
    digitalWrite(R3, HIGH);
    digitalWrite(Y3, LOW);
    digitalWrite(G3, LOW);
    delay(r * 250);
    digitalWrite(R3, LOW);
    digitalWrite(Y3, HIGH);
    digitalWrite(G3, LOW);
    delay(y * 1000);
    digitalWrite(R3, LOW);
    digitalWrite(Y3, LOW);
    digitalWrite(G3, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    for (int i = 1; i <= g; i++) {
      lcd.setCursor(6, 1);
      lcd.print(i);
      delay(i * 1000);
    }
  }

  else if ( Signal_Number == 4)
  {
    RouteD();
    digitalWrite(R4, HIGH);
    digitalWrite(Y4, LOW);
    digitalWrite(G4, LOW);
    delay(r * 250);
    digitalWrite(R4, LOW);
    digitalWrite(Y4, HIGH);
    digitalWrite(G4, LOW);
    delay(y * 1000);
    digitalWrite(R4, LOW);
    digitalWrite(Y4, LOW);
    digitalWrite(G4, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    for (int i = 1; i <= g; i++) {
      lcd.setCursor(6, 1);
      lcd.print(i);
      delay(i * 1000);
    }
  }
}
void RouteB() {
  digitalWrite(R3, HIGH);
  digitalWrite(Y3, LOW);
  digitalWrite(G3, LOW);

  digitalWrite(R1, HIGH);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  digitalWrite(R4, HIGH);
  digitalWrite(Y4, LOW);
  digitalWrite(G4, LOW);
}
void RouteC() {
  digitalWrite(R1, HIGH);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  digitalWrite(R2, HIGH);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);

  digitalWrite(R4, HIGH);
  digitalWrite(Y4, LOW);
  digitalWrite(G4, LOW);
}
void RouteD() {
  digitalWrite(R1, HIGH);
  digitalWrite(Y1, LOW);
  digitalWrite(G1, LOW);

  digitalWrite(R2, HIGH);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);

  digitalWrite(R3, HIGH);
  digitalWrite(Y3, LOW);
  digitalWrite(G3, LOW);
}

void RouteA() {
  digitalWrite(R2, HIGH);
  digitalWrite(Y2, LOW);
  digitalWrite(G2, LOW);

  digitalWrite(R3, HIGH);
  digitalWrite(Y3, LOW);
  digitalWrite(G3, LOW);

  digitalWrite(R4, HIGH);
  digitalWrite(Y4, LOW);
  digitalWrite(G4, LOW);
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

void debug() {
  pinMode(R1, OUTPUT);
  pinMode(Y1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(Y2, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(Y3, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(Y4, OUTPUT);
  pinMode(G4, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(Y1, HIGH);
  digitalWrite(G1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(Y2, HIGH);
  digitalWrite(G2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(Y3, HIGH);
  digitalWrite(G3, HIGH);
  digitalWrite(R4, HIGH);
  digitalWrite(Y4, HIGH);
  digitalWrite(G4, HIGH);
}
void initLEDs() {
  pinMode(R1, OUTPUT);
  digitalWrite(R1, LOW);
  pinMode(Y1, OUTPUT);
  digitalWrite(Y1, LOW);
  pinMode(G1, OUTPUT);
  digitalWrite(G1, LOW);

  pinMode(R2, OUTPUT);
  digitalWrite(R2, LOW);
  pinMode(Y2, OUTPUT);
  digitalWrite(Y2, LOW);
  pinMode(G2, OUTPUT);
  digitalWrite(G2, LOW);

  pinMode(R3, OUTPUT);
  digitalWrite(R3, LOW);
  pinMode(Y3, OUTPUT);
  digitalWrite(Y3, LOW);
  pinMode(G3, OUTPUT);
  digitalWrite(G3, LOW);

  pinMode(R4, OUTPUT);
  digitalWrite(R4, LOW);
  pinMode(Y4, OUTPUT);
  digitalWrite(Y4, LOW);
  pinMode(G4, OUTPUT);
  digitalWrite(G4, LOW);
}
