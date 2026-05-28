#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(26, 25, 24, 23, 22, 21); // RS, EN, D4, D5, D6, D7

// IR sensor
const int irSensorPin = 15; // GPIO pin connected to the IR sensor

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows
  lcd.setCursor(0, 0);
  lcd.print("IR Sensor Demo");

  // Initialize IR sensor pin
  pinMode(irSensorPin, INPUT);
}

void loop() {
  // Read IR sensor value
  int irValue = digitalRead(irSensorPin);

  // Check IR sensor response and display on LCD
  lcd.setCursor(0, 1); // Set cursor to second line
  if (irValue == HIGH) {
    lcd.print("OUT ");
  } else {
    lcd.print("IN  ");
  }
  delay(500); // Small delay for better display readability
}
