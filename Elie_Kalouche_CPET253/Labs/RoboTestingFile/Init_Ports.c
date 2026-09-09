// Init_Ports.c
// Runs on MSP432
// Robotic Arm State Machine - Port Initializations
// All pins chosen from ports free after boosterpack is installed:
// Available: P6.3, P7, P8, P9, P10
//
// PIN ASSIGNMENT SUMMARY:
// -----------------------------------------------
// SERVOS (PWM via TimerA alternate function):
//   Servo 1:  P7.7  (TA1.1)
//   Servo 2:  P7.6  (TA1.2)
//   Servo 3:  P7.5  (TA1.3)
//   Servo 4:  P7.4  (TA1.4)
//   Servo 5:  P10.5 (TA3.1)
//   Servo 6:  P9.2  (TA3.3)
//   Hand:     P9.3  (TA3.4)
//   Rotate:   P8.2  (TA3.2)
//
// BLUETOOTH (eUSCI_A0 UART @ 9600 baud) - boosterpack wired:
//   P1.2 = UCA0RXD
//   P1.3 = UCA0TXD
//
// I2C LCD 1602 (eUSCI_B3 I2C):
//   P10.2 = UCB3SDA
//   P10.3 = UCB3SCL
//
// BUZZER (passive buzzer, GPIO software toggle):
//   P6.3 = Buzzer output
// -----------------------------------------------

#include "msp.h"

// ------------Port6_Init------------
// P6.3 = Buzzer (GPIO output, software toggled)
// Input: none
// Output: none
void Port6_Init(void)
{
    P6DIR  |=  0x08;   // 00001000  bit 3 = output
    P6SEL0 &= ~0x08;   // GPIO mode
    P6SEL1 &= ~0x08;
    P6OUT  &= ~0x08;   // buzzer OFF at start
}

// ------------Port7_Init------------
// P7.4 = TA1.4 PWM  Servo 4
// P7.5 = TA1.3 PWM  Servo 3
// P7.6 = TA1.2 PWM  Servo 2
// P7.7 = TA1.1 PWM  Servo 1
// Input: none
// Output: none
void Port7_Init(void)
{
    P7DIR  |=  0xF0;   // 11110000  bits 4-7 = outputs
    P7SEL0 |=  0xF0;   // 11110000  TimerA1 alternate function
    P7SEL1 &= ~0xF0;   // 00001111
}

// ------------Port8_Init------------
// P8.2 = TA3.2 PWM  Servo Rotate
// Input: none
// Output: none
void Port8_Init(void)
{
    P8DIR  |=  0x04;   // 00000100  bit 2 = output
    P8SEL0 |=  0x04;   // TimerA3 alternate function
    P8SEL1 &= ~0x04;   // 11111011
}

// ------------Port9_Init------------
// P9.2 = TA3.3 PWM  Servo 6
// P9.3 = TA3.4 PWM  Servo Hand
// Input: none
// Output: none
void Port9_Init(void)
{
    P9DIR  |=  0x0C;   // 00001100  bits 2,3 = outputs
    P9SEL0 |=  0x0C;   // TimerA3 alternate function
    P9SEL1 &= ~0x0C;   // 11110011
}

// ------------Port10_Init------------
// P10.2 = UCB3SDA  I2C LCD data
// P10.3 = UCB3SCL  I2C LCD clock
// P10.5 = TA3.1 PWM  Servo 5
// Input: none
// Output: none
void Port10_Init(void)
{
    // I2C pins bits 2,3  SEL0=1 SEL1=0
    P10SEL0 |=  0x0C;   // 00001100
    P10SEL1 &= ~0x0C;   // 11110011

    // Servo 5 PWM bit 5  SEL0=1 SEL1=0
    P10DIR  |=  0x20;   // 00100000  bit 5 = output
    P10SEL0 |=  0x20;   // TimerA3 alternate function
    P10SEL1 &= ~0x20;   // 11011111
}
