// Init_Timers.c
// Runs on MSP432
// Robotic Hand - Timer Initializations
//
// TIMER ASSIGNMENT:
//   TimerA1: ThumbR(CCR1) Thumb(CCR2) Pointer(CCR3) Middle(CCR4)
//   TimerA3: PinkyRing(CCR1) Rotate(CCR3)
//
// PWM CALCULATIONS at 6MHz (SMCLK/8):
//   CCR0 = 119999  -> 20ms period (50Hz)
//   Angle 0   = ~700  counts
//   Angle 90  = ~3500 counts
//   Angle 180 = ~6300 counts

#include "msp.h"

// ------------TimerA1_Init------------
// ThumbR  TA1.1 CCR1
// Thumb   TA1.2 CCR2
// Pointer TA1.3 CCR3
// Middle  TA1.4 CCR4
void TimerA1_Init(void)
{
    TA1CTL   = 0x0280;   // SMCLK /8 = 6MHz stop mode clear
    TA1R     = 0;
    TA1EX0   = 0x0000;
    TA1CCR0  = 119999;   // 20ms period

    TA1CCTL1 = 0x00E0;   // output mode 7  ThumbR
    TA1CCR1  = 3500;     // 90 deg home

    TA1CCTL2 = 0x00E0;   // output mode 7  Thumb
    TA1CCR2  = 3500;

    TA1CCTL3 = 0x00E0;   // output mode 7  Pointer
    TA1CCR3  = 3500;

    TA1CCTL4 = 0x00E0;   // output mode 7  Middle
    TA1CCR4  = 3500;

    TA1CTL  |= 0x0010;   // start Up mode
}

// ------------TimerA3_Init------------
// PinkyRing TA3.1 CCR1
// Rotate    TA3.3 CCR3
void TimerA3_Init(void)
{
    TA3CTL   = 0x0280;   // SMCLK /8 = 6MHz stop mode clear
    TA3R     = 0;
    TA3EX0   = 0x0000;
    TA3CCR0  = 119999;   // 20ms period

    TA3CCTL1 = 0x00E0;   // output mode 7  PinkyRing
    TA3CCR1  = 3500;

    TA3CCTL3 = 0x00E0;   // output mode 7  Rotate
    TA3CCR3  = 3500;

    TA3CTL  |= 0x0010;   // start Up mode
}
