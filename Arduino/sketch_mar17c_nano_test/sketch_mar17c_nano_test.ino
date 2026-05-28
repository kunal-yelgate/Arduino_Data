#include <LiquidCrystal.h>

// Initialize the LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
// Pins for IR sensors
const int inSensor = 2;
const int outSensor = 3;

// Counters for "In" and "Out"
int inCount = 0;
int outCount = 0;

void setup() {
  lcd.begin(16, 2); // Initialize 16x2 LCD
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);

  lcd.print("Visitor Counter");
  delay(2000); // Display welcome message
  lcd.clear();
}

void loop() {
  // Check "In" sensor
  if (digitalRead(inSensor) == HIGH) {
    inCount++;
    while (digitalRead(inSensor) == HIGH); // Debounce
    updateDisplay();
  }

  // Check "Out" sensor
  if (digitalRead(outSensor) == HIGH) {
    outCount++;
    while (digitalRead(outSensor) == HIGH); // Debounce
    updateDisplay();
  }
}

void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("In: ");
  lcd.print(inCount);
  lcd.setCursor(0, 1);
  lcd.print("Out: ");
  lcd.print(outCount);
}
