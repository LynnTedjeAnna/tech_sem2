#include <stdio.h>
#include <string.h>

#include "unity.h"
#include "unity_test_module.h"
#include "watch_registers.h"

// leave resource_detector.h as last include!
#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to
// ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void watch_setUp(void)
{
}

void watch_tearDown(void)
{
    // This is run after EACH test
}

void test_setting_time_hours(void)
{
    const uint8_t hours = 0xA5;
    uint8_t time_bits_high = 0xA5;
    uint8_t time_bits_low = 0x5A;

    watch_registers_set_time_hours(&time_bits_low, &time_bits_high, hours);
    TEST_ASSERT_EQUAL_HEX8(0x55, time_bits_high);
    TEST_ASSERT_EQUAL_HEX8(0x5A, time_bits_low);
}

void test_get_time()
{
    const uint8_t hours = 11;
    const uint8_t minutes = 55;
    const uint8_t seconds = 42;
    uint8_t time_bits_low = 0;
    uint8_t time_bits_high = 0b00;

    watch_registers_set_time_seconds(&time_bits_low, &time_bits_high, seconds);
    watch_registers_set_time_minutes(&time_bits_low, &time_bits_high, minutes);
    watch_registers_set_time_hours(&time_bits_low, &time_bits_high, hours);

    uint8_t h;
    uint8_t m;
    uint8_t s;
    watch_registers_get_time(time_bits_low, time_bits_high, &h, &m, &s);
    TEST_ASSERT_EQUAL(hours, h);
    TEST_ASSERT_EQUAL(minutes, m);
    TEST_ASSERT_EQUAL(seconds, s);
}


void run_watch_tests()
{
    UnityRegisterSetupTearDown( watch_setUp, watch_tearDown);

    MY_RUN_TEST(test_setting_time_hours);
    MY_RUN_TEST(test_get_time);

    UnityUnregisterSetupTearDown();
}
