#include <LiquidCrystal.h>

// LCD pin definitions
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// IR sensor pin definitions
const int entrySensorPin = 2;
const int exitSensorPin = 3;

// LED pin definitions
const int ledPins[] = {4, 5, 6, 7};

// Visitor count variables
int visitorsIn = 0;
int visitorsOut = 0;
int currentVisitors = 0;

void setup() {
  // Initialize LCD
   lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME  TO ");
  lcd.setCursor(0, 1);
  lcd.print("SMART CLASSROOM");
  delay(500);
  lcd.clear();
 
  lcd.print("In: ");
  lcd.print(visitorsIn);
  lcd.setCursor(8, 0);
  lcd.print(" Out: ");
  lcd.print(visitorsOut);
  lcd.setCursor(0, 1); // Second row
  lcd.print("PRESENT: ");
  lcd.print(currentVisitors);

  // Set up IR sensor pins
  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);

  // Set up LED pins
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Turn OFF all LEDs initially
  }
}

void loop() {
  // Check entry sensor
  if (digitalRead(entrySensorPin) == HIGH) {
    visitorsIn++;
    updateVisitorCount();
    delay(500); // Debounce delay
  }

  // Check exit sensor
  if (digitalRead(exitSensorPin) == HIGH) {
    visitorsOut++;
    updateVisitorCount();
    delay(500); // Debounce delay
  }
}

void updateVisitorCount() {
  // Calculate current visitors
  currentVisitors = visitorsIn - visitorsOut;

  // Update LCD display
  lcd.clear();
  
  lcd.setCursor(1, 0);
  lcd.print("In: ");
  lcd.print(visitorsIn);
  lcd.setCursor(8, 0);
  lcd.print(" Out: ");
  lcd.print(visitorsOut);
   lcd.setCursor(0, 1); // Second row
  lcd.print(" Present:");
  lcd.print(currentVisitors);

  // Update LEDs based on current visitors
  for (int i = 0; i < 4; i++) {
    if (currentVisitors >= 1) {
      digitalWrite(ledPins[i], HIGH); // Turn ON LEDs
    } else {
      digitalWrite(ledPins[i], LOW); // Turn OFF LEDs
    }
  }
}
