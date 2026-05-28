#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>

// Wi-Fi access point credentials
const char* ssid = "SMART CLASSROOM";
const char* password = "07184596";

// Static IP configuration
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// GPIO pins for relays (active low)
const int relayPins[] = {18 , 21 ,22 , 23};
const int buttonPins[] = {2, 4};

// Relay states
bool relayStates[] = {HIGH, HIGH, HIGH, HIGH}; // Start with relays off

// Visitor counter variables
int visitorsIn = 0;
int visitorsOut = 0;
int currentVisitors = 0;


// Create a WebServer object on port 80
WebServer server(80);

// LCD pins
const int RS = 13, EN = 12, D4 = 14, D5 = 27, D6 = 26, D7 = 25;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// IR sensor pins
const int entrySensorPin = 33;
const int exitSensorPin = 32;

// HTML content generation function
String generateHTML() {
  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<style>";
  html += "body { font-family: 'Segoe UI', sans-serif; max-width: 480px; margin: auto; text-align: center; background: linear-gradient(to bottom, #eef2f5, #d0e0eb); color: #333; padding: 20px; border-radius: 10px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1); }";
  html += "h1 { font-size: 28px; color: #4CAF50; margin-bottom: 20px; text-shadow: 1px 1px 3px rgba(0,0,0,0.3); }";
  html += ".button { display: inline-block; width: 80%; padding: 15px; margin: 10px; font-size: 20px; font-weight: bold; color: white; background: linear-gradient(to right, #4CAF50, #45a049); border: none; border-radius: 25px; box-shadow: 0 5px 15px rgba(0, 0, 0, 0.2); transition: transform 0.3s, background-color 0.3s; }";
  html += ".button.off { background: linear-gradient(to right, #f44336, #d32f2f); }";
  html += ".button:hover { transform: scale(1.05); }";
  html += ".refresh { background: linear-gradient(to right, #2196F3, #1976D2); padding: 12px 25px; margin: 20px; color: white; font-size: 20px; border: none; border-radius: 25px; text-shadow: 1px 1px 3px rgba(0,0,0,0.3); }";
  html += ".footer { margin-top: 30px; color: #666; font-size: 16px; font-style: italic; text-shadow: 1px 1px 3px rgba(0,0,0,0.2); }";
  html += "</style></head><body>";
  html += "<h1>SMART CLASSROOM</h1>";
  html += "<p><strong>PRESENT:</strong> " + String(currentVisitors) + "</p>";
  html += "<p><strong>IN:</strong> " + String(visitorsIn) + "</p>";
  html += "<p><strong>OUT:</strong>" + String(visitorsOut) + "</p>";

  // Relay control buttons
  for (int i = 0; i < 4; i++) {
    html += "<p>Relay " + String(i+1) + ": " + (relayStates[i] == LOW ? "ON" : "OFF") + "</p>";
    html += "<form action=\"/toggle_relay_" + String(i) + "\" method=\"GET\">";
    html += "<button class=\"button " + String(relayStates[i] == LOW ? "off" : "") + "\" type=\"submit\">" 
            + String(relayStates[i] == LOW ? "Turn OFF" : "Turn ON") + " Relay " + String(i+1) + "</button>";
    html += "</form><br>";
  }

  // Refresh button
  html += "<form action=\"/refresh\" method=\"GET\">";
  html += "<button class=\"refresh\" type=\"submit\">Refresh</button>";
  html += "</form>";

  html += "<div class=\"footer\">&copy; SMART CLASSROOM - Designed for Efficiency</div>";
  html += "</body></html>";

  return html;
}

// Update visitor count and LCD display
void updateVisitorCount() {
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

  // Control relays based on current visitors
  if (currentVisitors >= 1) {
    // Turn ON all relays
    for (int i = 0; i < 4; i++) {
      digitalWrite(relayPins[i], LOW); // Active LOW: LOW means ON
      relayStates[i] = LOW; // Update relay states
    }
  } else {
    // Turn OFF all relays
    for (int i = 0; i < 4; i++) {
      digitalWrite(relayPins[i], HIGH); // Active LOW: HIGH means OFF
      relayStates[i] = HIGH; // Update relay states
    }
  }
}

// Toggle relay function
void toggleRelay(int relayIndex) {
  relayStates[relayIndex] = !relayStates[relayIndex];
  digitalWrite(relayPins[relayIndex], relayStates[relayIndex]);
}

// Setup server routes
void setupServerRoutes() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generateHTML());
  });

  for (int i = 0; i < 4; i++) {
    int relayIndex = i;
    server.on(("/toggle_relay_" + String(i)).c_str(), HTTP_GET, [relayIndex]() {
      toggleRelay(relayIndex);
      server.send(200, "text/html", generateHTML());
    });
  }
 
  server.on("/refresh", HTTP_GET, []() {
    server.send(200, "text/html", generateHTML());
  });
}

void setup() {
  Serial.begin(115200);

  // Setup relay pins
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);
  }

  // Setup LCD
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   WELCOME  TO ");
  lcd.setCursor(0, 1);
  lcd.print("SMART CLASSROOM");
  delay(2000);
  lcd.clear();

  // Setup IR sensors
  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);

  // Setup Wi-Fi access point
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  // Setup server routes
  setupServerRoutes();
  server.begin();
}

void loop() {
  server.handleClient();

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
    delay(2000); // Debounce delay
  }
}
//add some design in the html page add animations in the program and add css  in which add container , back ground effect and animation in button and in program add the speed rangeing and  indication in relay 3 and realy 4 for the 
