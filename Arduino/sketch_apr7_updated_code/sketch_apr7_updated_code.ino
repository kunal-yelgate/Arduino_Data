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
const int relayPins[] = {18, 21, 22, 23};
const int buttonPins[] = {2, 4};

// Add these variables at the top with other declarations
unsigned long lastEntryTime = 0;
unsigned long lastExitTime = 0;
const unsigned long debounceTime = 1000; // 1 second debounce period
bool entrySensorTriggered = false;
bool exitSensorTriggered = false;
int lastEntryState = LOW;
int lastExitState = LOW;

bool relayStates[] = {HIGH, HIGH, HIGH, HIGH}; // Start with relays off

// Visitor counter variables
int visitorsIn = 0;
int visitorsOut = 0;
int currentVisitors = 0;

// Speed ranges for devices
int relaySpeeds[] = {50, 50, 50, 50}; // Speed ranging for all devices (0-100)

// Create a WebServer object on port 80
WebServer server(80);

// LCD pins
const int RS = 13, EN = 12, D4 = 14, D5 = 27, D6 = 26, D7 = 25;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// IR sensor pins
const int entrySensorPin = 33;
const int exitSensorPin = 32;

String generateHTML() {
  String html = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;500;600;700&display=swap" rel="stylesheet">
    <style>
        :root {
            --primary: #4361ee;
            --primary-light: #4cc9f0;
            --secondary: #3f37c9;
            --success: #4CAF50;
            --danger: #f44336;
            --warning: #ff9800;
            --info: #2196F3;
            --light: #f8f9fa;
            --dark: #212529;
            --gray: #6c757d;
            --white: #ffffff;
        }
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            transition: all 0.3s ease;
        }
        body {
            font-family: 'Poppins', sans-serif;
            max-width: 480px;
            margin: 20px auto;
            text-align: center;
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            color: var(--dark);
            padding: 20px;
            min-height: calc(100vh - 40px);
            border-radius: 20px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);
        }
        h1 {
            font-size: 28px;
            color: var(--primary);
            margin-bottom: 25px;
            text-shadow: 1px 1px 3px rgba(0,0,0,0.1);
            position: relative;
            padding-bottom: 10px;
        }
        h1::after {
            content: '';
            position: absolute;
            bottom: 0;
            left: 50%;
            transform: translateX(-50%);
            width: 80px;
            height: 4px;
            background: linear-gradient(to right, var(--primary), var(--primary-light));
            border-radius: 2px;
        }
        .section {
            margin-bottom: 25px;
            padding: 20px;
            border: none;
            border-radius: 15px;
            background: var(--white);
            box-shadow: 0 5px 15px rgba(0, 0, 0, 0.05);
            transition: all 0.3s ease;
            position: relative;
            overflow: hidden;
        }
        .section::before {
            content: '';
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 5px;
            background: linear-gradient(90deg, var(--primary), var(--primary-light));
        }
        .section:hover {
            transform: translateY(-5px);
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.1);
        }
        .section p {
            margin-bottom: 15px;
            font-size: 16px;
            color: var(--dark);
        }
        .section p strong {
            color: var(--primary);
        }
        .button {
            display: block;
            width: 80%;
            margin: 15px auto;
            padding: 15px;
            font-size: 16px;
            font-weight: 600;
            color: white;
            background: linear-gradient(135deg, var(--success) 0%, #45a049 100%);
            border: none;
            border-radius: 30px;
            box-shadow: 0 5px 15px rgba(76, 175, 80, 0.3);
            cursor: pointer;
            position: relative;
            overflow: hidden;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        .button.off {
            background: linear-gradient(135deg, var(--danger) 0%, #d32f2f 100%);
            box-shadow: 0 5px 15px rgba(244, 67, 54, 0.3);
        }
        .button:hover {
            transform: translateY(-3px) scale(1.02);
            box-shadow: 0 8px 20px rgba(76, 175, 80, 0.4);
        }
        .button.off:hover {
            box-shadow: 0 8px 20px rgba(244, 67, 54, 0.4);
        }
        .slider-container {
            margin-top: 20px;
            padding: 0 10px;
        }
        .slider-label {
            display: flex;
            justify-content: space-between;
            margin-bottom: 8px;
            font-size: 14px;
            color: var(--gray);
        }
        .slider {
            display: block;
            width: 100%;
            margin: 10px auto;
            height: 8px;
            -webkit-appearance: none;
            background: linear-gradient(90deg, var(--primary) 0%, var(--primary-light) 100%);
            border-radius: 10px;
            outline: none;
        }
        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 22px;
            height: 22px;
            border-radius: 50%;
            background: var(--white);
            cursor: pointer;
            border: 3px solid var(--primary);
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.2);
        }
        .value-display {
            font-size: 16px;
            font-weight: 600;
            color: var(--primary);
            display: inline-block;
            min-width: 40px;
        }
        .refresh {
            background: linear-gradient(135deg, var(--info) 0%, #1976D2 100%);
            padding: 15px 30px;
            margin: 25px auto;
            color: white;
            font-size: 16px;
            font-weight: 600;
            border: none;
            border-radius: 30px;
            box-shadow: 0 5px 15px rgba(33, 150, 243, 0.3);
            cursor: pointer;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        .footer {
            margin-top: 30px;
            color: var(--gray);
            font-size: 14px;
            font-style: italic;
        }
        .status-indicator {
            display: inline-block;
            width: 12px;
            height: 12px;
            border-radius: 50%;
            margin-right: 8px;
            background-color: var(--gray);
        }
        .status-indicator.on {
            background-color: var(--success);
            box-shadow: 0 0 10px rgba(76, 175, 80, 0.7);
        }
        .status-indicator.off {
            background-color: var(--danger);
        }
        .pulse {
            animation: pulse 2s infinite;
        }
        @keyframes pulse {
            0% { transform: scale(1); }
            50% { transform: scale(1.05); }
            100% { transform: scale(1); }
        }
        @media (max-width: 400px) {
            body {
                margin: 10px auto;
                padding: 15px;
            }
            .section {
                padding: 15px;
            }
            .button, .refresh {
                padding: 12px;
                font-size: 14px;
            }
        }
    </style>
</head>
<body>
    <h1>SMART CLASSROOM</h1>
    <div class="section">
        <p><strong>PRESENT:</strong> <span class="pulse">)=====";
  html += String(currentVisitors);
  html += R"=====(</span></p>
        <p><strong>IN:</strong> )=====";
  html += String(visitorsIn);
  html += R"=====(</p>
        <p><strong>OUT:</strong> )=====";
  html += String(visitorsOut);
  html += R"=====(</p>
    </div>)=====";

  // Generate device sections
  String deviceNames[] = {"BULB", "BULB 2", "FAN 1", "FAN 2"};
  String sliderLabels[] = {"Brightness", "Brightness", "Speed", "Speed"};
  
  for (int i = 0; i < 4; i++) {
    bool isOn = relayStates[i] == LOW;
    html += R"=====(
    <div class="section">
        <p><span class="status-indicator )=====";
    html += isOn ? "on" : "off";
    html += R"=====("></span>Relay )=====";
    html += String(i+1);
    html += ": ";
    html += isOn ? "ON" : "OFF";
    html += R"=====(</p>
        <form action="/toggle_relay_)=====";
    html += String(i);
    html += R"=====(" method="GET">
            <button class="button )=====";
    html += isOn ? "off" : "";
    html += R"=====(" type="submit">)=====";
    html += deviceNames[i];
    html += R"=====(</button>
        </form>)=====";
    
    // Add slider for each device
    html += R"=====(
        <div class="slider-container">
            <div class="slider-label">
                <span>)=====";
    html += sliderLabels[i];
    html += R"=====(</span>
                <span><span id="speedValue)=====";
    html += String(i+1);
    html += R"=====(" class="value-display">)=====";
    html += String(relaySpeeds[i]);
    html += R"=====(</span>%</span>
            </div>
            <input id="relay)=====";
    html += String(i+1);
    html += R"=====(Speed" type="range" min="0" max="100" value=")=====";
    html += String(relaySpeeds[i]);
    html += R"=====(" class="slider" oninput="updateValue('speedValue)=====";
    html += String(i+1);
    html += R"=====(', this.value)">
        </div>
    </div>)=====";
  }

  // Refresh button and footer
  html += R"=====(
    <form action="/refresh" method="GET">
        <button class="refresh" type="submit">Refresh Status</button>
    </form>
    <div class="footer">&copy; SMART CLASSROOM - Designed for Efficiency</div>
    <script>
        function updateValue(spanId, value) {
            const element = document.getElementById(spanId);
            element.textContent = value;
            element.style.transform = 'scale(1.2)';
            element.style.color = '#f44336';
            setTimeout(() => {
                element.style.transform = 'scale(1)';
                element.style.color = '#4361ee';
            }, 300);
            
            // Send the updated value to the server
            const relayNum = spanId.replace('speedValue', '');
            fetch('/set_relay_speed_' + relayNum, {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: 'value=' + value
            });
        }
        
        document.querySelectorAll('.button, .refresh').forEach(button => {
            button.addEventListener('click', function() {
                this.style.transform = 'translateY(3px)';
                setTimeout(() => {
                    this.style.transform = '';
                }, 200);
            });
        });
    </script>
</body>
</html>)=====";

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

// Handle speed changes
void handleSpeedChange(int relayIndex, int speed) {
  relaySpeeds[relayIndex] = speed;
  // Here you would implement actual PWM control for the relays
  // For example: analogWrite(relayPins[relayIndex], map(speed, 0, 100, 0, 255));
}

// Setup server routes
void setupServerRoutes() {
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generateHTML());
  });

  // Toggle relay routes
  for (int i = 0; i < 4; i++) {
    int relayIndex = i;
    server.on(("/toggle_relay_" + String(i)).c_str(), HTTP_GET, [relayIndex]() {
      toggleRelay(relayIndex);
      server.send(200, "text/html", generateHTML());
    });
  }

  // Speed control routes
  for (int i = 0; i < 4; i++) {
    int relayIndex = i;
    server.on(("/set_relay_speed_" + String(i+1)).c_str(), HTTP_POST, [relayIndex]() {
      if (server.hasArg("value")) {
        int speed = server.arg("value").toInt();
        handleSpeedChange(relayIndex, speed);
      }
      server.send(200, "text/plain", "OK");
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

  // Read current sensor states
  int currentEntryState = digitalRead(entrySensorPin);
  int currentExitState = digitalRead(exitSensorPin);

  // Entry sensor logic - detects rising edge (LOW to HIGH transition)
  if (currentEntryState != lastEntryState) {
    if (currentEntryState == HIGH) {
      if (!entrySensorTriggered && millis() - lastEntryTime > debounceTime) {
        visitorsIn++;
        updateVisitorCount();
        entrySensorTriggered = true;
        lastEntryTime = millis();
        Serial.println("Person entered - Count: " + String(currentVisitors));
      }
    } else {
      entrySensorTriggered = false;
    }
    lastEntryState = currentEntryState;
  }

  // Exit sensor logic - detects rising edge (LOW to HIGH transition)
  if (currentExitState != lastExitState) {
    if (currentExitState == HIGH) {
      if (!exitSensorTriggered && millis() - lastExitTime > debounceTime) {
        // Only count exit if there are people inside
        if (currentVisitors > 0) {
          visitorsOut++;
          updateVisitorCount();
          exitSensorTriggered = true;
          lastExitTime = millis();
          Serial.println("Person exited - Count: " + String(currentVisitors));
        }
      }
    } else {
      exitSensorTriggered = false;
    }
    lastExitState = currentExitState;
  }

  // Prevent negative visitor count
  if (currentVisitors < 0) {
    currentVisitors = 0;
    updateVisitorCount();
  }
}