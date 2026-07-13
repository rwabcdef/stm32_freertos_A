/*
 * timer2.c
 */

#include "main.h"
#include "timer2.h"

volatile uint16_t g_timer2Tick = 0;

static TIM_HandleTypeDef htim2;

void timer2_init(void)
{
  __HAL_RCC_TIM2_CLK_ENABLE();

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = (SystemCoreClock / 1000000) - 1;   /* 1 MHz timer clock */
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1000 - 1;                             /* 1000 counts -> 1 kHz tick */
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  HAL_TIM_Base_Start_IT(&htim2);

  HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2)
  {
    g_timer2Tick++;
  }
}
