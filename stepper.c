#include "stepper.h"
#include <wiringPi.h>
#include <stdio.h>

void playNote(float frequency, float duration_ms) {
    float period_ms = (1.0f / frequency) * 1000.0f;
    printf("period: %f\n", period_ms);

    for (int i = 0; i < duration_ms / period_ms; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(period_ms * 500);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(period_ms * 500);
    }
}