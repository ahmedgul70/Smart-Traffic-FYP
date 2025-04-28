#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
// top
const int R1 = 2;
const int Y1 = 3;
const int G1 = 4;

// left
const int R2 = A3;
const int Y2 = 8;
const int G2 = 9;

// bottom
const int R3 = 5;
const int Y3 = 6;
const int G3 = 7;

// right
const int R4 = A0;
const int Y4 = A1;
const int G4 = A2;

String Data;
String route = " ", carcount = " ";
int Lane1 = 0, Lane2 = 0, Lane3 = 0, Lane4 = 0;
//*******************************************************

void setup() {
  Serial.begin(9600);
  initLEDs();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Intelligent Traffic ");
  lcd.setCursor(0, 1);
  lcd.print("Control System");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Lane-1: ");
  lcd.print(Lane1);
  lcd.setCursor(0, 1);
  lcd.print("Lane-2: ");
  lcd.print(Lane2);
  lcd.setCursor(0, 2);
  lcd.print("Lane-3: ");
  lcd.print(Lane3);
  lcd.setCursor(0, 3);
  lcd.print("Lane-4: ");
  lcd.print(Lane4);
}

void loop() {
  if (Serial.available() > 0)
  {
    Data = Serial.readStringUntil("&");
    //    Serial.println(Data);
    Lane1 = String_Split(Data, ',' , 0).toInt();
    Lane2 = String_Split(Data, ',' , 1).toInt();
    Lane3 = String_Split(Data, ',' , 2).toInt();
    Lane4 = String_Split(Data, ',' , 3).toInt();

    if(Lane1 > 2){
      Lane1 = 2;
    }
    else if(Lane2 > 2){
      Lane2 = 2;
    }
    else if(Lane3 > 2){
      Lane3 = 2;
    }
    else if(Lane4 > 2){
      Lane4 = 2;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lane-1: ");
    lcd.print(Lane1);
    lcd.setCursor(0, 1);
    lcd.print("Lane-2: ");
    lcd.print(Lane2);
    lcd.setCursor(0, 2);
    lcd.print("Lane-3: ");
    lcd.print(Lane3);
    lcd.setCursor(0, 3);
    lcd.print("Lane-4: ");
    lcd.print(Lane4);
    count();
  }
}

// ******************************************************
void count() {
  if (Lane1 > Lane2 && Lane1 > Lane3 && Lane1 > Lane4) { // Route A
    lcd.setCursor(12, 0);
    lcd.print("Route A");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane1);
    Signal_Play(1, 4, 1, Lane1);
  }
  else if (Lane2 > Lane1 && Lane2 > Lane3 && Lane2 > Lane4) { // Route B
    lcd.setCursor(12, 1);
    lcd.print("Route B");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane2);
    Signal_Play(2, 4, 1, Lane2);
  }
  else if (Lane3 > Lane1 && Lane3 > Lane2 && Lane3 > Lane4) { // Route C
    lcd.setCursor(12, 2);
    lcd.print("Route C");
    //    lcd.setCursor(0, 1);
    //    lcd.print(Lane3);
    Signal_Play(3, 4, 1, Lane3);
  }
  else if (Lane4 > Lane1 && Lane4 > Lane2 && Lane4 > Lane3) { // Route D
    lcd.setCursor(12, 3);
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
    delay(g * 3000);
    //    lcd.setCursor(0, 1);
    //    lcd.print("Time: ");
    //    for (int i = 1; i <= g; i++) {
    //      lcd.setCursor(6, 1);
    //      lcd.print(i);
    //      delay(i * 1000);
    //    }
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
    delay(g * 3000);
    //    lcd.setCursor(0, 1);
    //    lcd.print("Time: ");
    //    for (int i = 1; i <= g; i++) {
    //      lcd.setCursor(6, 1);
    //      lcd.print(i);
    //      delay(i * 1000);
    //    }
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
    delay(g * 3000);
    //    lcd.setCursor(0, 1);
    //    lcd.print("Time: ");
    //    for (int i = 1; i <= g; i++) {
    //      lcd.setCursor(6, 1);
    //      lcd.print(i);
    //      delay(i * 1000);
    //    }
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
    delay(g * 3000);
    //    lcd.setCursor(0, 1);
    //    lcd.print("Time: ");
    //    for (int i = 1; i <= g; i++) {
    //      lcd.setCursor(6, 1);
    //      lcd.print(i);
    //      delay(i * 1000);
    //    }
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

void initLEDs() {
  pinMode(R1, OUTPUT);
  digitalWrite(R1, HIGH);
  pinMode(Y1, OUTPUT);
  digitalWrite(Y1, LOW);
  pinMode(G1, OUTPUT);
  digitalWrite(G1, LOW);

  pinMode(R2, OUTPUT);
  digitalWrite(R2, HIGH);
  pinMode(Y2, OUTPUT);
  digitalWrite(Y2, LOW);
  pinMode(G2, OUTPUT);
  digitalWrite(G2, LOW);

  pinMode(R3, OUTPUT);
  digitalWrite(R3, HIGH);
  pinMode(Y3, OUTPUT);
  digitalWrite(Y3, LOW);
  pinMode(G3, OUTPUT);
  digitalWrite(G3, LOW);

  pinMode(R4, OUTPUT);
  digitalWrite(R4, HIGH);
  pinMode(Y4, OUTPUT);
  digitalWrite(Y4, LOW);
  pinMode(G4, OUTPUT);
  digitalWrite(G4, LOW);
}
