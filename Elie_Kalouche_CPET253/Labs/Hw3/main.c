#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"

void Servo(uint16_t angle_count);

void ServoInit(void)  //This function initializes the servo to be centered (0 degrees)
{
    Servo(4500);                 // center servo
    Clock_Delay1ms(1000);        // allow time to move
    TA2CTL &= ~0x0030;           // stop timer (clear MC bits)
    return;
}

void Servo(uint16_t angle_count) // this function moves the servo.
{
    TA2CCR0 = 59999;             // 20ms period
    TA2CCR3 = angle_count;       // high time
    TA2CTL = 0x0210;             // SMCLK + up mode + clear TAR
    return;
}

void main(void)
{
    // Sets Port (P6.6 = TA2.3)
    P6DIR  |= BIT6;
    P6SEL0 |= BIT6;
    P6SEL1 &= ~BIT6;

    //Sets up TimerA2
    TA2CTL   = 0x0200;           // SMCLK, timer stopped for now
    TA2R     = 0;
    TA2CCTL3 = 0x00E0;           // reset/set mode
    TA2CCR0  = 59999;            // correct: period register
    TA2CCR3  = 4500;             // start centered

    //center the servo using the ServoInit() function
    ServoInit();

    enum motor_states {Reset, Sweep_Left, Sweep_Right} state, prevState;

    state = Reset;
    prevState = !Reset;
    uint16_t stateTimer = 0;
    bool isNewState;

    while(1) {

        isNewState = (state != prevState);
        prevState = state;

        switch (state)
        {
        case Reset:
            if(isNewState)
            {
                ServoInit();
                stateTimer = 0;
            }
            stateTimer++;
            if(stateTimer >= 50)
            {
                state = Sweep_Left;
            }
            break;

        case Sweep_Left:
            if(isNewState)
            {
                stateTimer = 0;
                Servo(7500);
            }
            stateTimer++;
            if(stateTimer >= 50)
            {
                state = Sweep_Right;
            }
            break;

        case Sweep_Right:
            if(isNewState)
            {
                stateTimer = 0;
                Servo(1500);
            }
            stateTimer++;
            if(stateTimer >= 150)
            {
                state = Reset;
            }
            break;
        }

        Clock_Delay1ms(20);
    }
}
