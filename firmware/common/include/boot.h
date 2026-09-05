#ifndef ES_BOOT_H
#define ES_BOOT_H

#include <stdint.h>

typedef enum {
    ES_BOOT_RESET = 0,
    ES_BOOT_CLOCK,
    ES_BOOT_MEMORY,
    ES_BOOT_GPIO,
    ES_BOOT_ADC,
    ES_BOOT_TIMER,
    ES_BOOT_UART,
    ES_BOOT_WATCHDOG,
    ES_BOOT_SELFTEST,
    ES_BOOT_READY,
    ES_BOOT_FAILED
} ES_BootStage;

typedef struct {
    ES_BootStage stage;

    uint32_t reset_count;
    uint32_t boot_time_ms;

    uint8_t memory_ok;
    uint8_t gpio_ok;
    uint8_t adc_ok;
    uint8_t timer_ok;
    uint8_t uart_ok;
    uint8_t watchdog_ok;
    uint8_t selftest_ok;

    uint8_t ready;
    uint8_t failed;
} ES_BootStatus;

void es_boot_init(
    ES_BootStatus *boot
);

void es_boot_stage(
    ES_BootStatus *boot,
    ES_BootStage stage
);

void es_boot_mark_ok(
    ES_BootStatus *boot,
    ES_BootStage stage
);

void es_boot_mark_failed(
    ES_BootStatus *boot,
    ES_BootStage stage
);

uint8_t es_boot_is_ready(
    const ES_BootStatus *boot
);

#endif
