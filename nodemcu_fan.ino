#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Code_2.4Ghz";         // Replace with your WiFi SSID
const char* password = "code95187";       // Replace with your WiFi password

ESP8266WebServer server(80); // Create a web server object on port 80

// Pin definitions
const int pin_fan = D1;  // Define pin D2 for Light control
const int pin_light = D2;  // Define pin D1 for Fan control

// Variables to store the current level
int fanLevel = 0;
int lightLevel = 0;

// Constants for delay times
const int pulseTime = 500;  // 500ms pulse // simulate click on button for 0.5 sec
const int resetTime = 2000; // 2000ms reset // when long press on button the fan/light turn off

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  
  // Set the control pins as outputs
  pinMode(pin_light, OUTPUT);
  pinMode(pin_fan, OUTPUT);

  // Initialize both pins to LOW
  digitalWrite(pin_light, LOW);
  digitalWrite(pin_fan, LOW);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Set up the web server routes
  server.on("/", handleRoot);                // Define the route for root URL
  server.on("/fan", handleFan);              // Define the route for controlling the Fan
  server.on("/light", handleLight);          // Define the route for controlling the Light
  server.on("/fan_reset", Fan_reset);        // Define the route for resetting the Fan

  server.on("/fan_l1", [](){ setFanLevel(1); });  // Fan Level 1
  server.on("/fan_l2", [](){ setFanLevel(2); });  // Fan Level 2
  server.on("/fan_l3", [](){ setFanLevel(3); });  // Fan Level 3

  server.on("/light_reset", Light_reset);        // Define the route for resetting the Light
  server.on("/led_l1", [](){ setLightLevel(1); }); // Light Level 1
  server.on("/led_l2", [](){ setLightLevel(2); }); // Light Level 2

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}
void handleRoot() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control Fan and Light</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            background-color: #e9ecef;
            margin: 0;
            padding: 20px;
        }

        h1 {
            margin-bottom: 20px;
            color: #343a40;
        }

        .container {
            display: grid;
            grid-template-columns: 1fr;
            grid-gap: 20px;
            max-width: 400px;
            margin: 0 auto;
        }

        .button-row {
            display: flex;
            justify-content: space-between;
            gap: 15px;
        }

        button {
            width: 100%;
            padding: 12px;
            font-size: 16px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        button:hover {
            background-color: #0056b3;
            box-shadow: 0 6px 8px rgba(0, 0, 0, 0.2);
        }

        .fan-button {
            background-color: #17a2b8;
        }

        .fan-button:hover {
            background-color: #138496;
        }

        #status {
            margin-top: 20px;
            font-size: 18px;
            color: #495057;
            font-weight: bold;
        }
    </style>
</head>
<body>

    <h1>Fan Control</h1>

    <div class="container">
        <div class="button-row">
            <button class="fan-button" onclick="sendRequest('/fan_l1')">FAN_L1</button>
            <button class="fan-button" onclick="sendRequest('/fan_l2')">FAN_L2</button>
            <button class="fan-button" onclick="sendRequest('/fan_l3')">FAN_L3</button>
        </div>
        <div><button class="fan-button" onclick="sendRequest('/fan_reset')">Pulse Fan reset (D1 for 2000ms)</button></div>
    
        <h1>Light Control</h1>

        <div class="button-row">
            <button onclick="sendRequest('/led_l1')">LED_L1</button>
            <button onclick="sendRequest('/led_l2')">LED_L2</button>
        </div>
        <div><button onclick="sendRequest('/light_reset')">Pulse Light reset (D2 for 2000ms)</button></div>
    </div>

    <p id="status"></p>


    <script>
        function sendRequest(url) {
            var xhr = new XMLHttpRequest();
            xhr.open('GET', url, true);
            xhr.onreadystatechange = function () {
                if (xhr.readyState == 4 && xhr.status == 200) {
                    document.getElementById('status').innerHTML = xhr.responseText;
                }
            };
            xhr.send();
        }
    </script>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", page);
}










void handleFan() {
  pulsePin(pin_light, pulseTime);
  server.send(200, "text/plain", "Fan was pulsed for 500 milliseconds");
}

void Fan_reset() {
  resetPin(pin_light, resetTime);
  fanLevel = 0;  // Reset the fan level
  server.send(200, "text/plain", "Fan was reset for 2000 milliseconds");
}

void setFanLevel(int level) {
  if (level != fanLevel) {
    if (level == 0) {
      Fan_reset();
    } else {
      int diff = level - fanLevel;
      if (diff > 0) {
        pulsePinMultiple(pin_light, diff, pulseTime);
      } else {
        Fan_reset();
        pulsePinMultiple(pin_light, level, pulseTime);
      }
      fanLevel = level;
    }
  }
  server.send(200, "text/plain", "Fan set to level " + String(level));
}

void handleLight() {
  pulsePin(pin_fan, pulseTime);
  server.send(200, "text/plain", "Light was pulsed for 500 milliseconds");
}

void Light_reset() {
  resetPin(pin_fan, resetTime);
  lightLevel = 0;  // Reset the light level
  server.send(200, "text/plain", "Light was reset for 2000 milliseconds");
}

void setLightLevel(int level) {
  if (level != lightLevel) {
    if (level == 0) {
      Light_reset();
    } else {
      int diff = level - lightLevel;
      if (diff > 0) {
        pulsePinMultiple(pin_fan, diff, pulseTime);
      } else {
        Light_reset();
        pulsePinMultiple(pin_fan, level, pulseTime);
      }
      lightLevel = level;
    }
  }
  server.send(200, "text/plain", "Light set to level " + String(level));
}

void pulsePin(int pin, int time) {
  digitalWrite(pin, HIGH);
  delay(time);
  digitalWrite(pin, LOW);
}

void resetPin(int pin, int time) {
  pulsePin(pin, time);
  delay(time); // Delay after resetting
}

void pulsePinMultiple(int pin, int count, int time) {
  for (int i = 0; i < count; i++) {
    pulsePin(pin, time);
    delay(time); // Optional delay between pulses
  }
}

void loop() {
  server.handleClient(); // Continuously listen for client requests
}
