#include <wiringPi.h>
#include <stdio.h>
#include "stepperTest.h"

#define DIR_PIN 0
#define STEP_PIN 2

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("wiringPi failed to setup!\n");
        return 1;
    }

    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);

    while (1) {
        playNote(261.63, 1000);
        playNote(293.66, 1000);
        playNote(329.63, 1000);
        playNote(349.23, 1000);
        playNote(392.00, 1000);
        playNote(440.00, 1000);
        playNote(493.88, 1000);
        playNote(523.25, 1000);
    }
}

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