#include "PWM.hpp"

TIM_HandleTypeDef PWM::timer = {};
uint32_t PWM::configuredFrequency = 0U;
bool PWM::initialized = false;

uint32_t PWM::timerClockHz()
{
  RCC_ClkInitTypeDef clockConfig = {};
  uint32_t flashLatency = 0U;
  HAL_RCC_GetClockConfig(&clockConfig, &flashLatency);

  uint32_t pclk = HAL_RCC_GetPCLK1Freq();
  if(clockConfig.APB1CLKDivider != RCC_HCLK_DIV1)
  {
    pclk *= 2U;
  }
  return pclk;
}

void PWM::initialize(GPIO_TypeDef* port, uint16_t pin, uint32_t channel,
                     pwmFreqValues frequency)
{
  if(initialized)
  {
    return;
  }

  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_TIM4_CLK_ENABLE();

  timer.Instance = TIM4;
  timer.Init.Prescaler = (timerClockHz() / 1000000U) - 1U;
  timer.Init.CounterMode = TIM_COUNTERMODE_UP;
  timer.Init.Period = (1000000U / static_cast<uint32_t>(frequency)) - 1U;
  timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  HAL_TIM_PWM_Init(&timer);

  GPIO_InitTypeDef gpioConfig = {};
  gpioConfig.Pin = pin;
  gpioConfig.Mode = GPIO_MODE_AF_PP;
  gpioConfig.Pull = GPIO_NOPULL;
  gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;
  gpioConfig.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(port, &gpioConfig);

  TIM_OC_InitTypeDef outputConfig = {};
  outputConfig.OCMode = TIM_OCMODE_PWM1;
  outputConfig.Pulse = 0U;
  outputConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
  outputConfig.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&timer, &outputConfig, channel);
  HAL_TIM_PWM_Start(&timer, channel);

  initialized = true;
  configuredFrequency = static_cast<uint32_t>(frequency);
}

uint32_t PWM::channelForPin(GPIO_TypeDef* port, uint16_t pin)
{
  // Note: TIM_CHANNEL_1 == 0, so 0 cannot be used as the "no channel" sentinel.
  if(port != GPIOD)
  {
    return PWM_CHANNEL_INVALID;
  }

  switch(pin)
  {
    case GPIO_PIN_12: return TIM_CHANNEL_1;
    case GPIO_PIN_13: return TIM_CHANNEL_2;
    case GPIO_PIN_14: return TIM_CHANNEL_3;
    case GPIO_PIN_15: return TIM_CHANNEL_4;
    default: return PWM_CHANNEL_INVALID;
  }
}

PWM::PWM(GPIO_TypeDef* port, uint16_t pin, pwmFreqValues frequency)
: port(port), pin(pin), channel(channelForPin(port, pin)), percent(0U)
{
  configuredFrequency = static_cast<uint32_t>(frequency);
}

void PWM::init()
{
  if(channel != PWM_CHANNEL_INVALID)
  {
    initialize(port, pin, channel,
               static_cast<pwmFreqValues>(configuredFrequency));
  }
}

void PWM::setPercent(uint8_t value)
{
  if(channel == PWM_CHANNEL_INVALID)
  {
    return;
  }

  if(!initialized)
  {
    init();
  }

  if(value > 100U)
  {
    value = 100U;
  }

  percent = value;
  uint32_t pulse = (static_cast<uint32_t>(timer.Init.Period) + 1U) * percent / 100U;
  if(pulse > timer.Init.Period)
  {
    pulse = timer.Init.Period;
  }
  __HAL_TIM_SET_COMPARE(&timer, channel, pulse);
}

uint8_t PWM::getPercent() const
{
  return percent;
}
