// Init_Ports.c
// Runs on MSP432
// Robotic Arm - Port Initializations
//
// PIN ASSIGNMENT:
//   Servo 1  P7.7  TA1CCR1
//   Servo 2  P7.6  TA1CCR2
//   Servo 3  P7.5  TA1CCR3
//   Servo 4  P7.4  TA1CCR4
//   Servo 5  P10.5 TA3CCR1
//   Servo 6  P9.2  TA3CCR3
//   Hand     P9.3  TA3CCR4
//   Rotate   P8.2  TA3CCR2
//   Buzzer   P6.3  GPIO output
//   LCD SDA  P10.2 eUSCI_B3
//   LCD SCL  P10.3 eUSCI_B3

#include "msp.h"

// ------------Port6_Init------------
// P6.3 = Buzzer (GPIO output)
// Input: none
// Output: none
void Port6_Init(void)
{
    P6DIR  |=  0x08;    // 00001000  bit 3 = output
    P6SEL0 &= ~0x08;    // GPIO mode - must clear both SEL bits
    P6SEL1 &= ~0x08;
    P6OUT  &= ~0x08;    // buzzer OFF
}

// ------------Port7_Init------------
// P7.4 = TA1.4  Servo 4
// P7.5 = TA1.3  Servo 3
// P7.6 = TA1.2  Servo 2
// P7.7 = TA1.1  Servo 1
// Input: none
// Output: none
void Port7_Init(void)
{
    P7DIR  |=  0xF0;    // 11110000  bits 4-7 = outputs
    P7SEL0 |=  0xF0;    // TimerA1 alternate function
    P7SEL1 &= ~0xF0;
}

// ------------Port8_Init------------
// P8.2 = TA3.2  Rotate servo
// Input: none
// Output: none
void Port8_Init(void)
{
    P8DIR  |=  0x04;    // 00000100  bit 2 = output
    P8SEL0 |=  0x04;    // TimerA3 alternate function
    P8SEL1 &= ~0x04;
}

// ------------Port9_Init------------
// P9.2 = TA3.3  Servo 6
// P9.3 = TA3.4  Hand servo
// Input: none
// Output: none
void Port9_Init(void)
{
    P9DIR  |=  0x0C;    // 00001100  bits 2,3 = outputs
    P9SEL0 |=  0x0C;    // TimerA3 alternate function
    P9SEL1 &= ~0x0C;
}

// ------------Port10_Init------------
// P10.2 = UCB3SDA  I2C LCD data
// P10.3 = UCB3SCL  I2C LCD clock
// P10.5 = TA3.1    Servo 5
// Input: none
// Output: none
void Port10_Init(void)
{
    // P10.5 = Servo 5 (TA3CCR1)
    P10DIR |= 0x20;     // P10.5 output
    P10SEL0 |= 0x20;    // Timer function
    P10SEL1 &= ~0x20;

    // P10.2 = SDA, P10.3 = SCL for I2C (UCB3)
    P10SEL0 |= 0x0C;    // bits 2 and 3
    P10SEL1 &= ~0x0C;   // ensure primary module function
}
