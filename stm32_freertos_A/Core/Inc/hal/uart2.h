/*
 * uart2.h
 */

#ifndef UART2_H_
#define UART2_H_

#define UART2__BUFFER_LEN 64

#include "stm32f4xx_hal.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart2;

void uart2_init(void);
bool uart2_frameRx(char* data, uint16_t* dataLen);

#ifdef __cplusplus
}
#endif

#endif /* UART2_H_ */
