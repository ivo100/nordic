#include "keypad.h"
#include "led.h"

// just for fun - using message queue to pass button presses 1-3
// from UART to led 1-3
// led 0 is used by a heartbeat thread in led

#define QUEUE_SIZE 16
#define DATA_LEN 1
#define DATA_ALIGN 1
K_MSGQ_DEFINE(queue, DATA_LEN, QUEUE_SIZE, DATA_ALIGN);

// main thread
int main(void) {
    keypad keypad;
    printk("main 1.0.4 starts\n");

    if (led_init()) {
        printk("led_init failed");
        return 1;
    }

    if (keypad_init(&keypad)) {
        printk("keypad_init failed");
        return 1;
    }

    // main loop
    while (1) {
        k_yield();
        //  Read all key presses
        while (k_msgq_num_used_get(&queue)) {
            uint8_t idx;
            k_msgq_get(&queue, &idx, K_NO_WAIT);
            idx = idx - 48;
            // we handle only 1,2,3
            if (idx > 0 && idx < 4) {
                led_toggle(idx);
            }
            k_yield();
        }
        k_msleep(20);
    }
}
