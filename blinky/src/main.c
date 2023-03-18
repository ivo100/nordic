/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE	DT_ALIAS(sw0)

// led on or off

static int led_value = 0;

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* STEP 3.2 - Get the device pointer. pin number, and pin's configuration flags through gpio_dt_spec */
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

/* STEP 4 - Define the callback function */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	led_value = 1 - led_value;
	printk("BUTTON CLICK led value: %d\n", led_value);
	int ret = gpio_pin_set_dt(&led, led_value);
	if (ret < 0) {
		printk("*** ERROR from pin_st\n");
		return;
	}

}
/* STEP 5 - Define a variable of type static struct gpio_callback */
static struct gpio_callback button_cb_data;


void main(void)
{
	int ret;
	printk("BUTTON BLINKY SAMPLE STARTS...\n");
	if (!device_is_ready(led.port)) {
		printk("*** ERROR 1\n");
		return;
	}
	if (!device_is_ready(button.port)) {
		printk("*** ERROR 2\n");
		return;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		printk("*** ERROR 3\n");
		return;
	}

	ret = gpio_pin_set_dt(&led, led_value);
	if (ret < 0) {
		printk("*** ERROR 4\n");
		return;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		printk("*** ERROR 5\n");
		return;
	}
	/* STEP 3 - Configure the interrupt on the button's pin */
	ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE );

	/* STEP 6 - Initialize the static struct gpio_callback variable   */
    gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin)); 	
	
	/* STEP 7 - Add the callback function by calling gpio_add_callback()   */
	gpio_add_callback(button.port, &button_cb_data);
	
	//gpio_pin_set_dt(&button, 1);

	while (1) {
		// bool val = gpio_pin_get_dt(&button);

		// ret = gpio_pin_set_dt(&led, val);
		// if (ret < 0) {
		// 	return;
		// }
		k_msleep(SLEEP_TIME_MS);
	}
}
