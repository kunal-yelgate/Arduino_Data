#include <LiquidCrystal.h>

// Initialize the LCD library with the pins
const int RS = 13, EN = 12, D4 = 14, D5 = 27, D6 = 26, D7 = 25;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// IR sensor pins
const int entrySensorPin = 33;
const int exitSensorPin = 32;

// Visitor counter variables
int visitorsIn = 0;
int visitorsOut = 0;
int currentVisitors = 0;


void setup() {

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Visitor Counter");
  delay(10);
  lcd.clear();
}

void loop() {
  // Read sensor states
  //entrySensorPin = digitalRead(entrySensorPin);
  //exitSensorPin = digitalRead(exitSensorPin);

 // Check entry sensor
  if (digitalRead(entrySensorPin) == HIGH) {
    visitorsIn++;
    delay(2500); // Debounce delay
  }

  // Check exit sensor
  if (digitalRead(exitSensorPin) == HIGH) {
    visitorsOut++;
    delay(2500); // Debounce delay
  }
}

void updateDisplay() {
 currentVisitors = visitorsIn - visitorsOut;

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("In: ");
  lcd.print(visitorsIn);
  lcd.setCursor(8, 0);
  lcd.print("Out: ");
  lcd.print(visitorsOut);
  lcd.setCursor(0, 1);
  lcd.print("Present: ");
  lcd.print(currentVisitors);
}
