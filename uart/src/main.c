#include "keypad.h"
#include "led.h"

/* Every thread needs its own stack in RAM */
#define THREAD_STACK_SIZE 1024

led L[4] = {};

/* All animations handled by this thread */
void blinking_thread(void *d0, void *d1, void *d2) {
    int value = 1;
    while (1) {
        led_toggle(&leds[3]);
        k_msleep(100);
        value = 1 - value;
        //printk("blink loop %d\n", value);
    }
}

int main(void) {
    keypad keypad;
    printk("main starts\n");
    if (keypad_init(&keypad)) {
        printk("keypad_init failed");
        return 1;
    }
    for (int i=0; i<4; i++) {
        leds[i].id = i;
        leds[i].value = 0;
        if (led_init(&leds[i])) {
            printk("led_init %d failed\n", i);
            return 1;
        }
    }
    k_thread_start(blinking_thread);
    while (1) {
        k_msleep(1000);
        //printk("main loop\n");
    }
}

/* Define and initialize the new thread */
K_THREAD_DEFINE(blinking_thread_tid, THREAD_STACK_SIZE,
                blinking_thread, NULL, NULL, NULL,
                K_LOWEST_APPLICATION_THREAD_PRIO, 0, 0);
