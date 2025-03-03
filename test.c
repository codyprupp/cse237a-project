#include <stdio.h>
#include "test.h"
#include "ads1115.h"
#include <unistd.h>

int main(void) {
    ADS1115 ads;
    ads1115Init(&ads, "/dev/i2c-1");

    unsigned long long counter = 0;

    while (1) {
        ads1115Update(&ads);
       
        printf("%llu %d\n", counter, (int16_t)ads.a0);
        fflush(stdout);

        usleep(10 * 1000);
        counter++;
    }
    
    return 0;
}