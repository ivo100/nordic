#ifndef MY_PIXELS_H_
#define MY_PIXELS_H_
#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/util.h>

#define STRIP_NODE DT_ALIAS(led_strip)
#define NUM_PIXELS DT_PROP(DT_ALIAS(led_strip), chain_length)

typedef uint8_t byte;

int pixels_show();

void pixels_clear();

void pixels_set(byte red, byte green, byte blue);

int pixels_clear_one(byte index);

int pixels_set_one(byte index, byte red, byte green, byte blue);

void pixels_sleep(byte msec);

#endif MY_PIXELS_H_
