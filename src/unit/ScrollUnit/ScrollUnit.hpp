#pragma once

#include <base/M5UnitBase.hpp>

class ScrollUnit : public M5UnitBase {
public:
    static constexpr uint8_t I2C_ADDRESS = 0x40;

    ScrollUnit(void);
    virtual ~ScrollUnit(void) = default;

    virtual bool begin(TwoWire &wire = Wire, uint8_t address = I2C_ADDRESS,
                       uint8_t sda = SDA, uint8_t scl = SCL,
                       uint32_t frequency = I2C_FREQUENCY);
    virtual bool update(void);
};
