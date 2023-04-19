/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "sample_module.h"

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(MODULE_NAME, CONFIG_SAMPLE_MODULE_LOG_LEVEL);

const char *sample_module_name_get(void) {
    printk("======= sample_module_name_get %s  \n", STRINGIFY(MODULE_NAME));
    printk("======= CONFIG_SAMPLE_MODULE_LOG_LEVEL %s  \n", STRINGIFY(CONFIG_SAMPLE_MODULE_LOG_LEVEL));
    return STRINGIFY(MODULE_NAME);
}

void sample_module_func(void) {
    LOG_INF("log in test_module %d", 11);
}
