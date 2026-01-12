/**
 * @file    CoreTest.c
 * @author  Radhakrishnan Rajaram
 * @version 1.0.0
 * @date    2025-09-04
 * @brief   CPU Core Self-Test implementation for POST
 * @copyright
 * Copyright (c) 2025 Aria Innovations Pvt Limited
 *
 * @details
 * This module verifies basic CPU ALU operations and simple RAM access during
 * Power-On Self-Test (POST). All tests use defined macros and safe patterns to
 * ensure firmware robustness and compliance with IEC 62304 and MISRA guidelines.
 */

#include "CoreTest.h"
#include <stdint.h>
#include <stdbool.h>

/* Test values and expected results */
#define CORETEST_VAL1                  (0x12345678UL)
#define CORETEST_VAL2                  (0x87654321UL)
#define CORETEST_EXPECTED_XOR          (CORETEST_VAL1 ^ CORETEST_VAL2)
#define CORETEST_EXPECTED_ANDNOT       ((~CORETEST_VAL1) & CORETEST_VAL2)
#define CORETEST_EXPECTED_SHIFT        (CORETEST_VAL1 >> 4U)
#define CORETEST_EXPECTED_ADD          (CORETEST_VAL1 + CORETEST_VAL2)
#define CORETEST_RAM_TEST_ADDR         (0x20000000UL)
#define CORETEST_RAM_TEST_PATTERN      (0xA5A5A5A5UL)

/**
 * @brief Execute CPU core test sequence.
 *
 * Performs a series of ALU and memory operations to ensure core CPU logic is
 * functioning correctly.
 *
 * @retval true  All test operations passed successfully.
 * @retval false A mismatch occurred during any operation.
 */
bool CoreTest_Run(void)
{
    volatile uint32_t val1 = CORETEST_VAL1;
    volatile uint32_t val2 = CORETEST_VAL2;
    volatile uint32_t result = 0U;
    volatile uint32_t * const pTestRam = (uint32_t *)CORETEST_RAM_TEST_ADDR;

    bool testPassed = true;

    /* XOR test */
    result = val1 ^ val2;
    if (result != CORETEST_EXPECTED_XOR)
    {
        testPassed = false;
    }

    /* AND-NOT test */
    if (testPassed == true)
    {
        result = (~val1) & val2;
        if (result != CORETEST_EXPECTED_ANDNOT)
        {
            testPassed = false;
        }
    }

    /* Right shift test */
    if (testPassed == true)
    {
        result = val1 >> 4U;
        if (result != CORETEST_EXPECTED_SHIFT)
        {
            testPassed = false;
        }
    }

    /* Add test */
    if (testPassed == true)
    {
        result = val1 + val2;
        if (result != CORETEST_EXPECTED_ADD)
        {
            testPassed = false;
        }
    }

    /* RAM read/write test */
    if (testPassed == true)
    {
        *pTestRam = CORETEST_RAM_TEST_PATTERN;
        if (*pTestRam != CORETEST_RAM_TEST_PATTERN)
        {
            testPassed = false;
        }
    }

    return testPassed;
}
