# Intruder Detection System using Geophone Sensor

## Introduction
This project utilizes a **Geophone sensor**, a seismic sensor that detects ground vibrations, to identify the footsteps of individuals in its vicinity. Typically installed underground, the geophone sensor captures seismic activity, which can indicate a person's approach. The primary objective is to detect unauthorized individuals entering a restricted area.

## Hardware Used
1. **Geophone Sensor**: A seismic sensor that converts ground vibrations into voltage for detection.
2. **Raspberry Pi**: Processes incoming data from the sensor.
3. **ADC (ADS1115)**: Converts the analog signal from the geophone sensor into a digital signal for the Raspberry Pi to process.
   - **Configuration**: 16-bit, 4-channel ADC

## Circuit Diagram
Please refer to the circuit diagram provided in the repository for proper hardware connections.

## Code Overview
### Library Imports
The following libraries are used in the project:
- `matplotlib`, `scipy`, `numpy`, `telepot`, and `RPi.GPIO`
- These libraries support data analysis, sensor data processing, and messaging functionalities.

### GPIO Port and LED Setup
The system uses LEDs to indicate network status:
- **Three LED blinks**: Raspberry Pi is connected to the internet.
- **LED remains ON**: No internet connection.
- **Single LED blink per detection**: Indicates step detection after network testing.

### Telegram Bot Notifications
A **Telegram bot** is integrated to notify the user when an intruder is detected. The bot sends a message to a specified chat ID.

### ADC Configuration
The ADC is configured to:
- Address: `0x48`
- Gain: `16`
- Data rate: `128`

### Sensing
The system records and processes vibrations to detect footsteps. For each detected vibration, the system:
1. Reads the differential input from the ADC.
2. Calculates the kurtosis of the signal.
3. If the kurtosis exceeds a threshold, an intruder alert is triggered.

## Installation
1. **Clone the repository** and set up the circuit according to the diagram.
2. **Install required libraries** using pip:
   ```bash
   pip install matplotlib numpy scipy telepot RPi.GPIO
