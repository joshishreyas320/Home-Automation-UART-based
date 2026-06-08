# Bluetooth Home Automation System

### Arduino UNO + HC-05 | Relay Control via Smartphone

---

## Project Overview

This project implements a Bluetooth-based Home Automation System using an Arduino UNO and HC-05 Bluetooth module. Three household loads — a Lamp, a Motor, and an LED — are controlled wirelessly through a smartphone application such as MIT App Inventor or Serial Bluetooth Terminal.

Each load is driven through a 2N2222 transistor-based relay driver circuit, providing safe isolation between the microcontroller and high-power loads. The project was designed and verified using Proteus 8 simulation and compiled for the Arduino Nano (ATmega328P) target.

---

## Hardware Components

| Component        | Specification            | Quantity |
| ---------------- | ------------------------ | -------- |
| Microcontroller  | Arduino UNO (ATmega328P) | 1        |
| Bluetooth Module | HC-05 (UART, 9600 baud)  | 1        |
| Relay Module     | 5V Relay (SPDT)          | 3        |
| NPN Transistor   | 2N2222 Relay Driver      | 3        |
| Load 1           | Lamp / Bulb              | 1        |
| Load 2           | DC Motor                 | 1        |
| Load 3           | Yellow LED               | 1        |
| Flyback Diode    | 1N4007                   | 3        |
| Resistor         | 1kΩ Base Resistor        | 3        |
| Power Supply     | 5V DC                    | 1        |

---

## Pin Configuration

| Arduino Pin | Connected To       | Function           |
| ----------- | ------------------ | ------------------ |
| Pin 0 (RX)  | HC-05 TX           | Bluetooth Receive  |
| Pin 1 (TX)  | HC-05 RX           | Bluetooth Transmit |
| Pin 13      | Relay 1 via 2N2222 | Lamp Control       |
| Pin 12      | Relay 2 via 2N2222 | Motor Control      |
| Pin 7       | Relay 3 via 2N2222 | LED Control        |
| 5V / GND    | HC-05 VCC/GND      | Power Supply       |

---

## Command Set

| Command | Action          |
| ------- | --------------- |
| 1       | Lamp ON         |
| 0       | Lamp OFF        |
| T       | Lamp Toggle     |
| 2       | Motor ON        |
| 3       | Motor OFF       |
| U       | Motor Toggle    |
| 4       | LED ON          |
| 5       | LED OFF         |
| V       | LED Toggle      |
| A       | All Devices ON  |
| X       | All Devices OFF |
| S       | Status Report   |

---

## Project Structure

Home_Automation_Arduino/

├── D3_Home_Automation/

│   └── D3_Home_Automation/

│       ├── D3_Home_Automation.ino

│       └── build/arduino.avr.nano/

│           ├── D3_Home_Automation.ino.hex

│           ├── D3_Home_Automation.ino.elf

│           └── D3_Home_Automation.ino.with_bootloader.bin

├── home_automation_Arduino.pdsprj

└── Backup Of home_automation_Arduino.pdsbak

---

## How It Works

1. The HC-05 Bluetooth module receives character commands from the smartphone over UART communication at 9600 baud.

2. The Arduino continuously checks for incoming data using Serial.available() and reads commands using Serial.read().

3. The handleCommand() function decodes the received command and determines which device should be controlled.

4. The setRelay(pin, state) function drives the corresponding GPIO pin HIGH or LOW.

5. The GPIO output controls the 2N2222 transistor, which energizes or de-energizes the relay coil.

6. State variables such as lampState, motorState, and ledState keep track of the current device status.

---

## Circuit Working – Relay Driver

Signal Flow:

Arduino GPIO (HIGH)

↓

1kΩ Base Resistor

↓

2N2222 Base

↓

Relay Coil (+5V)

↓

Ground (Emitter)

### Operation

* GPIO HIGH → 2N2222 saturates → Relay coil energized → Load turns ON
* GPIO LOW → 2N2222 turns OFF → Relay coil de-energized → Load turns OFF
* 1N4007 flyback diode across the relay coil protects the transistor from inductive voltage spikes

---

## Firmware Highlights

Relay Assignments:

RELAY_LAMP = Pin 13

RELAY_MOTOR = Pin 12

RELAY_LED = Pin 7

Program Flow:

* Wait for incoming Bluetooth command
* Read command character
* Execute corresponding action
* Update relay state
* Maintain device status variables

Relay Control Function:

digitalWrite(pin, state ? HIGH : LOW)

---

## Software & Tools

| Tool                         | Purpose                                |
| ---------------------------- | -------------------------------------- |
| Arduino IDE                  | Firmware Development                   |
| Proteus 8                    | Circuit Simulation                     |
| HC-05 + Serial Bluetooth App | Wireless Control                       |
| MIT App Inventor             | Custom Android Application Development |

---

## How to Run

### Simulation (Proteus)

1. Open `home_automation_Arduino.pdsprj` in Proteus 8.
2. Load the HEX file from the `build/arduino.avr.nano/` folder into the Arduino component.
3. Run the simulation.
4. Use the Virtual Terminal to send commands and observe relay operation.

### Hardware

1. Upload `D3_Home_Automation.ino` to the Arduino UNO using Arduino IDE.
2. Connect the HC-05 Bluetooth module to the Arduino UART pins.
3. Pair the HC-05 with a smartphone using PIN `1234` or `0000`.
4. Open Serial Bluetooth Terminal or a custom MIT App Inventor application.
5. Send commands according to the Command Set table.
6. Observe the corresponding load switching action.

---

## Features

* Individual ON/OFF control for Lamp, Motor, and LED
* Toggle command support for each device
* Master ALL ON and ALL OFF commands
* Real-time status reporting using the S command
* Device state tracking to prevent unnecessary relay switching
* Proteus simulation verified
* Active HIGH relay driver using 2N2222 NPN transistors
* Smartphone-based wireless control through Bluetooth

---

## Author

**Shreyas Joshi**

Electronics & Embedded Systems Engineer

Maharashtra, India

---

## License

Educational and Portfolio Use Only.
