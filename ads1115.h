#ifndef ADS1115_H
#define ADS1115_H

#include <stdint.h>
#include <limits.h>

#define ADS1115_I2C_ADDR 0b1001000 // Configured by shorting ADDR pin to GND

#define ADS1115_CONVERSION  0b00000000
#define ADS1115_CONFIG      0b00000001

typedef struct {
    int fd;
    int16_t a0;
    int16_t a1;
    int16_t a2;
    int16_t a3;
} ADS1115;

int ads1115Init(ADS1115* ads1115, char* i2cFileName);
int ads1115Update(ADS1115* ads1115);

#endif