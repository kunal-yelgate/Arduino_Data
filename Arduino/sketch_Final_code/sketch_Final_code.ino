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
  html += "body { font-family: 'Segoe UI', sans-serif; background: radial-gradient(circle, #f0f8ff, #e6eef3); margin: 0; padding: 20px; color: #333; text-align: center; }";
  html += "h1 { font-size: 42px; color: #4CAF50; text-shadow: 0 4px 10px rgba(0, 0, 0, 0.2); margin-bottom: 30px; }";
  html += ".container { margin: 20px auto; padding: 25px; width: 90%; max-width: 700px; background: linear-gradient(to bottom, #ffffff, #eef7fc); box-shadow: 0 10px 20px rgba(0, 0, 0, 0.2); border-radius: 20px; border: 2px solid #4CAF50; }";
  html += ".visitor-container { background: radial-gradient(circle, #d9f4ff, #ffffff); padding-bottom: 15px; }";
  html += ".relay-container { background: radial-gradient(circle, #e6ffe8, #ffffff); margin-top: 30px; }";
  html += ".relay { margin-bottom: 20px; padding: 20px; background: #ffffff; border: 2px solid #ddd; border-radius: 10px; box-shadow: 0 6px 10px rgba(0, 0, 0, 0.1); }";
  html += ".slider-container { margin: 20px 0; }";
  html += ".slider { width: 85%; margin: 10px auto; height: 8px; background: linear-gradient(to right, #4CAF50, #45a049); border-radius: 8px; outline: none; cursor: pointer; transition: background-color 0.3s ease, transform 0.2s ease; }";
  html += ".slider:hover { background: #45a049; transform: scale(1.02); }";
  html += ".slider::-webkit-slider-thumb { width: 20px; height: 20px; background: linear-gradient(to bottom, #2196F3, #1a76c1); border-radius: 50%; box-shadow: 0 4px 6px rgba(0, 0, 0, 0.3); cursor: pointer; transition: box-shadow 0.3s ease, transform 0.3s ease; }";
  html += ".slider::-webkit-slider-thumb:hover { transform: scale(1.2); box-shadow: 0 6px 10px rgba(0, 0, 0, 0.5); }";
  html += ".button { display: inline-block; padding: 15px 30px; font-size: 20px; color: white; background: linear-gradient(to right, #4CAF50, #45a049); border: none; border-radius: 30px; box-shadow: 0 8px 12px rgba(0, 0, 0, 0.2); margin: 10px; cursor: pointer; transition: transform 0.3s ease, background-color 0.3s ease, box-shadow 0.3s ease; }";
  html += ".button:hover { animation: pulse 0.8s infinite; background: #45a049; transform: scale(1.1); box-shadow: 0 10px 14px rgba(0, 0, 0, 0.3); }";
  html += "@keyframes pulse { 0% { transform: scale(1); box-shadow: 0 8px 12px rgba(0, 0, 0, 0.2); } 50% { transform: scale(1.1); box-shadow: 0 10px 14px rgba(0, 0, 0, 0.3); } 100% { transform: scale(1); box-shadow: 0 8px 12px rgba(0, 0, 0, 0.2); } }";
  html += ".footer { margin-top: 30px; color: #555; font-size: 16px; text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.2); }";
  html += "</style></head><body>";
  html += "<h1>SMART CLASSROOM</h1>";

  // Visitor Counter Section
  html += "<div class='visitor-container container'>";
  html += "<h2>Visitor Counter</h2>";
  html += "<p><strong>In:</strong> <span id='visitorsIn'>0</span></p>";
  html += "<p><strong>Out:</strong> <span id='visitorsOut'>0</span></p>";
  html += "<p><strong>Present:</strong> <span id='currentVisitors'>0</span></p>";
  html += "</div>";

  // Relay Controls Section
  html += "<div class='relay-container container'>";
  html += "<h2>Relay Controls</h2>";

  for (int i = 1; i <= 4; i++) {
    html += "<div class='relay'>";
    html += "<p><strong>Relay " + String(i) + ":</strong> OFF</p>";
    html += "<div class='slider-container'>";
    html += "<input type='range' class='slider' min='0' max='100' value='50' id='relayRange" + String(i) + "'>";
    html += "<p>Efficiency: <span id='efficiency" + String(i) + "'>50%</span></p>";
    html += "</div>";
    html += "<button class='button' onclick='toggleRelay(" + String(i) + ")'>Toggle Relay " + String(i) + "</button>";
    html += "</div>";
  }

  html += "</div>";
  html += "<div class='footer'>© SMART CLASSROOM - Designed for Efficiency</div>";
  html += "<script>";
  html += "function toggleRelay(relay) { fetch('/toggle_relay_' + relay); }";
  html += "</script>";
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
    delay(1000); // Debounce delay
  }

  // Check exit sensor
  if (digitalRead(exitSensorPin) == HIGH) {
    visitorsOut++;
    updateVisitorCount();
    delay(1000); // Debounce delay
  }
}
