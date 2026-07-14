/*
 * timer3.c
 */

#include "main.h"
#include "timer3.h"

#define TIMER3_ONESHOT_PERIOD_MS 200

static TIM_HandleTypeDef htim3;

void timer3_init(void)
{
  __HAL_RCC_TIM3_CLK_ENABLE();

  // TIM3 is on APB1; its actual clock is 2x PCLK1 whenever the APB1
  // prescaler isn't 1 (standard STM32F4 timer clock rule).
  uint32_t timClk = HAL_RCC_GetPCLK1Freq();
  RCC_ClkInitTypeDef clkConfig;
  uint32_t flashLatency;
  HAL_RCC_GetClockConfig(&clkConfig, &flashLatency);
  if (clkConfig.APB1CLKDivider != RCC_HCLK_DIV1)
  {
    timClk *= 2;
  }

  // 10 kHz counting clock (0.1 ms resolution) so the period register stays
  // well within TIM3's 16-bit range for any of the durations we care about.
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = (timClk / 10000) - 1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = (TIMER3_ONESHOT_PERIOD_MS * 10) - 1;  /* 200 ms */
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void timer3_startOneShot(void)
{
  __HAL_TIM_SET_COUNTER(&htim3, 0);
  __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
  HAL_TIM_Base_Start_IT(&htim3);
}

void TIM3_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim3);
}

void timer3_handlePeriodElapsed(void)
{
  HAL_TIM_Base_Stop_IT(&htim3); // one-shot: stop until re-triggered
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET); // green LED off
}
