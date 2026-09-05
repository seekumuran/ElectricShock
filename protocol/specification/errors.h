#ifndef ELECTRIC_SHOCK_ERRORS_H
#define ELECTRIC_SHOCK_ERRORS_H

#include <stdint.h>

typedef struct {

    uint32_t frames_received;

    uint32_t frames_valid;

    uint32_t crc_errors;

    uint32_t sync_errors;

    uint32_t length_errors;

    uint32_t version_errors;

    uint32_t duplicate_frames;

    uint32_t lost_frames;

} ES_ProtocolStats;

void es_stats_reset(
    ES_ProtocolStats *stats
);

#endif
