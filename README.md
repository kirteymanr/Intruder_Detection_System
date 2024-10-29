# Wireless Intruder Detection System Leveraging Pressure and Vibration Signatures for Unauthorized Access Detection via MQTT

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Architecture](#architecture)
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
   git clone https://github.com/kirteymanr/Intruder_Detection_System.git
   cd Intruder_Detection_System


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

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
- [MQTT Protocol](https://mqtt.org/)
- [Arduino](https://www.arduino.cc/)
- [ESP8266/ESP32](https://www.esp8266.com/)
