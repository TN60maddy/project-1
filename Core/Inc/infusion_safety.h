/**
 * @file infusion_safety.h
 * @brief Minimal safety specification (design constraints) for medical-grade firmware.
 *
 * This header is intentionally short and practical. It documents project-wide rules
 * that must be followed for determinism and safety.
 */
#ifndef INFUSION_SAFETY_H
#define INFUSION_SAFETY_H

/* =========================
 * FreeRTOS / IRQ PRIORITIES
 * =========================
 *
 * - Any ISR that calls a FreeRTOS *FromISR API MUST have NVIC priority numerically
 *   >= configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY.
 * - ISRs with priority numerically < configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
 *   MUST NOT call FreeRTOS APIs.
 *
 * Project policy:
 * - Use priority 5 for "RTOS-aware" peripheral ISRs unless a stronger reason exists.
 */

/* =========================
 * WATCHDOG POLICY
 * =========================
 * - Watchdog is expected to be enabled in production.
 * - All long-running tasks must refresh the watchdog (or feed a dedicated watchdog task).
 * - Any unrecoverable hardware fault must stop actuators and then allow watchdog reset.
 */

/* =========================
 * ISR RULES (HARD)
 * =========================
 * - Do not call blocking HAL APIs from ISR (e.g., HAL_I2C_*, HAL_UART_Transmit with long timeouts).
 * - Do not call HAL_Delay() from ISR.
 * - Keep ISR work minimal: capture state, notify task, return.
 */

/* =========================
 * I2C BUS RULES (HARD)
 * =========================
 * - Never use HAL_MAX_DELAY on safety-relevant buses.
 * - All I2C operations must use bounded timeouts and return errors on timeout.
 * - For shared I2C buses behind a mux: channel select + transfer must be atomic under a mutex.
 */

/* Default timeouts (ms) - tune per board bringup/EMI testing. */
#define INF_I2C_TIMEOUT_MS_DEFAULT        (100U)
#define INF_I2C_TIMEOUT_MS_INIT           (200U)
#define INF_EEPROM_WRITE_CYCLE_DELAY_MS   (7U)

#endif /* INFUSION_SAFETY_H */


