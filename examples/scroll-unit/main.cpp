#include "ScrollUnit.hpp"

ScrollUnit scroll;
bool pressed = false;

void setup(void) {
    if (!scroll.begin(Wire1, ScrollUnit::I2C_ADDRESS, RXD2, TXD2)) {
        forever();
    }
}

void loop(void) {
    if (scroll.isButtonPressed(pressed) && pressed) {
        ESP_LOGI("main", "Button pressed");
    }
    delay(100);
}