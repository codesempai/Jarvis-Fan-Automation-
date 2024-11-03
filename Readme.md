# ESP8266 Fan and Light Control with Jarvis AI Integration

## Project Summary
This project involves a Python script that runs an ESP8266 web server to control a fan and light. The integration with the Jarvis AI system allows for voice command execution and other automated processes, enabling full automation of fan and light control.

## Arduino Code Explanation
The code configures an ESP8266 to act as a web server, enabling users to control a fan and light through a web interface. Users can select different fan and light levels, reset the settings to default, and send pulsed control signals.

### Key Components:
- **WiFi Setup**: The ESP8266 connects to a WiFi network using a predefined SSID and password.
- **Pin Configuration**: GPIO D1 is assigned to control the fan, and GPIO D2 is assigned to control the light.
- **Server Routes**:
  - `/`: Displays an HTML control page with buttons for setting fan and light levels.
  - `/fan_l1`, `/fan_l2`, `/fan_l3`: Set the fan to levels 1, 2, and 3 by pulsing D1.
  - `/led_l1`, `/led_l2`: Set the light to levels 1 and 2 by pulsing D2.
  - `/fan_reset`, `/light_reset`: Resets the fan/light by pulsing the pin longer.
- **Pulse Logic**: Functions like `pulsePin` and `pulsePinMultiple` handle pin pulsing to simulate different levels by changing duty cycles.
- **Main Loop**: Continuously listens for incoming web requests to execute actions accordingly.

## Python Code Explanation
This Python script allows users to make HTTP requests to control the fan and light connected to the ESP8266 microcontroller. It includes functions to select different modes for the fan, turn off the fan and light, and check the response from the ESP8266 server.

### Key Components:
- **Base URL**: The script defines a `base_url` that points to the ESP8266's IP address.
- **Control Functions**:
  - `fan_l1()`, `fan_l2()`, `fan_l3()`: Functions to set the fan to levels 1, 2, and 3, respectively.
  - `fan_reset()`: Function to reset the fan.
  - `light_l1()`, `light_l2()`: Functions to set the light to levels 1 and 2, respectively.
- **HTTP Requests**: Each function sends a GET request to the respective URL and prints the response from the ESP8266, providing feedback on the action taken.

## Installation
1. **Upload the Arduino Code**: Use the Arduino IDE to upload the provided ESP8266 code to your microcontroller.
2. **Install Python**: Ensure you have Python installed on your machine. You can download it from [python.org](https://www.python.org/).
3. **Install Requests Library**: Install the `requests` library if not already installed.
4. **Run the Python Script**: Replace `<ESP8266_IP_ADDRESS>` in the Python script with the actual IP address of your ESP8266. Run the script to control the fan and light.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
- ESP8266 Community for providing excellent libraries and documentation.
- OpenAI for the AI tools that facilitate automation.
