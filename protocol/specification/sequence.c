#include "sequence.h"

void es_sequence_init(
    ES_SequenceTracker *tracker
) {
    tracker->expected = 0;
    tracker->initialized = 0;
}


ES_SequenceResult es_sequence_check(
    ES_SequenceTracker *tracker,
    uint16_t sequence
) {
    if (!tracker->initialized) {

        tracker->expected =
            (uint16_t)(sequence + 1);

        tracker->initialized = 1;

        return ES_SEQUENCE_FIRST;
    }

    if (sequence == tracker->expected) {

        tracker->expected =
            (uint16_t)(sequence + 1);

        return ES_SEQUENCE_NEXT;
    }

    /*
     * Previous packet received again.
     */

    if ((uint16_t)(sequence + 1) == tracker->expected) {
        return ES_SEQUENCE_DUPLICATE;
    }

    /*
     * Anything else means one or more
     * packets may have been lost.
     */

    tracker->expected =
        (uint16_t)(sequence + 1);

    return ES_SEQUENCE_LOST;
}
