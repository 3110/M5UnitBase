#include "ScrollUnit.hpp"

ScrollUnit scroll;
bool pressed = false;

void setup(void) {
    if (!scroll.begin(Wire1, RXD2, TXD2)) {
        forever();
    }
}

void loop(void) {
    if (scroll.isButtonPressed(pressed) && pressed) {
        ESP_LOGI("main", "Button pressed");
    }
    delay(100);
}