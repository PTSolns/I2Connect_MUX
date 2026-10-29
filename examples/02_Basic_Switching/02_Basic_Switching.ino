// Example: Basic Port Switching for I2Connect: MUX
// Last Update: October 23, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Demonstrates how to switch between all four MUX ports to communicate with 
// multiple devices that share the exact same I2C address.
//
// SKILLS LEARNED
// setPort()
// disableAllPorts()
//
// DESCRIPTION
// The primary purpose of an I2C multiplexer is to resolve address conflicts. 
// If you have four identical OLED displays (all hardcoded to 0x3C), you cannot 
// connect them to the same standard I2C bus. By placing one display on each 
// MUX port (MUX1 through MUX4), you can talk to them independently simply by 
// changing the active port before sending your commands.

#include <Wire.h>
#include <PTSolns_I2Connect_MUX.h>

// User Settings
const uint32_t SERIAL_BAUD  = 115200; 
const uint8_t  MUX_ADDRESS  = 0x70;   

// Imagine we have identical sensors attached to the MUX ports, all sharing address 0x59
const uint8_t SENSOR_ADDRESS = 0x59; 

PTSolns_I2Connect_MUX mux;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) { }

    Wire.begin();
    
    if (!mux.begin(Wire, MUX_ADDRESS)) {
        Serial.println("I2Connect MUX not detected. Check wiring.");
        while (1) { } 
    }
    
    Serial.println("MUX initialized.");
    Serial.println("----------------------------------------");
}

void loop() {
    // Loop through all four physical ports on the board (MUX1 to MUX4)
    for (uint8_t port = 1; port <= 4; port++) {
        
        Serial.print("Switching to MUX");
        Serial.print(port);
        Serial.println("...");
        
        // Open the specific port
        mux.setPort(port); 
        
        // Any standard I2C commands now route exclusively down this specific branch
        Wire.beginTransmission(SENSOR_ADDRESS);
        if (Wire.endTransmission() == 0) {
            Serial.print(" -> Successfully communicated with device on MUX");
            Serial.println(port);
        } else {
            Serial.print(" -> No device found on MUX");
            Serial.print(port);
            Serial.println(" at that address.");
        }
        
        delay(1000); // Wait 1 second before switching to the next port
    }
    
    // Optional: Isolate the main bus by closing all channels when the cycle is done
    mux.disableAllPorts();
    Serial.println("All MUX ports disabled to clear the bus.\n");
    
    delay(2000);
}
