# PTSolns *I2Connect: MUX* Library

![Arduino Library](https://img.shields.io/badge/Arduino-Library-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Utility](https://img.shields.io/badge/Utility-Multiplexer-orange)

Library for the PTSolns *I2Connect: MUX* module. Available through both the Arduino Library Manager and the PTSolns IDE Library Manager, this library provides an abstracted, user-friendly interface to control hardware routing and instantly resolve I2C address conflicts.

---

## Overview

The *I2Connect: MUX* is a 4-channel I2C multiplexer module designed to effortlessly resolve address collisions on the I2C bus. Because the I2C protocol relies on unique addressing, connecting two identical sensors (e.g., two displays hardcoded to 0x3C) to the same microcontroller will cause data corruption. The MUX solves this by acting as a digital gatekeeper, allowing you to branch your primary I2C bus into four independent, isolated downstream channels labeled MUX1 through MUX4.

The module automatically handles logic level shifting and is fully compatible with both 3.3V and 5V systems. The included library abstracts the internal hardware routing of the multiplexer IC, allowing you to simply command the library to "open MUX2" and communicate with whatever is attached to that specific port.

Like all I2Connect modules, it connects using standard Qwiic® compatible connectors. It provides two main I2C input ports for daisy-chaining upstream, and four downstream expansion ports (MUX1 - MUX4). It also features a preinstalled right-angle header for standard breadboard use.

---

## *I2Connect* Series

The PTSolns *I2Connect* Series is a family of plug and play expansion modules designed to simplify the integration of sensors, displays, user interfaces, and other peripherals into embedded systems. Built around the industry standard I2C communication protocol and featuring convenient Qwiic® compatible connectors (4 pin, 1 mm JST SH), *I2Connect* modules can be quickly connected without soldering or complex wiring.

Each module is fully assembled and includes a preinstalled male header that is compatible with standard solderless breadboards, enabling immediate use and rapid prototyping. Designed to work seamlessly with a wide range of microcontroller platforms, I2Connect modules combine compact hardware, comprehensive documentation, and easy to use software libraries. The _I2Connect_ Series enables makers, students, educators, and professionals to rapidly prototype, evaluate, and develop reliable electronic systems.

The following modules are part of the *I2Connect* Series:

- [**AHT20**](https://ptsolns.com/products/i2connect-aht20) — Temperature & Humidity
- [**VEML7700**](https://ptsolns.com/products/i2connect-veml7700) — Light & Lux
- [**EEPROM**](https://ptsolns.com/products/i2connect-eeprom) — 2 Mbit Memory
- **Buttons** — User Input via 4×4 Matrix of Buttons
- **Digit Display** — Dual 7 Segment Display
- **ICP-20100** — Pressure & Temperature
- **KXTJ3-1057** — 3 Axis Accelerometer
- **MUX** — 4 Channel I2C Multiplexer
- **OLED** — 0.96" 128×64 OLED Display
- **I2C Doctor** — I2C Bus Recovery and Diagnostics
- **...and more!**

---

## Key Features

- 4 isolated downstream I2C channels (MUX1 to MUX4).
- Resolves address conflicts for identical I2C components.
- Default I2C address of 0x70.
- Configurable hardware addresses (0x70 through 0x77) via solder jumpers.
- 3.3V and 5V logic and power compatibility.
- 6x Qwiic® compatible 4-pin JST SH connectors (2 input, 4 output).
- Breadboard-friendly 4-pin 2.54mm angled male header (VCC, GND, SDA, SCL).
- Switchable main I2C pullup resistors via solder jumper.

---

## I2Connect Ecosystem

The *I2Connect: MUX* is part of the PTSolns I2Connect ecosystem.

All *I2Connect* modules utilize a standardized 4 pin JST SH 1.0 mm connector carrying:

| Pin | Function |
| --- | -------- |
| 1   | GND      |
| 2   | VCC      |
| 3   | SDA      |
| 4   | SCL      |

This connector follows the widely adopted Qwiic® standard, allowing modules and compatible boards to be connected without soldering.

For maximum compatibility, the module also includes a preinstalled angled male header, allowing use with virtually any 3.3 V or 5 V microcontroller platform even when a Qwiic compatible connector is unavailable.

---

## MUX Specifications

| Parameter               | Value                               |
| ----------------------- | ----------------------------------- |
| Downstream Channels     | 4 (MUX1, MUX2, MUX3, MUX4)          |
| Interface               | I2C                                 |
| I2C Address             | 0x70 (Default)                      |
| Operating Voltage       | 3.3 V / 5 V Rated                   |
| Connectors              | 6x 4-pin 1mm JST SH, 1x 4-pin Header|

---

## I2C Addressing & Multiplexing

The *I2Connect: MUX* module uses a default I2C address of:

```text
0x70
```
This address can be modified from 0x70 up to 0x77 by closing the A0, A1, and A2 solder jumpers located on the back of the PCB.

By changing these hardware jumpers, up to eight MUX boards can be daisy-chained onto a single main I2C bus, expanding a single microcontroller to support up to 32 isolated downstream channels.

---

## *PTSolns IDE*

The [*PTSolns IDE*](https://ptsolns.com/ide) is a free desktop application for programming PTSolns microcontroller development boards and compatible Arduino platforms.

This library is available directly through both the PTSolns IDE Library Manager and the Arduino Library Manager.

To install:

1. Open the PTSolns IDE (or Arduino IDE).
2. Open the Library Manager.
3. Search for:

```text
I2Connect_MUX
```
4. Click Install.

Features of the [*PTSolns IDE*](https://ptsolns.com/ide) include:

* Integrated board management
* Built in serial monitor
* Library management
* Example project browser
* Support for over 8,500 third party libraries
* Built in CH340 USB driver support
* Open source and community driven

The [*PTSolns IDE*](https://ptsolns.com/ide) can be used alongside the Arduino IDE and supports many PTSolns development boards out of the box.

---

## Quick Start

```cpp
#include <Wire.h>
#include <PTSolns_I2Connect_MUX.h>

PTSolns_I2Connect_MUX mux;
const uint8_t SENSOR_ADDRESS = 0x3C; // Example OLED address

void setup()
{
    Serial.begin(115200);
    Wire.begin();

    if (mux.begin()) {
        Serial.println("MUX initialized!");
    } else {
        Serial.println("Failed to find MUX.");
        while(1);
    }
}

void loop()
{
    // Talk to the screen attached to MUX1
    mux.setPort(1);
    Wire.beginTransmission(SENSOR_ADDRESS);
    // ... send data to display 1 ...
    Wire.endTransmission();
    
    // Switch over and talk to the screen attached to MUX2
    mux.setPort(2);
    Wire.beginTransmission(SENSOR_ADDRESS);
    // ... send data to display 2 ...
    Wire.endTransmission();
    
    delay(100);
}
```

---
## Basic Functions

Initialization

```cpp
// Initializes MUX at default address 0x70 and closes all ports
mux.begin();
```
Routing I2C Traffic
```cpp
// Open the MUX3 port for downstream communication
mux.setPort(3);

// Secure the main bus by disconnecting all downstream modules
mux.disableAllPorts();
```
