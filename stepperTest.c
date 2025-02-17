#include <wiringPi.h>
#include <stdio.h>
#include "stepperTest.h"

#define DIR_PIN 0
#define STEP_PIN 2
#define STEPS_PER_REVOLUTION 200

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("wiringPi failed to setup!\n");
        return 1;
    }

    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);

    while (1) {
        playNote(261.63);
        playNote(293.66);
        playNote(329.63);
        playNote(349.23);
        playNote(392.00);
        playNote(440.00);
        playNote(493.88);
        playNote(523.25);
    }
}

void playNote(float frequency) {
    float period_us = (1 / frequency) * 1000000;

    for (int i = 0; i < STEPS_PER_REVOLUTION; i++) {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(period_us);
        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(period_us);
    }
}