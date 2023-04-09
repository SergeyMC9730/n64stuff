#pragma once

#include <stdint.h>

typedef struct uptime_t {
    double seconds;
    uint64_t milliseconds;
} uptime_t;

extern volatile uptime_t SystemUptime;

void __time_update(int a);