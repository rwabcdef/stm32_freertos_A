/*
 * uart2.h
 */

#ifndef UART2_H_
#define UART2_H_

#include "main.h"
#include <stdbool.h>

#define UART_MSG_TYPE__FRAME_RX 1

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart2;

void uart2_init(void);

// Non-blocking bare metal read.
bool uart2_frameRx(char* data, uint16_t* dataLen);

// Blocking write - returns once the whole buffer has been transmitted.
uint8_t uart2_writeBlocking(char* buffer);

#ifdef __cplusplus
}
#endif

#endif /* UART2_H_ */
