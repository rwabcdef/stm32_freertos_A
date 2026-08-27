#ifndef PWM_HPP_
#define PWM_HPP_

#include <stdint.h>
#include "main.h"

enum pwmFreqValues : uint32_t
{
  PWM_FREQ_100HZ = 100U,
  PWM_FREQ_500HZ = 500U,
  PWM_FREQ_1KHZ = 1000U,
  PWM_FREQ_2KHZ = 2000U
};

// Sentinel for "no valid timer channel" - must not collide with a real
// TIM_CHANNEL_x value (TIM_CHANNEL_1 is 0, so 0 cannot be used for this).
static constexpr uint32_t PWM_CHANNEL_INVALID = 0xFFFFFFFFU;

class PWM
{
  public:
    PWM(GPIO_TypeDef* port, uint16_t pin, pwmFreqValues frequency);

    void init();
    void setPercent(uint8_t percent);
    uint8_t getPercent() const;

  private:
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t channel;
    uint8_t percent;

    static TIM_HandleTypeDef timer;
    static uint32_t configuredFrequency;
    static bool initialized;

    static uint32_t timerClockHz();
    static void initialize(GPIO_TypeDef* port, uint16_t pin,
                 uint32_t channel, pwmFreqValues frequency);
    static uint32_t channelForPin(GPIO_TypeDef* port, uint16_t pin);
};

#endif
