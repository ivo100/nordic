#include "pixels.h"

#include <string.h>

static struct led_rgb _pixels[NUM_PIXELS];

static struct device *strip = DEVICE_DT_GET(STRIP_NODE);

int pixels_show() {
    return led_strip_update_rgb(strip, _pixels, NUM_PIXELS);
}

void pixels_clear() {
    memset(&_pixels, 0x00, sizeof(_pixels));
    return;
}

/// @brief
/// @param index
/// @param red
/// @param green
/// @param blue
/// @return
int pixels_set_one(byte index, byte red, byte green, byte blue) {
    if (index < 0 || index >= NUM_PIXELS) {
        return NUM_PIXELS;
    }
    struct led_rgb *p = &_pixels[index];
    p->b = blue;
    p->g = green;
    p->r = red;
    return 0;
}

void pixels_set(byte red, byte green, byte blue) {
    struct led_rgb rgb = {red, green, blue};
    uint32_t *p = (uint32_t *)&rgb;
    memset(&_pixels, *p, sizeof(_pixels));
}

int pixels_clear_one(byte index) {
    if (index < 0 || index >= NUM_PIXELS) {
        return 1;
    }
    struct led_rgb *p = &_pixels[index];
    p->b = p->g = p->r = 0;
}

void pixels_sleep(byte msec) {
    k_msleep(msec);
}
