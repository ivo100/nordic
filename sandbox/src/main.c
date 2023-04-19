#include "keypad.h"
#include "led.h"

// just for fun - using message queue to pass button presses 1-3
// from UART to led 1-3
// led 0 is used by a heartbeat thread in led

#define QUEUE_SIZE 16
#define DATA_LEN 1
#define DATA_ALIGN 1

extern void run_timer(void);

K_MSGQ_DEFINE(queue, DATA_LEN, QUEUE_SIZE, DATA_ALIGN);

keypad keyp;

int work();
int main();
int init();

// main thread
int main(void) {
    printk("main 1.4.18 starts\n");
    if (init()) {
        printk("init failed\n");
        return 1;
    }
    // run_timer();
    //  main loop
    while (1) {
        k_yield();
        work();
    }
}

int init() {
    if (keypad_init(&keyp)) {
        printk("keypad_init failed");
        return 1;
    }
    if (led_init()) {
        printk("led_init failed");
        return 1;
    }
    return 0;
}

int work() {
    uint8_t idx;
    //  Read all keypad codes from the queue
    while (k_msgq_num_used_get(&queue)) {
        k_msgq_get(&queue, &idx, K_NO_WAIT);
        idx = idx - 48;
        // we handle only 1,2,3
        if (idx > 0 && idx < 4) {
            led_toggle(idx);
        }
        k_yield();
        k_msleep(10);
    }
    k_msleep(20);
    return 0;
}
