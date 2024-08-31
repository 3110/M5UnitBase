#include "ScrollUnit.hpp"

const char *TAG = "main";
ScrollUnit scroll;
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