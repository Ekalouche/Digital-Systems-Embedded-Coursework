// servo_test.c
// Runs on MSP432
// Cycles through all 8 servos one at a time
// Each servo sweeps MIN -> MID -> MAX then next servo starts

#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include "../inc/Clock.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

// Servo values found from physical testing
#define SERVO_MIN   700     // 0 degrees
#define SERVO_MID   3500    // 90 degrees
#define SERVO_MAX   7000    // 180 degrees

// Servo number -> timer channel map:
//   0 = Servo 1  P7.7  TA1CCR1
//   1 = Servo 2  P7.6  TA1CCR2
//   2 = Servo 3  P7.5  TA1CCR3
//   3 = Servo 4  P7.4  TA1CCR4
//   4 = Servo 5  P10.5 TA3CCR1
//   5 = Servo 6  P9.2  TA3CCR3
//   6 = Hand     P9.3  TA3CCR4
//   7 = Rotate   P8.2  TA3CCR2

void ServoSet(uint8_t servoNum, uint16_t val)
{
    switch(servoNum){
        case 0: TA1CCR1 = val; break;
        case 1: TA1CCR2 = val; break;
        case 2: TA1CCR3 = val; break;
        case 3: TA1CCR4 = val; break;
        case 4: TA3CCR1 = val; break;
        case 5: TA3CCR3 = val; break;
        case 6: TA3CCR4 = val; break;
        case 7: TA3CCR2 = val; break;
        default: break;
    }
}

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    Clock_Init48MHz();

    Port6_Init();
    Port7_Init();
    Port8_Init();
    Port9_Init();
    Port10_Init();

    TimerA1_Init();
    TimerA3_Init();

    uint8_t s;

    while(1)
    {
        for(s = 0; s < 4; s++)
        {
            ServoSet(s, SERVO_MIN);
            Clock_Delay1ms(1000);
            ServoSet(s, SERVO_MID);
            Clock_Delay1ms(1000);
            ServoSet(s, SERVO_MAX);
            Clock_Delay1ms(1000);
            ServoSet(s, SERVO_MID);   // return to center before next servo
            Clock_Delay1ms(500);
        }
    }
}
