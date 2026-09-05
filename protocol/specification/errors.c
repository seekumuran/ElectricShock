#include "errors.h"

void es_stats_reset(
    ES_ProtocolStats *stats
) {
    stats->frames_received = 0;
    stats->frames_valid = 0;

    stats->crc_errors = 0;
    stats->sync_errors = 0;
    stats->length_errors = 0;
    stats->version_errors = 0;

    stats->duplicate_frames = 0;
    stats->lost_frames = 0;
}
