#include "stepper.h"
#include <wiringPi.h>
#include <stdio.h>

// Maps each motor to its corresponding step GPIO
const int STEP_PINS[NUM_MOTORS] = {1, 2};

void playNoteDuration(float frequency, float duration_ms, int motor) {
    float period_us = (1.0f / (frequency)) * 1000000.0f;

    for (int i = 0; i < duration_ms * 1000.0f / period_us; i++) {
        digitalWrite(STEP_PINS[motor], 1);
        delayMicroseconds(period_us / 2);
        digitalWrite(STEP_PINS[motor], 0);
        delayMicroseconds(period_us / 2);
    }
}

void playNote(float frequency, int motor) {
    float period_us = (1.0f / frequency) * 1000000.0f;

    digitalWrite(STEP_PINS[motor], 1);
    delayMicroseconds(period_us / 2);
    digitalWrite(STEP_PINS[motor], 0);
    delayMicroseconds(period_us / 2);
}

void initMotors() {
    pinMode(DIR_PIN, OUTPUT);
    for (int i = 0; i < NUM_MOTORS; i++) {
        pinMode(STEP_PINS[i], OUTPUT);
    }
}

void stepMotor(int motor) {
    digitalWrite(STEP_PINS[motor], 1);
    digitalWrite(STEP_PINS[motor], 0);
}