// Init_Timers.c
// Runs on MSP432
// Robotic Arm State Machine - Timer Initializations
//
// TIMER ASSIGNMENT:
// -----------------------------------------------
// TimerA1: Servos 1-4
//   TA1.1 = Servo 1  (P7.7)   CCR1
//   TA1.2 = Servo 2  (P7.6)   CCR2
//   TA1.3 = Servo 3  (P7.5)   CCR3
//   TA1.4 = Servo 4  (P7.4)   CCR4
//
// TimerA3: Servos 5, 6, Hand, Rotate
//   TA3.1 = Servo 5  (P10.5)  CCR1
//   TA3.2 = Rotate   (P8.2)   CCR2
//   TA3.3 = Servo 6  (P9.2)   CCR3
//   TA3.4 = Hand     (P9.3)   CCR4
//
// SERVO PWM CALCULATIONS:
// -----------------------------------------------
// Clock source : SMCLK = 48MHz
// Prescaler    : /8 = 6MHz
// Period       : 20ms (50Hz)
//   counts = 20ms x 6MHz = 120,000  ->  CCR0 = 119,999
//
// Pulse width -> CCR value (1 count = 0.1667us at 6MHz):
//   MIN  ( 0 deg) : 1.0ms =  6,000 counts
//   MID  (90 deg) : 1.5ms =  9,000 counts  <- home
//   MAX  (180 deg): 2.0ms = 12,000 counts
//
//   Hand OPEN  : 6,000  (MIN)
//   Hand CLOSE : 12,000 (MAX)
//
// Movement increment per command: 1000 counts (~30 deg)
// -----------------------------------------------

#include "msp.h"

// ------------TimerA1_Init------------
// Servos 1-4  CCR1-CCR4
// Input: none
// Output: none
void TimerA1_Init(void)
{
    TA1CTL   = 0x0280;   // SMCLK, /8 = 6MHz, stop mode, clear TAR
    TA1R     = 0;        // clear timer count
    TA1EX0   = 0x0000;   // additional /1

    TA1CCR0  = 119999;   // 20ms period at 6MHz

    TA1CCTL1 = 0x00E0;   // output mode 7 (Reset/Set)  Servo 1
    TA1CCR1  = 9000;     // home 90 deg

    TA1CCTL2 = 0x00E0;   // output mode 7  Servo 2
    TA1CCR2  = 9000;

    TA1CCTL3 = 0x00E0;   // output mode 7  Servo 3
    TA1CCR3  = 9000;

    TA1CCTL4 = 0x00E0;   // output mode 7  Servo 4
    TA1CCR4  = 9000;

    TA1CTL  |= 0x0010;   // start in Up mode
}

// ------------TimerA3_Init------------
// Servo 5, Servo 6, Hand, Rotate  CCR1-CCR4
// Input: none
// Output: none
void TimerA3_Init(void)
{
    TA3CTL   = 0x0280;   // SMCLK, /8 = 6MHz, stop mode, clear TAR
    TA3R     = 0;        // clear timer count
    TA3EX0   = 0x0000;   // additional /1

    TA3CCR0  = 119999;   // 20ms period at 6MHz

    TA3CCTL1 = 0x00E0;   // output mode 7  Servo 5 (P10.5)
    TA3CCR1  = 9000;     // home

    TA3CCTL2 = 0x00E0;   // output mode 7  Rotate  (P8.2)
    TA3CCR2  = 9000;     // home

    TA3CCTL3 = 0x00E0;   // output mode 7  Servo 6 (P9.2)
    TA3CCR3  = 9000;     // home

    TA3CCTL4 = 0x00E0;   // output mode 7  Hand    (P9.3)
    TA3CCR4  = 6000;     // start OPEN (MIN)

    TA3CTL  |= 0x0010;   // start in Up mode
}
