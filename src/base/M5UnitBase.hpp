#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <pins_arduino.h>

class M5UnitBase {
public:
    static constexpr uint32_t I2C_FREQUENCY = 400000UL;

    M5UnitBase(void);
    virtual ~M5UnitBase(void) = default;

    virtual bool begin(TwoWire &wire, uint8_t address, uint8_t sda = SDA,
                       uint8_t scl = SCL, uint32_t frequency = I2C_FREQUENCY);
    virtual bool update(void);

    virtual bool isConnected(void) const;
    virtual bool read(uint8_t reg, uint8_t *data, size_t size) const;

protected:
    TwoWire *_wire;
    uint8_t _address;
};
