#include "stm8s.h"
#include "stdio.h"

#include <precise_delay.h>

#define PUTCHAR_PROTOTYPE int putchar(int c)
#define GETCHAR_PROTOTYPE int getchar(void)

void main(void)
{
  uint8_t count;

  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  UART1_DeInit();

  /**
		* UART1 configured as follow:
		*		- BaudRate = 115200 baud  
		*		- Word Length = 8 Bits
		*		- One Stop Bit
		*		- No parity
		*		- Receive and transmit enabled
		*		- UART1 Clock disabled
		*/
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
             UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  while (1)
  {
    printf("UART1 works (%u)\n\r", count);
    count++;
    delay_ms(1000);
  }
}

PUTCHAR_PROTOTYPE
{
  /* Write a character to the UART1 */
  UART1_SendData8(c);

  /* Loop until the end of transmission */
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
    ;

  return (c);
}

GETCHAR_PROTOTYPE
{
  char c = 0;

  /* Loop until the Read data register flag is SET */
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET)
    ;
  c = UART1_ReceiveData8();

  return (c);
}
