#ifndef ES_TRANSPORT_H
#define ES_TRANSPORT_H

#include <stdint.h>

#define ES_TX_BUFFER_SIZE 256
#define ES_RX_BUFFER_SIZE 256

typedef struct {
    uint8_t buffer[ES_TX_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} ES_TxBuffer;

typedef struct {
    uint8_t buffer[ES_RX_BUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} ES_RxBuffer;

typedef struct {
    ES_TxBuffer tx;
    ES_RxBuffer rx;

    uint32_t tx_bytes;
    uint32_t rx_bytes;

    uint32_t tx_overflow;
    uint32_t rx_overflow;
} ES_Transport;

void es_transport_init(ES_Transport *transport);

int es_transport_tx_push(
    ES_Transport *transport,
    uint8_t byte
);

int es_transport_tx_pop(
    ES_Transport *transport,
    uint8_t *byte
);

int es_transport_rx_push(
    ES_Transport *transport,
    uint8_t byte
);

int es_transport_rx_pop(
    ES_Transport *transport,
    uint8_t *byte
);

uint16_t es_transport_tx_available(
    const ES_Transport *transport
);

uint16_t es_transport_rx_available(
    const ES_Transport *transport
);

#endif
