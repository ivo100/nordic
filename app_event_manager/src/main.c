/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <app_event_manager.h>
#include <config_event.h>
#include <zephyr/logging/log.h>

#define MODULE main

#define LOG_LEVEL 3
LOG_MODULE_REGISTER(MODULE, LOG_LEVEL);

#define INIT_VALUE1 3

void main(void) {
    char *version = "v1.0";

    for (int i = 0; i < 10; i++) {
        // printk("APP STARTS %s, i %d\n", version, i);
        // INF is level 4
        // LOG_INF("====INFO APP STARTS %s, i %d", version, i);
        LOG_WRN("====WARN APP STARTS %s, i %d", version, i);
        k_msleep(1000);
    }

    if (app_event_manager_init()) {
        LOG_ERR("Application Event Manager not initialized");
    } else {
        struct config_event *event = new_config_event();
        event->init_value1 = INIT_VALUE1;
        APP_EVENT_SUBMIT(event);
    }
}
