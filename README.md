# Wireless Intruder Detection System Leveraging Pressure and Vibration Signatures for Unauthorized Access Detection via MQTT

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Introduction
The Intruder Detection System is a wireless security solution designed to detect unauthorized access to a designated area. Utilizing a grid of pressure sensors and a geophone sensor, the system provides real-time alerts to ensure safety and security in residential and commercial environments.

## Features
- Real-time monitoring and alerting
- Wireless communication using MQTT protocol
- Utilizes pressure sensors and geophone sensor for accurate detection
- Easy installation and setup
- User-friendly interface for monitoring and control

## Hardware Requirements
- Pressure sensors (as many as needed for the grid)
- Geophone sensor
- Microcontroller (e.g., Arduino, Raspberry Pi)
- Wi-Fi module (e.g., ESP8266, ESP32)
- Power supply (batteries or USB power)
- Jumper wires and a breadboard (for prototyping)
- Optional: enclosure for housing the components

## Software Requirements
- Arduino IDE (for microcontroller programming)
- MQTT broker (e.g., Mosquitto)
- Any MQTT client for monitoring (e.g., MQTT.fx, MQTT Explorer)
- Libraries:
  - PubSubClient for MQTT
  - Adafruit Sensor libraries (if using specific sensors)

## Installation
1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/intruder-detection-system.git
   cd intruder-detection-system

## Set up the Hardware
- Connect the pressure sensors and geophone sensor to the microcontroller according to the circuit diagram provided in the repository.

## Install Required Libraries
- Open the Arduino IDE and install the required libraries through the Library Manager.

## Upload the Code
1. Open the `main.ino` file in the Arduino IDE.
2. Update the Wi-Fi credentials and MQTT broker details in the code.
3. Upload the code to the microcontroller.

## Start the MQTT Broker
- If using Mosquitto, follow the installation instructions on the Mosquitto website and start the broker.

## Usage
1. Power the system on. The sensors will start detecting any pressure or vibrations in the area.
2. The system will publish alerts to the MQTT broker when an intrusion is detected.
3. Use an MQTT client to subscribe to the relevant topic and monitor the alerts in real time.

## Architecture
The system architecture consists of:
- **Sensor Layer**: Pressure and geophone sensors for detecting intrusions.
- **Controller Layer**: Microcontroller to process sensor data and communicate with the MQTT broker.
- **Communication Layer**: Wi-Fi module for sending alerts and receiving commands.
- **User Interface**: MQTT client to receive and visualize alerts.

## Contributing
Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- [MQTT Protocol](https://mqtt.org/)
- [Arduino](https://www.arduino.cc/)
- [ESP8266/ESP32](https://www.esp8266.com/)
