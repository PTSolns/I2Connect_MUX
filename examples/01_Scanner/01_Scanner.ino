// Example: I2C Scanner for I2Connect: MUX
// Last Update: October 23, 2026
// Support: http://ptsolns.com/contact-us
//
// WHAT THIS EXAMPLE DOES
// Initializes the multiplexer and systematically scans MUX1 through MUX4,
// reporting any I2C devices connected to each specific port.
//
// SKILLS LEARNED
// begin()
// setPort(portNumber)
//
// DESCRIPTION
// When building complex I2C projects, you often need to verify that your devices 
// are wired correctly and recognized by the bus. This scanner isolates each 
// physical port on the I2Connect: MUX and runs a standard I2C address sweep. 
// It utilizes the library's built-in translation array to ensure that asking 
// for "MUX2" opens the correct hardware channel underneath.

#include <Wire.h>
#include <PTSolns_I2Connect_MUX.h>

// User Settings
const uint32_t SERIAL_BAUD  = 115200; 
const uint32_t I2C_CLOCK_HZ = 100000; // Standard 100kHz for reliable scanning
const uint8_t  I2C_ADDRESS  = 0x70;   // Default address (Jumpers A0-A2 Open)

PTSolns_I2Connect_MUX mux;

void setup() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) { }

    Wire.begin();
    
    if (!mux.begin(Wire, I2C_ADDRESS, I2C_CLOCK_HZ)) {
        Serial.println("I2Connect MUX not detected. Please check your wiring!");
        while (1) { } // Halt execution
    }
    
    Serial.println("I2Connect MUX initialized.");
    Serial.println("Starting Port Scan...");
    Serial.println("----------------------------------------");
}

void loop() {
    Serial.println("\n--- New Scan Cycle ---");
    
    // Loop through the physical ports labeled on the silkscreen (1 to 4)
    for (uint8_t port = 1; port <= 4; port++) {
        
        // Open the specific port
        mux.setPort(port);
        
        Serial.print("MUX");
        Serial.print(port);
        Serial.print(" Port: ");
        
        bool foundDevice = false;
        
        // Standard I2C sweep (Addresses 1 to 127)
        for (uint8_t addr = 1; addr < 127; addr++) {
            // Skip the multiplexer's own address so it doesn't show up in the results
            if (addr == I2C_ADDRESS) continue; 
            
            Wire.beginTransmission(addr);
            if (Wire.endTransmission() == 0) {
                Serial.print("[Device at 0x");
                if (addr < 16) Serial.print("0");
                Serial.print(addr, HEX);
                Serial.print("] ");
                foundDevice = true;
            }
        }
        
        if (!foundDevice) {
            Serial.print("Empty");
        }
        Serial.println();
    }
    
    delay(5000); // Wait 5 seconds before scanning again
}
