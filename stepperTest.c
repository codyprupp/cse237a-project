#include <wiringPi.h>
#include <stdio.h>
#include "stepper.h"

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