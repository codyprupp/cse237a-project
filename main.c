#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <pthread.h>
#include "ads1115.h"
#include "stepper.h"

#define ACTUATE_THRESHOLD 0

ADS1115 ads;
pthread_t updateThread;

void* updateADS1115(void* arg) {
    while (1) {
        ads1115Update(&ads);
    }
    return NULL;
}

int main(void) {
    if (wiringPiSetup() < 0) {
        printf("ERROR: wiringPi initialization failed!\n");
        return 1;
    }

    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);

    ads1115Init(&ads, "/dev/i2c-1");

    // Update the ADC readings in separate thread
    if (pthread_create(&updateThread, NULL, updateADS1115, NULL)) {
        printf("ERROR: Unable to create ADS1115 update thread\n");
        return 1;
    }

    while (1) {
        if (ads.a[0] > ACTUATE_THRESHOLD) {
            playNote(C, 100);
        } else if (ads.a[1] > ACTUATE_THRESHOLD) {
            playNote(E, 100);
        } else if (ads.a[2] > ACTUATE_THRESHOLD) {
            playNote(G, 100);
        } else if (ads.a[3] > ACTUATE_THRESHOLD) {
            playNote(C*2, 100);
        } 

        printf("%d %d %d %d\n", ads.a[0], ads.a[1], ads.a[2], ads.a[3]);
    }

    close(ads.fd);
    pthread_join(updateThread, NULL);

    return 0;
}