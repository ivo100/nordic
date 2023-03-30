
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024

/* scheduling priority used by each thread */
#define PRIORITY 7

/* delay between greetings (in ms) */
#define SLEEPTIME 5000

K_THREAD_STACK_DEFINE(threadA_stack_area, STACKSIZE);
static struct k_thread threadA_data;

/* Defining a timer */
struct k_timer my_timer;
extern void my_expiry_function(struct k_timer *timer_id);

/* threadA is a static thread that is spawned automatically */

uint64_t start_time;

void threadA(void *dummy1, void *dummy2, void *dummy3) {
    ARG_UNUSED(dummy1);
    ARG_UNUSED(dummy2);
    ARG_UNUSED(dummy3);

    printk("thread_a: thread started \n");

    while (1) {
        // printk("thread_a: thread loop \n");
        k_msleep(SLEEPTIME);
    }
}

void my_expiry_function(struct k_timer *timer_id) {
    uint64_t start = start_time;
    int64_t delta = k_uptime_delta(&start);
    printk(">>>>> timer expired, elapsed time since start: %lld\n", delta);
}

void run_timer(void) {
    start_time = k_uptime_get();
    printk("run_timer start %lld\n", start_time);
    k_thread_create(&threadA_data, threadA_stack_area,
                    K_THREAD_STACK_SIZEOF(threadA_stack_area),
                    threadA, NULL, NULL, NULL,
                    PRIORITY, 0, K_FOREVER);

    k_thread_name_set(&threadA_data, "thread_a");

    k_timer_init(&my_timer, my_expiry_function, NULL);

    k_timer_start(&my_timer, K_MSEC(7000), K_MSEC(2000));

    k_thread_start(&threadA_data);
}