#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "ads1115.h"
#include "stepper.h"
#include <time.h>

#define ACTUATE_THRESHOLD 0

ADS1115 ads;
pthread_t updateThread;

float motorPeriods[NUM_MOTORS] = {(1.0f / C) * 1000000.0f, (1.0f / G) * 1000000.0f};//, (1.0f / G) * 1000000.0f, (1.0f / (C*2)) * 1000000.0f};
long long motorHistory[NUM_MOTORS] = {0};

void* updateADS1115(void* arg) {
    while (1) {
        ads1115Update(&ads);
    }
    return NULL;
}

long long getMicroseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000LL + ts.tv_nsec / 1000;
}

// Step motor if period has passed
void actuateMotor(int motor) {
    long long curTime = getMicroseconds();
    if (curTime - motorHistory[motor] > motorPeriods[motor]) {
        stepMotor(motor);
        motorHistory[motor] = curTime;
    }
}

int main(void) {
    if (wiringPiSetup() < 0) {
        printf("ERROR: wiringPi initialization failed!\n");
        return 1;
    }

    initMotors();

    ads1115Init(&ads, "/dev/i2c-1");

    // Update the ADC readings in separate thread
    if (pthread_create(&updateThread, NULL, updateADS1115, NULL)) {
        printf("ERROR: Unable to create ADS1115 update thread\n");
        return 1;
    }

    while (1) {
        for (int i = 0; i < NUM_MOTORS; i++) {
            if (ads.a[i] > ACTUATE_THRESHOLD) {
                actuateMotor(i);
            }
        }

        // printf("\n");
    }

    close(ads.fd);
    pthread_join(updateThread, NULL);

    return 0;
}