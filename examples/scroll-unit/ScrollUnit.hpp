#pragma once

#include <M5UnitBase.hpp>

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
        ENCODER_AB_BA = 0xFB,
        BOOTLOADER_VERSION = 0xFC,
        JUMP_TO_BOOTLOADER = 0xFD,
        FIRMWARE_VERSION = 0xFE,
        I2C_ADDRESS = 0xFF,
    };

    ScrollUnit(void);
    virtual ~ScrollUnit(void) = default;

    virtual const char *getUnitName(void) const override;

    virtual bool begin(TwoWire &wire, uint8_t sda, uint8_t scl,
                       uint8_t address = I2C_ADDRESS,
                       uint32_t frequency = I2C_FREQUENCY);
    virtual bool update(void) override;

    virtual int32_t getEncoderValue(void) const;
    virtual int32_t getIncEncoderValue(void) const;
    virtual void resetEncoderValue(void) const;

    virtual bool isButtonPressed(void) const;

    virtual bool isEncoderValueUpdated(void) const;
    virtual bool isIncEncoderValueUpdated(void) const;
    virtual bool isButtonPressedUpdated(void) const;

    virtual bool setLED(uint8_t r, uint8_t g, uint8_t b) const;
    virtual bool getLED(uint8_t &r, uint8_t &g, uint8_t &b) const;

protected:
    virtual bool updateEncoderValue(void);
    virtual bool updateIncEncoderValue(void);
    virtual bool updateButtonPressed(void);

private:
    bool _encoderValueUpdated;
    int32_t _encoderValue;

    bool _incEncoderValueUpdated;
    int32_t _incEncoderValue;

    bool _buttonPressedUpdated;
    bool _buttonPressed;
};
