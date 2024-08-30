#pragma once

#include <base/M5UnitBase.hpp>

class ScrollUnit : public M5UnitBase {
public:
    static constexpr uint8_t I2C_ADDRESS = 0x40;

    enum class register_t : uint8_t
    {
        ENCODER = 0x10,
        BUTTON = 0x20,
        RGB_LED = 0x30,
        RESET = 0x40,
        INC_ENCODER = 0x50,
        BOOTLOADER_VERSION = 0xFC,
        JUMP_TO_BOOTLOADER = 0xFD,
        FIRMWARE_VERSION = 0xFE,
        I2C_ADDRESS = 0xFF,
    };

    ScrollUnit(void);
    virtual ~ScrollUnit(void) = default;

    virtual const char *getUnitName(void) const override;

    virtual bool begin(TwoWire &wire = Wire, uint8_t address = I2C_ADDRESS,
                       uint8_t sda = SDA, uint8_t scl = SCL,
                       uint32_t frequency = I2C_FREQUENCY);
    virtual bool update(void);

    virtual bool getEncoderValue(int32_t &value) const;
    virtual bool getIncEncoderValue(int32_t &value) const;
    virtual bool isButtonPressed(bool &pressed) const;
};
