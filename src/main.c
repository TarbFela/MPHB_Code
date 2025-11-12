#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include "hardware/spi.h"
#include "hardware/pwm.h"

#define PWM1_GPIO_PIN 16
#define PWM2_GPIO_PIN 20

int main(void) {
    stdio_init_all();
    sleep_ms(10000);

    uint gpio1 = PWM1_GPIO_PIN;
    uint gpio2 = PWM2_GPIO_PIN;

    uint slice_num1 = pwm_gpio_to_slice_num(gpio1);
    uint slice_num2 = pwm_gpio_to_slice_num(gpio2);

    if(slice_num1 == slice_num2) goto reboot;

    pwm_config pwmcfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&pwmcfg, 48000000); //1Hz (?)



    printf("Hello Capstone World!\n");
    char ui = 0;
    while(1) {
        scanf("%c",&ui);
        printf("You entered: %c\n",ui);
        if(ui=='q') break;
    }

reboot:
    printf("REBOOT!\n");
    reset_usb_boot(0,0);
    return 0;
}