#include "led.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define THREAD_STACK_SIZE 1024

struct leds {
    struct gpio_dt_spec led;
    int value;
} _leds[4] = {
    {GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios), 0}};

void heartbeat_thread(void *d0, void *d1, void *d2) {
    while (1) {
        k_yield();
        led_toggle(0);
        k_msleep(1000);
        // printk("heartbeat\n");
    }
}

// initialize 4 leds 0-3
int led_init() {
    for (int i = 0; i < 4; i++) {
        if (!device_is_ready((_leds[i].led.port))) {
            return 1;
        }
        if (gpio_pin_configure_dt(&_leds[i].led, GPIO_OUTPUT_ACTIVE) < 0) {
            return 1;
        }
        led_toggle(i);
    }
    return 0;
}

int led_toggle(int idx) {
    if (idx < 0 || idx > 3) {
        return 1;
    }
    return gpio_pin_toggle_dt(&_leds[idx].led);
}

K_THREAD_DEFINE(heartbeat_thread_tid, THREAD_STACK_SIZE,
                heartbeat_thread, NULL, NULL, NULL,
                K_LOWEST_APPLICATION_THREAD_PRIO, 0, 0);
