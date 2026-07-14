/*
 * timer3.h
 *
 * One-shot 200 ms hardware timer used to switch the green LED off
 * a short time after it's turned on (e.g. for a "message received" flash).
 */

#ifndef TIMER3_H_
#define TIMER3_H_

#ifdef __cplusplus
extern "C" {
#endif

void timer3_init(void);

// (Re)starts the 200 ms one-shot countdown from zero. Safe to call again
// before it elapses - this just restarts the 200 ms window.
void timer3_startOneShot(void);

// Called by timer2's shared HAL_TIM_PeriodElapsedCallback when TIM3 elapses.
void timer3_handlePeriodElapsed(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER3_H_ */
