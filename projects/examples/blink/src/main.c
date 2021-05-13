#include "stm8s.h"
#include "stm8s_it.h"

#include <precise_delay.h>

void Delay(uint16_t nCount);

void main(void)
{
  // Speed up to 16MHz with HSI
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  // CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);

  CLK_CCOConfig(CLK_OUTPUT_CPU);

  // Configure GPIO
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1)
  {
    for (int i = 0; i < 200; i++)
      delay_cys(US_TO_CY(1000));

    GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
  }
}