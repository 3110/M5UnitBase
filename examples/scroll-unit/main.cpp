#include "ScrollUnit.hpp"

const char *TAG = "main";
ScrollUnit scroll;
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
bool pressed = false;

struct encoder_t
{
    int32_t value;
    int32_t prev;
};

encoder_t encoderValue;
encoder_t incEncoderValue;

void setup(void) {
    if (!scroll.begin(Wire1, RXD2, TXD2)) {
        forever();
    }
    scroll.setLED(0, 255, 0);
    scroll.getLED(r, g, b);
    ESP_LOGI(TAG, "LED R: 0x%02X, G: 0x%02X, B: 0x%02X", r, g, b);
}

void loop(void) {
    if (scroll.isButtonPressed(pressed) && pressed) {
        ESP_LOGI(TAG, "Button pressed");
    }
    if (scroll.getEncoderValue(encoderValue.value) &&
        encoderValue.prev != encoderValue.value) {
        ESP_LOGI(TAG, "Encoder Value: %d", encoderValue.value);
        encoderValue.prev = encoderValue.value;
    }
    if (scroll.getIncEncoderValue(incEncoderValue.value) &&
        incEncoderValue.prev != incEncoderValue.value) {
        if (incEncoderValue.value != 0) {
            ESP_LOGI(TAG, "Inc Encoder Value: %d", incEncoderValue.value);
        }
        incEncoderValue.prev = incEncoderValue.value;
        delay(10);
    }
}