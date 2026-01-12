/**
 * @file infusion_platform.h
 * @brief Small platform helpers (RTOS-aware delay, ISR detection).
 *
 * NOTE: Header-only to avoid requiring CubeIDE regeneration for new .c files.
 */
#ifndef INFUSION_PLATFORM_H
#define INFUSION_PLATFORM_H

#include "stm32h7xx_hal.h"

/* FreeRTOS headers are safe to include project-wide in this firmware. */
#include "FreeRTOS.h"
#include "task.h"

static inline int Infusion_InIsr(void) {
  /* Non-zero IPSR => currently in exception/ISR context. */
  return (__get_IPSR() != 0U);
}

/**
 * @brief Enable DWT cycle counter for high-resolution timestamping.
 * @note Safe to call multiple times.
 */
static inline void Infusion_CycleCounterInit(void) {
  /* Enable trace */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  /* Reset and enable cycle counter */
  DWT->CYCCNT = 0U;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief Read current cycle count (wraps at 2^32).
 */
static inline uint32_t Infusion_CycleCount(void) {
  return DWT->CYCCNT;
}

/**
 * @brief Convert CPU cycles to microseconds using SystemCoreClock.
 * @note Uses integer math; will truncate fractional microseconds.
 */
static inline uint32_t Infusion_CyclesToUs(uint32_t cycles) {
  if (SystemCoreClock == 0U) {
    return 0U;
  }
  return (uint32_t)(((uint64_t)cycles * 1000000ULL) / (uint64_t)SystemCoreClock);
}

/**
 * @brief Delay for ms in a way that is safe both before and after the scheduler starts.
 *
 * Rules:
 * - In task context AFTER scheduler start: uses vTaskDelay (yields CPU).
 * - Before scheduler start: uses HAL_Delay.
 * - In ISR context: does NOT block (returns immediately). Delays in ISRs are forbidden.
 */
static inline void Infusion_DelayMs(uint32_t ms) {
  if (ms == 0U) {
    return;
  }

  if (Infusion_InIsr()) {
    /* Forbidden: do not block inside ISR. */
    return;
  }

  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) {
    vTaskDelay(pdMS_TO_TICKS(ms));
  } else {
    HAL_Delay(ms);
  }
}

#endif /* INFUSION_PLATFORM_H */


