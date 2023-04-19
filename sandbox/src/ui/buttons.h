
#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <inttypes.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>

#ifdef __cplusplus
extern "C" {
#endif

// struct buttons_entry_ctx {
//     struct gpio_callback button_cb_data;
// };

typedef int (*buttons_cb)(struct gpio_callback *ctx);

int buttons_init(buttons_cb cb);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
