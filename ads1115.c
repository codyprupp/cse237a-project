#include "ads1115.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Configure ADC settings
int ads1115Init(ADS1115* ads1115, char* i2cFileName) {
    ads1115->fd = open(i2cFileName, O_RDWR);
    if (ads1115->fd < 0) {
        printf("ERROR: Failed to open i2c; ensure i2c is enabled on the Pi and the i2c field of the struct has been initialized.\n");
        return 1;
    }

    if (ioctl(ads1115->fd, I2C_SLAVE, ADS1115_I2C_ADDR) < 0) {
        printf("ERROR: Failed to set I2C slave address!\n");
        return 1;
    }

    uint8_t buf[3] = {ADS1115_CONFIG, 0b10000100, 0b10000011};
    if (write(ads1115->fd, buf, sizeof(buf)) != sizeof(buf)) {
        printf("ERROR: Failed to write config register!\n");
        return 1;
    }

    return 0;
}

// Read ADC pins and store in struct
int ads1115Update(ADS1115* ads1115) {
    uint8_t buf[1] = {ADS1115_CONVERSION};
    if (write(ads1115->fd, buf, sizeof(buf)) != sizeof(buf)) {
        printf("ERROR: Failed to write conversion register address!\n");
        return 1;
    }
    
    uint8_t rBuf[2];
    if (read(ads1115->fd, rBuf, sizeof(rBuf)) != sizeof(rBuf)) {
        perror("ERROR: Failed to read conversion data!\n");
        return 1;
    }

    int16_t rawValue = (rBuf[0] << 8) | rBuf[1];
    
    ads1115->a0 = (rawValue < 0) ? 0 : rawValue;

    return 0;     
}