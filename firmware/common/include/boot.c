#include "boot.h"

void es_boot_init(
    ES_BootStatus *boot
)
{
    boot->stage = ES_BOOT_RESET;

    boot->reset_count++;
    boot->boot_time_ms = 0;

    boot->memory_ok = 0;
    boot->gpio_ok = 0;
    boot->adc_ok = 0;
    boot->timer_ok = 0;
    boot->uart_ok = 0;
    boot->watchdog_ok = 0;
    boot->selftest_ok = 0;

    boot->ready = 0;
    boot->failed = 0;
}

void es_boot_stage(
    ES_BootStatus *boot,
    ES_BootStage stage
)
{
    boot->stage = stage;
}

void es_boot_mark_ok(
    ES_BootStatus *boot,
    ES_BootStage stage
)
{
    switch (stage) {

    case ES_BOOT_MEMORY:
        boot->memory_ok = 1;
        break;

    case ES_BOOT_GPIO:
        boot->gpio_ok = 1;
        break;

    case ES_BOOT_ADC:
        boot->adc_ok = 1;
        break;

    case ES_BOOT_TIMER:
        boot->timer_ok = 1;
        break;

    case ES_BOOT_UART:
        boot->uart_ok = 1;
        break;

    case ES_BOOT_WATCHDOG:
        boot->watchdog_ok = 1;
        break;

    case ES_BOOT_SELFTEST:
        boot->selftest_ok = 1;
        break;

    default:
        break;
    }
}

void es_boot_mark_failed(
    ES_BootStatus *boot,
    ES_BootStage stage
)
{
    boot->stage = stage;
    boot->failed = 1;
    boot->ready = 0;
}

uint8_t es_boot_is_ready(
    const ES_BootStatus *boot
)
{
    return boot->ready &&
           !boot->failed;
}
