// Init_Ports.c
// Runs on MSP432
// Robotic Hand - Port Initializations
//
// PIN ASSIGNMENT:
//   ThumbR   P7.7  TA1.1
//   Thumb    P7.6  TA1.2
//   Pointer  P7.5  TA1.3
//   Middle   P7.4  TA1.4
//   PinkyRing P10.5 TA3.1
//   Rotate   P9.2  TA3.3

#include "msp.h"

// ------------Port7_Init------------
// P7.4 = TA1.4  Middle
// P7.5 = TA1.3  Pointer
// P7.6 = TA1.2  Thumb
// P7.7 = TA1.1  ThumbR
void Port7_Init(void)
{
    P7DIR  |=  0xF0;   // 11110000  bits 4-7 outputs
    P7SEL0 |=  0xF0;   // TimerA1 alternate function
    P7SEL1 &= ~0xF0;
}

// ------------Port9_Init------------
// P9.2 = TA3.3  Rotate
void Port9_Init(void)
{
    P9DIR  |=  0x04;   // 00000100  bit 2 output
    P9SEL0 |=  0x04;   // TimerA3 alternate function
    P9SEL1 &= ~0x04;
}

// ------------Port10_Init------------
// P10.5 = TA3.1  PinkyRing
void Port10_Init(void)
{
    P10DIR  |=  0x20;   // 00100000  bit 5 output
    P10SEL0 |=  0x20;   // TimerA3 alternate function
    P10SEL1 &= ~0x20;
}
