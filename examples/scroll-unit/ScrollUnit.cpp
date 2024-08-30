#include "ScrollUnit.hpp"

template bool M5UnitBase::getValue<int32_t>(uint8_t, int32_t &) const;

ScrollUnit::ScrollUnit(void) : M5UnitBase() {
}

const char *ScrollUnit::getUnitName(void) const {
    return "ScrollUnit";
}

bool ScrollUnit::begin(TwoWire &wire, uint8_t address, uint8_t sda, uint8_t scl,
                       uint32_t frequency) {
    return M5UnitBase::begin(wire, address, sda, scl, frequency);
}

bool ScrollUnit::update(void) {
    return M5UnitBase::update();
}

bool ScrollUnit::getEncoderValue(int32_t &value) const {
    return this->getValue<int32_t>(static_cast<uint8_t>(register_t::ENCODER),
                                   value);
}

bool ScrollUnit::getIncEncoderValue(int32_t &value) const {
    return this->getValue<int32_t>(
        static_cast<uint8_t>(register_t::INC_ENCODER), value);
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