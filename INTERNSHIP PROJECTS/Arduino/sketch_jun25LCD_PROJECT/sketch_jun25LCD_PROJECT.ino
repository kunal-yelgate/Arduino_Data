#include <LiquidCrystal.h>
const int Rs = 2;
const int En = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
LiquidCrystal lcd(Rs, En, D4, D5, D6, D7);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(20, 2);
  lcd.setCursor(0, 0);
  lcd.print("  SUMMER INTERNSHIP ");
  lcd.setCursor(0, 1);
  lcd.print("    PROGRAM 2024 ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);
  lcd.print("MJEMBESYS TECHNOCRATS");
  lcd.setCursor(0, 1);
  lcd.print("  MR.MAHESH JADHAV");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("    VDF SCHOOL OF ");
  lcd.setCursor(0, 1);
  lcd.print("  POLYTECHNIC LATUR");
  delay(2000);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print(" GUIDE BY");
  lcd.setCursor(3, 1);
  lcd.print("MR.K.D.DADPE");
  delay(2000);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("SUBMITTED BY");
  lcd.setCursor(3, 1);
  lcd.print("KUNAL YELGATE");
  delay(2000);
  lcd.clear();
}
