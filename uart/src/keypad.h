#ifndef MY_KEYPAD_H_
#define MY_KEYPAD_H_

#include <stdint.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>

#define RECEIVE_BUF_SIZE 16
#define RECEIVE_TIMEOUT 100
#define SEND_BUF_SIZE 64

struct my_keypad {
    struct device *uart;
    int id;
    int value;
    uint8_t tx_buf[SEND_BUF_SIZE];
    uint8_t rx_buf[RECEIVE_BUF_SIZE];
};

typedef struct my_keypad keypad;

int keypad_init(keypad *keypad);

#endif