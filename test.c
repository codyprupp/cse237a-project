#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include "test.h"
#include "ads1115.h"

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("wiringPi failed to setup!\n");
        return 1;
    }

    // Init I2C
    ADS1115 adc;
    adc.fd = wiringPiI2CSetup(ADS1115_I2C_ADDR);
    if (adc.fd < 0) {
        printf("I2C setup failed!\n");
        return -1;
    }

    ads1115Init(&adc);
    printf("Initial ADC value: %d\n", adc.a0);

    while (1) {
        ads1115Update(&adc);
        printf("ADC VALUE: %d (status %d)\n", adc.a0, adc.fd);
        delay(100);
    }
}