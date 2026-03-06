/*
 * Copyright (c) 2026
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_bt_profile_report

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <drivers/behavior.h>

#include <dt-bindings/zmk/keys.h>
#include <zmk/behavior.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)

#include <zmk/behavior_queue.h>
#include <zmk/ble.h>

#define KP_BEHAVIOR_DEV DEVICE_DT_NAME(DT_NODELABEL(kp))
#define TAP_TIME_MS 15U
#define INTER_KEY_WAIT_MS 10U

static int queue_tap(struct zmk_behavior_binding_event *event, uint32_t keycode,
                     uint32_t *delay_ms) {
    struct zmk_behavior_binding binding = {
        .behavior_dev = KP_BEHAVIOR_DEV,
        .param1 = keycode,
        .param2 = 0,
    };

    int ret = zmk_behavior_queue_add(event, binding, true, *delay_ms);
    if (ret < 0) {
        return ret;
    }

    ret = zmk_behavior_queue_add(event, binding, false, TAP_TIME_MS);
    if (ret < 0) {
        return ret;
    }

    *delay_ms = INTER_KEY_WAIT_MS;
    return 0;
}

static uint32_t digit_for_profile_index(int profile_index) {
    static const uint32_t profile_digits[] = {N1, N2, N3, N4, N5, N6, N7, N8, N9};

    if (profile_index >= 0 && profile_index < ARRAY_SIZE(profile_digits)) {
        return profile_digits[profile_index];
    }

    return N0;
}

static int on_bt_profile_report_binding_pressed(struct zmk_behavior_binding *binding,
                                                struct zmk_behavior_binding_event event) {
    static const uint32_t prefix[] = {LS(P), R, O, F, I, L, E, SPACE, LS(B), LS(T), SPACE};
    int profile_index = zmk_ble_active_profile_index();
    uint32_t delay_ms = 0;

    ARG_UNUSED(binding);

    if (profile_index < 0 || profile_index >= ZMK_BLE_PROFILE_COUNT) {
        LOG_WRN("Invalid active profile index: %d", profile_index);
        return ZMK_BEHAVIOR_OPAQUE;
    }

    for (int i = 0; i < ARRAY_SIZE(prefix); i++) {
        int ret = queue_tap(&event, prefix[i], &delay_ms);
        if (ret < 0) {
            LOG_ERR("Failed to queue prefix key %d: %d", i, ret);
            return ret;
        }
    }

    int ret = queue_tap(&event, digit_for_profile_index(profile_index), &delay_ms);
    if (ret < 0) {
        LOG_ERR("Failed to queue profile digit: %d", ret);
        return ret;
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

#else

static int on_bt_profile_report_binding_pressed(struct zmk_behavior_binding *binding,
                                                struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);
    return ZMK_BEHAVIOR_OPAQUE;
}

#endif /* !CONFIG_ZMK_SPLIT || CONFIG_ZMK_SPLIT_ROLE_CENTRAL */

static int on_bt_profile_report_binding_released(struct zmk_behavior_binding *binding,
                                                 struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_bt_profile_report_driver_api = {
    .locality = BEHAVIOR_LOCALITY_CENTRAL,
    .binding_pressed = on_bt_profile_report_binding_pressed,
    .binding_released = on_bt_profile_report_binding_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif /* IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA) */
};

BEHAVIOR_DT_INST_DEFINE(0, NULL, NULL, NULL, NULL, POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,
                        &behavior_bt_profile_report_driver_api);

#endif /* DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT) */
