#include "PTSolns_I2Connect_MUX.h"

PTSolns_I2Connect_MUX::PTSolns_I2Connect_MUX() {
    _wire = &Wire;
    _i2cAddress = DEFAULT_I2C_ADDRESS;
    _i2cClock = DEFAULT_I2C_CLOCK;
}

bool PTSolns_I2Connect_MUX::begin(TwoWire &wirePort, uint8_t i2cAddress, uint32_t i2cClock) {
    _wire = &wirePort;
    setI2CAddress(i2cAddress); 
    _i2cClock = i2cClock;
    _wire->setClock(_i2cClock);

    delay(10); // Brief wait for I2C bus stability

    if (!isConnected()) {
        return false;
    }

    // Start with all downstream ports disabled to prevent address collisions
    disableAllPorts();
    
    return true;
}

void PTSolns_I2Connect_MUX::setI2CAddress(uint8_t i2cAddress) {
    _i2cAddress = i2cAddress;
}

void PTSolns_I2Connect_MUX::setI2CClock(uint32_t i2cClock) {
    _i2cClock = i2cClock;
    if (_wire) {
        _wire->setClock(_i2cClock);
    }
}

bool PTSolns_I2Connect_MUX::isConnected() {
    _wire->beginTransmission(_i2cAddress);
    return (_wire->endTransmission() == 0);
}

bool PTSolns_I2Connect_MUX::setPort(uint8_t portNumber) {
    // Only physical ports 1, 2, 3, and 4 are valid
    if (portNumber < 1 || portNumber > 4) {
        return false;
    }

    uint8_t arrayIndex = portNumber - 1;
    uint8_t hardwareChannel = _portMap[arrayIndex];

    _wire->beginTransmission(_i2cAddress);
    _wire->write(1 << hardwareChannel);
    return (_wire->endTransmission() == 0);
}

bool PTSolns_I2Connect_MUX::disableAllPorts() {
    _wire->beginTransmission(_i2cAddress);
    _wire->write(0x00); // Writing 0 disables all channels
    return (_wire->endTransmission() == 0);
}

uint8_t PTSolns_I2Connect_MUX::getActivePorts() {
    _wire->requestFrom(_i2cAddress, (uint8_t)1);
    if (_wire->available()) {
        return _wire->read();
    }
    return 0x00;
}