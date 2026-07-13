/*
 * timer2.h
 */

#ifndef TIMER2_H_
#define TIMER2_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint16_t g_timer2Tick;

void timer2_init(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER2_H_ */
