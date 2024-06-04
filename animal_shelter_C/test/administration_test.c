//
// Created by Lynn Tedje Anna Meindertsma on 22 Mar 2024.
//
#include <string.h>

#include "../src/administration.h"
#include "unity.h"
#include "unity_test_module.h"

// leave resource_detector.h as last include!
#include "resource_detector.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void administration_setUp(void) {
    // This is run before EACH test
}

void test_addAnimal_emptyArray(void) {
    Animal test; size_t test_nnoap;
    int res = add_animal(&test, NULL, 10, 0, &test_nnoap);
    TEST_ASSERT_EQUAL(res, -1);
}

void test_addAnimal_fullArray(void) {
    Animal test; size_t test_nnoap; int animal_array[10];
    int res = add_animal(&test, (Animal *) animal_array, 10, 10, &test_nnoap);
    TEST_ASSERT_EQUAL(res, -1);
}

void administration_tearDown(void)
{
    // This is run after EACH test
}

void test_EmptyTest(void)
{
    TEST_ASSERT_EQUAL(1, 0);
}

void run_administration_tests(void)
{
    UnityRegisterSetupTearDown( administration_setUp, administration_tearDown);

    MY_RUN_TEST(test_EmptyTest);
    MY_RUN_TEST(test_addAnimal_emptyArray);
    MY_RUN_TEST(test_addAnimal_fullArray);

    UnityUnregisterSetupTearDown();
}
