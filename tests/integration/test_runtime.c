#include <assert.h>
#include <stdio.h>

#include "runtime.h"

int main(void)
{
    ES_Runtime runtime;

    es_runtime_init(
        &runtime
    );

    assert(
        es_runtime_get_sequence(
            &runtime
        ) == 0
    );

    /*
     * 0 ms -> first frame
     */
    es_runtime_tick(
        &runtime,
        0
    );

    assert(
        runtime.stats.frames_generated == 1
    );

    /*
     * 1 ms -> input update
     */
    es_runtime_tick(
        &runtime,
        1
    );

    assert(
        runtime.stats.input_ticks >= 1
    );

    /*
     * 4 ms -> second frame
     */
    es_runtime_tick(
        &runtime,
        4
    );

    assert(
        runtime.stats.frames_generated >= 2
    );

    printf(
        "runtime integration: PASS\n"
    );

    return 0;
}
