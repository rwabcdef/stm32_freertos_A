/*
 * uart2.c
 */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "uart2.h"
#include <string.h>

UART_HandleTypeDef huart2;

static volatile char rx_byte;
static volatile char rxBuffer[UART2__BUFFER_LEN];
static volatile uint16_t rxLen;
static volatile bool frameRx;

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);
}

// called by HAL_UART_IRQHandler, i.e., called in the interrupt
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if(rxLen < (UART2__BUFFER_LEN - 1))
        {
        	rxBuffer[rxLen++] = rx_byte;
        	if(rx_byte == '\n')
        	{
        		// end of frame
        		frameRx = true;
        	}
        	if(rxLen >= UART2__BUFFER_LEN)
        	{
        		// buffer full
        	}
        }

        HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_byte, 1); // re-arm interrupt
    }
}

void uart2_init(void)
{
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // PA2 = TX, PA3 = RX
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 19200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    memset((void*)rxBuffer, 0, UART2__BUFFER_LEN);
    rxLen = 0;
    frameRx = false;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }

    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

    HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_byte, 1);  // start RX interrupt
}

bool uart2_frameRx(char* data, uint16_t* dataLen)
{
    bool ret = false;

    HAL_NVIC_DisableIRQ(USART2_IRQn);   // lock

    if (frameRx)
    {
        frameRx = false;

        strncpy(data, (const char*)rxBuffer, rxLen);
        *dataLen = rxLen;

        memset((void*)rxBuffer, 0, UART2__BUFFER_LEN);
        rxLen = 0;

        ret = true;
    }

    HAL_NVIC_EnableIRQ(USART2_IRQn);    // unlock

    return ret;
}
