#include "base/M5UnitBase.hpp"

M5UnitBase::M5UnitBase(void) : _wire(nullptr), _address(0) {
}

bool M5UnitBase::begin(TwoWire &wire, uint8_t address, uint8_t sda, uint8_t scl,
                       uint32_t frequency) {
    this->_wire = &wire;
    this->_address = address;
    this->_wire->begin(sda, scl, frequency);
    return isConnected();
}

bool M5UnitBase::update(void) {
    return true;
}

bool M5UnitBase::isConnected(void) const {
    if (this->_wire == nullptr || this->_address == 0) {
        return false;
    }
    this->_wire->beginTransmission(this->_address);
    return this->_wire->endTransmission() == 0;
}

bool M5UnitBase::read(uint8_t reg, uint8_t *data, size_t size) const {
    if (this->_wire == nullptr || this->_address == 0) {
        return false;
    }
    this->_wire->beginTransmission(this->_address);
    this->_wire->write(reg);
    if (this->_wire->endTransmission() != 0) {
        return false;
    }
    if (this->_wire->requestFrom(this->_address, size) != size) {
        return false;
    }
    for (size_t i = 0; i < size; i++) {
        data[i] = this->_wire->read();
    }
    return true;
}

bool M5UnitBase::write(uint8_t reg, const uint8_t *data, size_t size) const {
    if (this->_wire == nullptr || this->_address == 0) {
        return false;
    }
    this->_wire->beginTransmission(this->_address);
    this->_wire->write(reg);
    for (size_t i = 0; i < size; ++i) {
        this->_wire->write(data[i]);
    }
    return this->_wire->endTransmission() == 0;
}