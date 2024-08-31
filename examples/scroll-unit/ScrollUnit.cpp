#include "ScrollUnit.hpp"

template bool M5UnitBase::getValue<int32_t>(uint8_t, int32_t &) const;

ScrollUnit::ScrollUnit(void) : M5UnitBase() {
}

const char *ScrollUnit::getUnitName(void) const {
    return "ScrollUnit";
}

bool ScrollUnit::begin(TwoWire &wire, uint8_t sda, uint8_t scl, uint8_t address,
                       uint32_t frequency) {
    return M5UnitBase::begin(wire, sda, scl, address, frequency);
}

bool ScrollUnit::update(void) {
    return true;
}

bool ScrollUnit::getEncoderValue(int32_t &value) const {
    return this->getValue<int32_t>(static_cast<uint8_t>(register_t::ENCODER),
                                   value);
}

bool ScrollUnit::getIncEncoderValue(int32_t &value) const {
    return this->getValue<int32_t>(
        static_cast<uint8_t>(register_t::INC_ENCODER), value);
}

bool ScrollUnit::resetEncoderValue(void) const {
    return this->setValue<uint8_t>(static_cast<uint8_t>(register_t::RESET), 1);
}

bool ScrollUnit::isButtonPressed(bool &pressed) const {
    uint8_t data = 0;
    if (!this->getValue<uint8_t>(static_cast<uint8_t>(register_t::BUTTON),
                                 data)) {
        return false;
    }
    pressed = (data & 0x01) == 0x00;
    return true;
}

bool ScrollUnit::setLED(uint8_t r, uint8_t g, uint8_t b) const {
    const int32_t rgb = (b << 24) | (g << 16) | (r << 8);
    return this->setValue<int32_t>(static_cast<uint8_t>(register_t::RGB_LED),
                                   rgb);
}

bool ScrollUnit::getLED(uint8_t &r, uint8_t &g, uint8_t &b) const {
    int32_t rgb = 0;
    if (!this->getValue<int32_t>(static_cast<uint8_t>(register_t::RGB_LED),
                                 rgb)) {
        return false;
    }
    r = (rgb >> 8) & 0xFF;
    g = (rgb >> 16) & 0xFF;
    b = (rgb >> 24) & 0xFF;
    return true;
}