#ifndef PTSOLNS_I2CONNECT_MUX_H
#define PTSOLNS_I2CONNECT_MUX_H

#include <Arduino.h>
#include <Wire.h>

class PTSolns_I2Connect_MUX {
public:
    // Default address for the multiplexer (Jumpers A2, A1, A0 Open)
    static const uint8_t DEFAULT_I2C_ADDRESS = 0x70; 
    static const uint32_t DEFAULT_I2C_CLOCK = 100000UL;

    PTSolns_I2Connect_MUX();

    bool begin(TwoWire &wirePort = Wire, uint8_t i2cAddress = DEFAULT_I2C_ADDRESS, uint32_t i2cClock = DEFAULT_I2C_CLOCK);

    void setI2CAddress(uint8_t i2cAddress);
    void setI2CClock(uint32_t i2cClock);

    bool isConnected();
    
    // Core functional methods for the multiplexer
    bool setPort(uint8_t portNumber);
    bool disableAllPorts();
    uint8_t getActivePorts();

private:
    TwoWire *_wire;
    uint8_t _i2cAddress;
    uint32_t _i2cClock;

    // Hardware to Silkscreen Lookup Table
    // Index 0 to 3 maps to Silkscreen MUX1 to MUX4
    // Values are the internal IC hardware channels (3, 2, 0, 1)
    const uint8_t _portMap[4] = {3, 2, 0, 1};
};

#endif