#include "keypad.h"

#include <string.h>
#include <zephyr/sys/printk.h>

extern struct k_msgq queue;

/*  callback function for UART */
static int keypad_received_event(const struct device *dev, struct uart_event *evt, void *keyp) {
    switch (evt->type) {
        case UART_RX_RDY:
            if ((evt->data.rx.len) == 1) {
                // received 1 char - send it to the queue
                uint8_t ch = evt->data.rx.buf[evt->data.rx.offset];
                if (k_msgq_put(&queue, &ch, K_NO_WAIT)) {
                    printk("k_msgq_put error\n");
                }
            }
            break;
        case UART_RX_DISABLED:
            // reenable
            uart_rx_enable(dev, ((keypad *)keyp)->rx_buf, RECEIVE_BUF_SIZE, RECEIVE_TIMEOUT);
            break;

        default:
            break;
    }
}

// keypad reads characters from the serial consoles
// it acts as producer and sends them to led consumer using message queue
int keypad_init(keypad *keypad) {
    keypad->uart = DEVICE_DT_GET(DT_NODELABEL(uart0));
    strncpy(keypad->tx_buf, "\nPress 1-3 on nRF terminal to toggle LEDS 1-3 on DK\n", SEND_BUF_SIZE);
    if (uart_callback_set(keypad->uart, keypad_received_event, keypad)) {
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
