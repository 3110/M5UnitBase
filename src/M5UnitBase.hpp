#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <esp_log.h>

class M5UnitBase {
public:
    static constexpr uint32_t I2C_FREQUENCY = 400000UL;

    M5UnitBase(void);
    virtual ~M5UnitBase(void) = default;

    virtual bool begin(TwoWire &wire, uint8_t sda, uint8_t scl, uint8_t address,
                       uint32_t frequency = I2C_FREQUENCY);
    virtual bool update(void);

    virtual bool isConnected(void) const;

    virtual const char *getUnitName(void) const = 0;

protected:
    virtual bool read(uint8_t reg, uint8_t *data, size_t size) const;
    virtual bool write(uint8_t reg, const uint8_t *data, size_t size) const;

    template <typename T>
    inline bool getValue(uint8_t reg, T &value) const {
        uint8_t data[sizeof(T)];
        if (!read(reg, data, sizeof(T))) {
            ESP_LOGE(getUnitName(), "Failed to read value from register %d",
                     reg);
            return false;
        }
        value = *reinterpret_cast<T *>(data);
        return true;
    }

private:
    TwoWire *_wire;
    uint8_t _address;
};

inline void forever(void) {
    while (1) {
        delay(1000);
    }
}
