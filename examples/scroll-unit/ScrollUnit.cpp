#include "ScrollUnit.hpp"

template bool M5UnitBase::getValue<int32_t>(uint8_t, int32_t &) const;

ScrollUnit::ScrollUnit(void)
    : M5UnitBase(),
      _encoderValue({false, 0}),
      _incEncoderValue({false, 0}),
      _buttonPressed({false, false}) {
}

const char *ScrollUnit::getUnitName(void) const {
    return "ScrollUnit";
}

bool ScrollUnit::begin(TwoWire &wire, uint8_t sda, uint8_t scl, uint8_t address,
                       uint32_t frequency) {
    return M5UnitBase::begin(wire, sda, scl, address, frequency);
}

bool ScrollUnit::update(void) {
    updateEncoderValue();
    updateIncEncoderValue();
    updateButtonPressed();
    return true;
}

int32_t ScrollUnit::getEncoderValue(void) const {
    return this->_encoderValue.value;
}

int32_t ScrollUnit::getIncEncoderValue(void) const {
    return this->_incEncoderValue.value;
}

void ScrollUnit::resetEncoderValue(void) const {
    if (!this->setValue<int32_t>(static_cast<uint8_t>(register_t::RESET), 1)) {
        ESP_LOGE(getUnitName(), "Failed to reset encoder value");
    }
}

bool ScrollUnit::isButtonPressed(void) const {
    return this->_buttonPressed.value;
}

bool ScrollUnit::isEncoderValueUpdated(void) const {
    return this->_encoderValue.updated;
}

bool ScrollUnit::isIncEncoderValueUpdated(void) const {
    return this->_incEncoderValue.updated;
}

bool ScrollUnit::isButtonPressedUpdated(void) const {
    return this->_buttonPressed.updated;
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

ScrollUnit::quadrature_direction_t ScrollUnit::getEncoderDirection(void) const {
    uint8_t value = 0;
    if (!this->getValue<uint8_t>(
            static_cast<uint8_t>(register_t::ENCODER_AB_BA), value)) {
        return quadrature_direction_t::ERROR;
    }
    return static_cast<quadrature_direction_t>(value);
}

bool ScrollUnit::setEncoderDirection(quadrature_direction_t direction) const {
    return this->setValue<uint8_t>(
        static_cast<uint8_t>(register_t::ENCODER_AB_BA),
        static_cast<uint8_t>(direction));
}

bool ScrollUnit::updateEncoderValue(void) {
    int32_t value = 0;
    if (!this->getValue<int32_t>(static_cast<uint8_t>(register_t::ENCODER),
                                 value)) {
        return false;
    }
    this->_encoderValue.updated = value != this->_encoderValue.value;
    if (this->_encoderValue.updated) {
        this->_encoderValue.value = value;
    }
    return true;
}

bool ScrollUnit::updateIncEncoderValue(void) {
    int32_t value = 0;
    if (!this->getValue<int32_t>(static_cast<uint8_t>(register_t::INC_ENCODER),
                                 value)) {
        return false;
    }
    this->_incEncoderValue = {true, value};
    return true;
}

bool ScrollUnit::updateButtonPressed(void) {
    uint8_t value = 0;
    if (!this->getValue<uint8_t>(static_cast<uint8_t>(register_t::BUTTON),
                                 value)) {
        return false;
    }
    const bool pressed = (value & 0x01) == 0x00;
    this->_buttonPressed.updated = pressed != this->_buttonPressed.value;
    if (this->_buttonPressed.updated) {
        this->_buttonPressed.value = pressed;
    }
    return true;
}
