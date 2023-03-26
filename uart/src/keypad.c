#include "keypad.h"

#include <string.h>
#include <zephyr/sys/printk.h>

/*  callback function for UART */
static int keypad_received_char(const struct device *dev, struct uart_event *evt, void *user_data) {
    switch (evt->type) {
        case UART_RX_RDY:
            if ((evt->data.rx.len) == 1) {
                // received 1 char - send it to msg queue
                uint8_t ch = evt->data.rx.buf[evt->data.rx.offset];
                printk("received char %c \n", ch);
                // TODO

                // if (evt->data.rx.buf[evt->data.rx.offset] == '1') {
                //     //producer_foo(&prod, 1);
                //     //gpio_pin_toggle_dt(&led0);
                // } else if (evt->data.rx.buf[evt->data.rx.offset] == '2') {
                //     //producer_foo(&prod, 2);
                //     //gpio_pin_toggle_dt(&led1);
                // } else if (evt->data.rx.buf[evt->data.rx.offset] == '3') {
                //     //producer_foo(&prod, 3);
                //     //gpio_pin_toggle_dt(&led2);
                // }
            }
            break;
        case UART_RX_DISABLED:
            printk("\n*** received UART_RX_DISABLED\n");
            // uart_rx_enable(dev, rx_buf, RECEIVE_BUF_SIZE, RECEIVE_TIMEOUT);
            break;

        default:
            break;
    }
}

// keypad reads characters from serial consoles
// it acts as producer and sends them to led consumer using message queue
int keypad_init(keypad *keypad) {
    keypad->uart = DEVICE_DT_GET(DT_NODELABEL(uart0));
    strncpy(keypad->tx_buf, "Press 1-3 on nRF terminal to toggle LEDS 1-3 on DK\n", SEND_BUF_SIZE);
    if (uart_callback_set(keypad->uart, keypad_received_char, NULL)) {
        return 1;
    }
    if (uart_tx(keypad->uart, keypad->tx_buf, SEND_BUF_SIZE, SYS_FOREVER_MS)) {
        return 1;
    }
    if (uart_rx_enable(keypad->uart, keypad->rx_buf, RECEIVE_BUF_SIZE, RECEIVE_TIMEOUT)) {
        return 1;
    }

    return 0;
}
