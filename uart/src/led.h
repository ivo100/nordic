#ifndef MY_LED_H_
#define MY_LED_H_

struct my_led {
    int id;  // 0-3
    int value;
};

typedef struct my_led led;

int led_init(led *led);

int led_toggle(led *led);

#endif
