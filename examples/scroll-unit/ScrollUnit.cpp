#include "ScrollUnit.hpp"

ScrollUnit::ScrollUnit(void) : M5UnitBase() {
}

bool ScrollUnit::begin(TwoWire &wire, uint8_t address, uint8_t sda, uint8_t scl,
                       uint32_t frequency) {
    return M5UnitBase::begin(wire, address, sda, scl, frequency);
}

bool ScrollUnit::update(void) {
    return M5UnitBase::update();
}
