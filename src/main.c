#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#include "hardware/spi.h"
#include "hardware/pwm.h"

// 16 = 0A, 20 = 2A
// 10 = 5A, 12 = 6A (pins 14 & 16)
#define PWM1_GPIO_PIN 10
#define PWM2_GPIO_PIN 12

int main(void) {
    stdio_init_all();
    sleep_ms(10000);

    uint gpio1 = PWM1_GPIO_PIN;
    uint gpio2 = PWM2_GPIO_PIN;

    uint slice_num1 = pwm_gpio_to_slice_num(gpio1);
    uint slice_num2 = pwm_gpio_to_slice_num(gpio2);
    uint chan_num1 = pwm_gpio_to_channel(gpio1);
    uint chan_num2 = pwm_gpio_to_channel(gpio2);

    if(slice_num1 == slice_num2) {
        printf("Choose different gpios to get different slices.\n");
        goto reboot;
    }

    pwm_config pwmcfg = pwm_get_default_config();
    pwm_config_set_clkdiv(&pwmcfg, 100); // 48MHz --> 480kHz
    pwmcfg.top = 47999; //480kHz --> 10Hz
    pwm_set_chan_level(slice_num1, chan_num1, 48000/4); // 25%
    pwm_set_chan_level(slice_num2, chan_num2, 48000/4); // 25%

    gpio_set_function(PWM1_GPIO_PIN, GPIO_FUNC_PWM);
    gpio_set_function(PWM2_GPIO_PIN, GPIO_FUNC_PWM);

    pwm_init(slice_num1, &pwmcfg, 0);
    pwm_set_counter(slice_num2,48000/2); // offset by 50%
    pwm_init(slice_num2,&pwmcfg,0);

    uint8_t pwm_mask = (1<<slice_num2) | (1<<slice_num1);

    // start them up!
    pwm_set_mask_enabled(pwm_mask);

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