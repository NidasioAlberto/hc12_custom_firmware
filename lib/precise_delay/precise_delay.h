#include "stm8s.h"

#ifndef __PRECISE_DELAY_H
#define __PRECISE_DELAY_H

#ifndef FCLK
#define FCLK 16000000
#endif

// Converts microseconds to cycles, 12288us MAX and 1us MIN
#define US_TO_CY(x) (x * (FCLK / 1000000UL) / 3) - 4

/// Delays the code by running nop operations, use with the macro US_TO_CY
void delay_cys(uint16_t cycles)
{
    cycles;

    // The caller has to:
    //   put the parameter on the stack (2 cycles)
    //   call the function (4 cycles)

    // Load cycles parameter from stack into register X
    __asm__("ldw x, (0x03, sp)\n"); // 2

    __asm__("nop\n"); // 1
    __asm__("delay_loop:\n");
    __asm__("decw x\n");          // 1
    __asm__("jrne delay_loop\n"); // 1 (2 with jump)
    __asm__("nop");               // 1

    // 4 cycles for ret
    // 2 cycles to free the stack of the parameter afterwards (with a pop)
}

#define delay_us(us) delay_cys(US_TO_CY(us))

// TODO: calculate the correct cycle count
void delay_ms(uint16_t ms)
{
    for (; ms > 0; ms--)
        delay_cys(US_TO_CY(1000));
}

#endif