#include "ScrollUnit.hpp"

const char *TAG = "main";
ScrollUnit scroll;

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

void setup(void) {
    if (!scroll.begin(Wire1, RXD2, TXD2)) {
        forever();
    }

    ScrollUnit::quadrature_direction_t direction =
        ScrollUnit::quadrature_direction_t::CCW;
    scroll.setEncoderDirection(direction);
    ESP_LOGI(TAG, "Encoder Direction: %s",
             direction == ScrollUnit::quadrature_direction_t::CW ? "AB" : "BA");

    scroll.setLED(0, 255, 0);
    scroll.getLED(r, g, b);
    ESP_LOGI(TAG, "LED R: 0x%02X, G: 0x%02X, B: 0x%02X", r, g, b);

    scroll.resetEncoderValue();
}

void loop(void) {
    scroll.update();

    if (scroll.isIncEncoderValueUpdated()) {
        const int32_t incEncoderValue = scroll.getIncEncoderValue();
        if (incEncoderValue != 0) {
            ESP_LOGI(TAG, "Inc Encoder Value: %d", incEncoderValue);
        }
    }
    if (scroll.isEncoderValueUpdated()) {
        ESP_LOGI(TAG, "Encoder Value: %d", scroll.getEncoderValue());
    }
    if (scroll.isButtonPressedUpdated() && scroll.isButtonPressed()) {
        ESP_LOGI(TAG, "Button pressed: Reset Encoder Value");
        scroll.resetEncoderValue();
    }
    delay(10);
}
