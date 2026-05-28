#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "SMART CLASSROOM";
const char* password = "987654321";
const int ledPins[] = {2, 15, 4, 5}; // Pins for four LEDs
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);

WebSocketsServer webSocket = WebSocketsServer(81);
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
 <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SMART CLASSROOM</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #b1e2f3;
            margin: 0;
            padding: 0;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
        }
        .container {
            width: 300px;
            margin: 20px;
            padding: 20px;
            background: #ffffff;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            border-radius: 10px;
            text-align: center;
        }
        .container h3 {
            margin-bottom: 15px;
            color: #333;
        }
        .btn {
            padding: 10px 20px;
            font-size: 16px;
            border: none;
            border-radius: 5px;
            background-color: #4caf50;
            color: white;
            cursor: pointer;
            margin: 10px 0;
        }
        .btn.off {
            background-color: #f44336;
        }
        .btn:disabled {
            background-color: #d3d3d3;
            cursor: not-allowed;
        }
        .slider {
            width: 100%;
            margin: 10px 0;
        }
        .value-display {
            font-size: 16px;
            color: #555;
            margin-top: 10px;
        }
        h1{
            color: orange;
        }
</style>
</head>
<body>
    <div  class="container">
        <h1>SMART CLASSROOM</h1>
    </div>
    <div class="container">
        <h3>Bulb 1</h3>
        <button class="btn" id="btn1" onclick="toggleSwitch(1)">Turn Off</button>
        <input type="range" class="slider" id="slider1" min="0" max="100" value="50">
        <div class="value-display">Value: <span id="value1">90</span></div>
    </div>

    <div class="container">
        <h3>Bulb 2</h3>
        <button class="btn" id="btn2" onclick="toggleSwitch(2)">Turn Off</button>
        <input type="range" class="slider" id="slider2" min="0" max="100" value="50">
        <div class="value-display">Value: <span id="value2">90</span></div>
    </div>

    <div class="container">
        <h3>Fan 1</h3>
        <button class="btn" id="btn3" onclick="toggleSwitch(3)">Turn Off</button>
        <input type="range" class="slider" id="slider3" min="0" max="100" value="50">
        <div class="value-display">Value: <span id="value3">50</span></div>
    </div>

    <div class="container">
        <h3>Fan 2</h3>
        <button class="btn" id="btn4" onclick="toggleSwitch(4)">Turn Off</button>
        <input type="range" class="slider" id="slider4" min="0" max="100" value="50">
        <div class="value-display">Value: <span id="value4">50</span></div>
    </div>

    <script>
        function toggleSwitch(num) {
            const button = document.getElementById(`btn${num}`);
            const slider = document.getElementById(`slider${num}`);

            if (button.textContent === "Turn Off") {
                button.textContent = "Turn On";
                button.classList.add('off');
                slider.disabled = true;
            } else {
                button.textContent = "Turn Off";
                button.classList.remove('off');
                slider.disabled = false;
            }
        }

        document.querySelectorAll('.slider').forEach((slider, index) => {
            slider.addEventListener('input', () => {
                document.getElementById(`value${index + 1}`).textContent = slider.value;
            });
        });
        var ws = new WebSocket('ws://' + window.location.hostname + ':81/');
        var buttons = document.querySelectorAll('.toggleButton');
        var statuses = [document.getElementById('status1'), document.getElementById('status2'), document.getElementById('status3'), document.getElementById('status4')];
        
        buttons.forEach((button, index) => {
            button.addEventListener('change', function() {
                var state = button.checked ? '1' : '0';
                ws.send(state + index); // Send the state along with the LED index
            });
        });

        ws.onmessage = function(event) {
            var data = event.data;
            var state = data.substring(0, 1);
            var index = parseInt(data.substring(1));
            statuses[index].textContent = state === '1' ? 'ON' : 'OFF';
        };
    </script>
 </body>
</html>

)rawliteral";
void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.begin();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    int index = payload[length - 1] - '0'; // Convert char to int
    if (index >= 0 && index < numLEDs) {
      if (payload[0] == '1') {
        digitalWrite(ledPins[index], HIGH);
      } else {
        digitalWrite(ledPins[index], LOW);
      }
    }
  }
}

void loop() {
  webSocket.loop();
}
