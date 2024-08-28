#include <esp_log.h>

#include "unit/ScrollUnit/ScrollUnit.hpp"

ScrollUnit scroll;
bool pressed = false;

void setup(void) {
    if (!scroll.begin(Wire1, ScrollUnit::I2C_ADDRESS, RXD2, TXD2)) {
        ESP_LOGE("ScrollUnit", "Failed to initialize ScrollUnit");
        forever();
    }
}

void loop(void) {
    scroll.update();
    if (!scroll.isButtonPressed(pressed)) {
        ESP_LOGE("ScrollUnit", "Failed to read button state");

    } else {
        if (pressed) {
            ESP_LOGI("ScrollUnit", "Button pressed");
        }
    }
    delay(100);
}