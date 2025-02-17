#include "ads1115.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>

int ads1115Init(ADS1115* ads1115) {
    // Configure ADC settings
    wiringPiI2CWriteReg16(ads1115->fd, ADS1115_CONFIG, 0b1000000010000011);
    delay(10);
    return ads1115->fd;
}

int ads1115Update(ADS1115* ads1115) {
    // Read ADC pins and store in struct
    ads1115->a0 = wiringPiI2CReadReg16(ads1115->fd, ADS1115_CONVERSION);
    return ads1115->fd;
}