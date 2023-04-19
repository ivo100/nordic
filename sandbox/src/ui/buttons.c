#include "buttons.h"

struct btns {
    struct gpio_dt_spec btn;
} _btns[4] = {
    {GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(sw2), gpios), 0},
    {GPIO_DT_SPEC_GET(DT_ALIAS(sw3), gpios), 0}};

static struct gpio_callback button_cb_data;
static buttons_cb cb;

static void _button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    // Important note!
    // Code in ISR runs at a high priority, therefore, it should be written with timing in mind.
    // Too lengthy or too complex tasks should not be performed by an ISR, they should be deferred to a thread or a workqueue
    //
    printk("pins %d\n", pins);
    printk("button %s pressed\n", dev->name);
    if (cb != NULL) {
        printk("callback \n");
        //*cb->handler;
    }
}

int buttons_init(buttons_cb callback) {
    printk("buttons_init enter\n");
    for (int i = 0; i < 4; i++) {
        struct gpio_dt_spec *button = &_btns[i].btn;
        printk("button pin %d\n", button->pin);
        if (!device_is_ready((button->port))) {
            return 1;
        }
        if (gpio_pin_configure_dt(button, GPIO_INPUT) < 0) {
            printk("error - button configure\n");
            return 2;
        }
        if (gpio_pin_interrupt_configure_dt(button, GPIO_INT_EDGE_TO_ACTIVE) < 0) {
            printk("error - pin interrupt callback configure\n");
            return 3;
        }

        gpio_init_callback(&button_cb_data, _button_pressed, BIT(button->pin));

        gpio_add_callback(button->port, &button_cb_data);

        cb = callback;
    }
    printk("buttons_init exit\n");
    return 0;
}
