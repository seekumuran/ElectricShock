#include "runtime.h"

/*
 * PCB hardware abstraction.
 */
extern void pcb_hardware_init(void);
extern uint32_t pcb_millis(void);
extern int pcb_uart_available(void);
extern uint8_t pcb_uart_read(void);
extern void pcb_uart_write(uint8_t byte);

void es_pcb_main(void)
{
    ES_Runtime runtime;

    pcb_hardware_init();

    es_runtime_init(
        &runtime
    );

    while (1) {

        uint32_t now;

        now = pcb_millis();

        es_runtime_tick(
            &runtime,
            now
        );

        while (pcb_uart_available()) {

            uint8_t byte =
                pcb_uart_read();

            es_runtime_rx_byte(
                &runtime,
                byte
            );
        }

        {
            uint8_t byte;

            while (es_transport_tx_pop(
                &runtime.transport,
                &byte)) {

                pcb_uart_write(byte);
            }
        }
    }
}
