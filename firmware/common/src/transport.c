#include "transport.h"

static uint16_t next_tx_index(uint16_t index)
{
    return (uint16_t)(
        (index + 1) % ES_TX_BUFFER_SIZE
    );
}

static uint16_t next_rx_index(uint16_t index)
{
    return (uint16_t)(
        (index + 1) % ES_RX_BUFFER_SIZE
    );
}

void es_transport_init(ES_Transport *transport)
{
    transport->tx.head = 0;
    transport->tx.tail = 0;

    transport->rx.head = 0;
    transport->rx.tail = 0;

    transport->tx_bytes = 0;
    transport->rx_bytes = 0;

    transport->tx_overflow = 0;
    transport->rx_overflow = 0;
}

int es_transport_tx_push(
    ES_Transport *transport,
    uint8_t byte
)
{
    uint16_t next;

    next = next_tx_index(transport->tx.head);

    if (next == transport->tx.tail) {
        transport->tx_overflow++;
        return 0;
    }

    transport->tx.buffer[
        transport->tx.head
    ] = byte;

    transport->tx.head = next;
    transport->tx_bytes++;

    return 1;
}

int es_transport_tx_pop(
    ES_Transport *transport,
    uint8_t *byte
)
{
    if (transport->tx.tail ==
        transport->tx.head)
        return 0;

    *byte = transport->tx.buffer[
        transport->tx.tail
    ];

    transport->tx.tail =
        next_tx_index(transport->tx.tail);

    return 1;
}

int es_transport_rx_push(
    ES_Transport *transport,
    uint8_t byte
)
{
    uint16_t next;

    next = next_rx_index(transport->rx.head);

    if (next == transport->rx.tail) {
        transport->rx_overflow++;
        return 0;
    }

    transport->rx.buffer[
        transport->rx.head
    ] = byte;

    transport->rx.head = next;
    transport->rx_bytes++;

    return 1;
}

int es_transport_rx_pop(
    ES_Transport *transport,
    uint8_t *byte
)
{
    if (transport->rx.tail ==
        transport->rx.head)
        return 0;

    *byte = transport->rx.buffer[
        transport->rx.tail
    ];

    transport->rx.tail =
        next_rx_index(transport->rx.tail);

    return 1;
}

uint16_t es_transport_tx_available(
    const ES_Transport *transport
)
{
    if (transport->tx.head >= transport->tx.tail)
        return transport->tx.head -
               transport->tx.tail;

    return ES_TX_BUFFER_SIZE -
           transport->tx.tail +
           transport->tx.head;
}

uint16_t es_transport_rx_available(
    const ES_Transport *transport)
{
    if (transport->rx.head >= transport->rx.tail)
        return transport->rx.head -
               transport->rx.tail;

    return ES_RX_BUFFER_SIZE -
           transport->rx.tail +
           transport->rx.head;
}
