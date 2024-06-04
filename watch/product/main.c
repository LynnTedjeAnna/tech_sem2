#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "watch.h"
#include "watch_device_simulator.h"

// leave resource_detector.h as last include!
#include "resource_detector.h"

int main(int argc, char* argv[])
{
    uint8_t hours = 11, minutes = 55, seconds = 42;

    watch_set_time_hours(hours);
    watch_set_time_minutes(minutes);
    watch_set_time_seconds(seconds);

    while (true)
    {
        watch_get_time(&hours, &minutes, &seconds);
        watch_device_simulator_print_time(hours, minutes, seconds);

        uint8_t number_seconds_update = 10;
        watch_device_simulator_increase_time(number_seconds_update);
        sleep(number_seconds_update);
    }

    return 0;
}
