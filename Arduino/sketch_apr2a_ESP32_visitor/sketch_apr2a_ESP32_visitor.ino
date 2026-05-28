#include <LiquidCrystal.h>
// Define LCD pins
const int RS = 26;  // Register Select pin
const int EN = 25;  // Enable pin
const int D4 = 13;  // Data pin D4
const int D5 = 12;  // Data pin D5
const int D6 = 14;  // Data pin D6
const int D7 = 27;  // Data pin D7
#define RELAY1_PIN         05  // Relay 1
#define RELAY2_PIN         18  // Relay 2
#define RELAY3_PIN         19  // Relay 3
#define RELAY4_PIN         21  // Relay 4

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// IR sensor pin definitions
const int entrySensorPin = 33;
const int exitSensorPin = 32;

// LED pin definitions
const int ledPins[] = {2};
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
  delay(2000);
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
    delay(2000); // Debounce delay
  }

  // Check exit sensor
  if (digitalRead(exitSensorPin) == HIGH) {
    visitorsOut++;
    updateVisitorCount();
    delay(3000); // Debounce delay
  }
}
void controlRelays() {
  if (currentVisitors > 0) {
    // Turn ON all relays
    digitalWrite(RELAY1_PIN, HIGH);
    digitalWrite(RELAY2_PIN, HIGH);
    digitalWrite(RELAY3_PIN, HIGH);
    digitalWrite(RELAY4_PIN, HIGH);
  } else {
    // Turn OFF all relays
    digitalWrite(RELAY1_PIN, LOW);
    digitalWrite(RELAY2_PIN, LOW);
    digitalWrite(RELAY3_PIN, LOW);
    digitalWrite(RELAY4_PIN, LOW);
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

