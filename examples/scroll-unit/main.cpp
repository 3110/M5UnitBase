#include "ScrollUnit.hpp"

const char *TAG = "main";
ScrollUnit scroll;

uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;

int32_t encoderValue = 0;
int32_t prevEncoderValue = 0;

int32_t incEncoderValue = 0;
int32_t prevIncEncoderValue = 0;

bool buttonPressed = false;
bool prevButtonPressed = false;

void setup(void) {
    if (!scroll.begin(Wire1, RXD2, TXD2)) {
        forever();
    }
    scroll.setLED(0, 255, 0);
    scroll.getLED(r, g, b);
    ESP_LOGI(TAG, "LED R: 0x%02X, G: 0x%02X, B: 0x%02X", r, g, b);
    scroll.resetEncoderValue();
}

void loop(void) {
    if (scroll.isButtonPressed(buttonPressed) &&
        prevButtonPressed != buttonPressed) {
        if (buttonPressed) {
            ESP_LOGI(TAG, "Button pressed: Reset Encoder Value");
            scroll.resetEncoderValue();
        }
        prevButtonPressed = buttonPressed;
    }
    if (scroll.getEncoderValue(encoderValue) &&
        prevEncoderValue != encoderValue) {
        ESP_LOGI(TAG, "Encoder Value: %d", encoderValue);
        prevEncoderValue = encoderValue;
    }
    if (scroll.getIncEncoderValue(incEncoderValue) &&
        prevIncEncoderValue != incEncoderValue) {
        if (incEncoderValue != 0) {
            ESP_LOGI(TAG, "Inc Encoder Value: %d", incEncoderValue);
        }
        prevIncEncoderValue = incEncoderValue;
        delay(10);
    }
}
