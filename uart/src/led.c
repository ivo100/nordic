#include "led.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

static struct gpio_dt_spec _leds[4] = {
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios),
    GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios)};

int invalid(led *led) {
    if (led == NULL) {
        return 1;
    }
    int id = led->id;
    if (id < 0 || id > 3) {
        return 1;
    }
    return 0;
}

int led_init(led *led) {
    int ret = invalid(led);
    if (ret) return ret;

    if (!device_is_ready((_leds[led->id].port))) {
        return 1;
    }

    ret = gpio_pin_configure_dt(&_leds[led->id], GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 1;
    }
    return 0;
}

int led_toggle(led *led) {
    int ret = invalid(led);
    if (ret) return ret;

    return gpio_pin_toggle_dt(&_leds[led->id]);
}
