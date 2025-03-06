#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "ads1115.h"
#include "stepper.h"
#include <time.h>
#include "music.h"

#define ACTUATE_THRESHOLD 0
#define DEMO_MODE 0 // 0 for manual mode, 1+ for song selection

ADS1115 ads;
pthread_t updateThread;

float motorPeriods[NUM_MOTORS] = {(1.0f / C4) * 1000000.0f, (1.0f / G4) * 1000000.0f}; // Stores the frequencies that each motor should play
long long motorHistory[NUM_MOTORS] = {0}; // Stores the most recent time a motor started playing a note (for scheduling)

/**
 * Thread function to update ADC readings in background so it doesn't interfere with audio output
 */
void* updateADS1115(void* arg) {
    while (1) {
        ads1115Update(&ads);
    }
    return NULL;
}

// Helper function to return the current time
long long getMicroseconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000000LL + ts.tv_nsec / 1000;
}

// Step motor if target period has passed
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

#if DEMO_MODE == 0
    while (1) {
        // Schedule a new note if pressure sensor detects input
        if (ads.a[0] > ACTUATE_THRESHOLD) {
            motorPeriods[0] = (1.0f / C4) * 1000000.0f; // Convert target frequency to period in ms
        } else if (ads.a[1] > ACTUATE_THRESHOLD) {
            motorPeriods[0] = (1.0f / E4) * 1000000.0f;
        } else {
            motorPeriods[0] = 0;
        }

        // Support for up to 2 simultaneous motors being actuated
        if (ads.a[2] > ACTUATE_THRESHOLD) {
            motorPeriods[1] = (1.0f / G4) * 1000000.0f;
        } else if (ads.a[3] > ACTUATE_THRESHOLD) {
            motorPeriods[1] = (1.0f / C5) * 1000000.0f;
        } else {
            motorPeriods[1] = 0;
        }

        // Actuate motors if there are any scheduled notes
        for (int i = 0; i < NUM_MOTORS; i++) {
            if (motorPeriods[i] > 0) {
                actuateMotor(i);
            }
        }
    }

#elif DEMO_MODE == 1
    playMusic(kids_mgmt_melody);
#elif DEMO_MODE == 2
    playMusic(twinkle_melody, 120);
#elif DEMO_MODE == 3
    playMusic(clocks_melody, 122);
    playMusic(clocks_melody, 122);
#endif

    pthread_cancel(updateThread);
    pthread_join(updateThread, NULL);
    close(ads.fd);

    return 0;
}
