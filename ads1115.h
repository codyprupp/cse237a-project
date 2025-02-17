#ifndef ADS1115_H
#define ADS1115_H

#include <stdint.h>

#define ADS1115_I2C_ADDR 0b1001000 // Configured by shorting ADDR pin to GND

#define ADS1115_CONVERSION  0b00000000
#define ADS1115_CONFIG      0b00000001

typedef struct {
    int fd;
    uint16_t a0;
    uint16_t a1;
    uint16_t a2;
    uint16_t a3;
} ADS1115;

int ads1115Init(ADS1115* ads1115);
int ads1115Update(ADS1115* ads1115);

#endif