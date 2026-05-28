 #include<LiquidCrystal.h>
const int Rs = 2;
const int En = 3;
const int D4 = 4;
const int D5 = 5;
const int D6 = 6;
const int D7 = 7;
LiquidCrystal lcd (Rs,En,D4,D5,D6,D7);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
   lcd.setCursor(0,0);
   lcd.print(" KUNAL ");
}
