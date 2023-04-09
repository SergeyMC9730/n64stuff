#include "time.h"

volatile uptime_t SystemUptime;

void __time_update(int a) {
    SystemUptime.milliseconds++;
    SystemUptime.seconds = (double)SystemUptime.milliseconds / 10000.f;
}