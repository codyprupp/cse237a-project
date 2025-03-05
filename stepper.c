#include "stepper.h"
#include <wiringPi.h>
#include <stdio.h>

void playNote(float frequency, float duration_ms) {
    float period_us = (1.0f / (frequency)) * 1000000.0f;

    for (int i = 0; i < duration_ms * 1000.0f / period_us; i++) {
        digitalWrite(STEP_PIN, 1);
        delayMicroseconds(period_us / 2);
        digitalWrite(STEP_PIN, 0);
        delayMicroseconds(period_us / 2);
    }
}