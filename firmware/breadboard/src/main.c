#include "main.h"
#include "runtime.h"

/*
 * Hardware-specific functions.
 *
 * These are intentionally abstract until the
 * real MCU register layer is restored/adapted.
 */
extern void hardware_init(void);
extern uint32_t hardware_millis(void);
extern int hardware_uart_available(void);
extern uint8_t hardware_uart_read(void);
extern void hardware_uart_write(uint8_t byte);

void es_breadboard_main(void)
{
    ES_Runtime runtime;

    hardware_init();

    es_runtime_init(&runtime);

    while (1) {

        uint32_t now;

        now = hardware_millis();

        /*
         * Execute scheduled firmware work.
         */
        es_runtime_tick(
            &runtime,
            now
        );

        /*
         * Drain incoming serial data.
         */
        while (hardware_uart_available()) {

            uint8_t byte;

            byte = hardware_uart_read();

            es_runtime_rx_byte(
                &runtime,
                byte
            );
        }

        /*
         * Drain outgoing transport buffer.
         */
        {
            uint8_t byte;

            while (es_transport_tx_pop(
                &runtime.transport,
                &byte)) {

                hardware_uart_write(byte);
            }
        }
    }
}
