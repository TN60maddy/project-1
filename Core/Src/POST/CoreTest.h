/**
 * @file    CoreTest.h
 * @author  Radhakrishnan Rajaram
 * @version 1.0.0
 * @date    2025-09-04
 * @brief   Header for CPU Core Self-Test during POST
 * @copyright
 * Copyright (c) 2025 Aria Innovations Pvt Limited
 */

#ifndef CORE_TEST_H
#define CORE_TEST_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Run CPU core self-test during POST.
 *
 * @return true if test passed, false otherwise.
 */
bool CoreTest_Run(void);

#ifdef __cplusplus
}
#endif

#endif /* CORE_TEST_H */
