
// #include <zephyr/sys/util.h>
// #include <zephyr/kernel.h>

//    40  		/* STEP 9 - Submit the work item to the workqueue instead of calling emulate_work() directly */
//    41  		/* Remember to comment out emulate_work(); */
//    42          emulate_work();
//    43: 		delta_time = k_uptime_delta(&time_stamp);
//    44          printk("thread0 yielding this round in %lld ms\n", delta_time);

// int64_t get_seconds() {
//     return k_uptime_get();
// }