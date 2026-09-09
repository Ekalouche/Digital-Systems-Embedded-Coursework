#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/motor.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"
#include "../inc/BumpInt.h"

// Globals updated by ISR
extern volatile int bumpCount;
extern volatile int bumpFlag;

void main(void){

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;   // stop watchdog
    Clock_Init48MHz();

    //ports
    Port2_Init();
    Port3_Init();
    Port4_Init();
    Port5_Init();

    BumpInt_Init();
    TimerA0_Init();

    __enable_irq();

    //states
    enum robotState {FORWARD, BACKWARD, STOP_STATE, TURN_LEFT, TURN_RIGHT} state, prevState;

    state = FORWARD;          //start in FORWARD state
    prevState = !FORWARD;   //used to know when the state has changed
    uint16_t stateTimer = 0;           //used to stay in a state
    bool isNewState;              //true when the state has switched

    while(1){

        isNewState = (state != prevState);
        prevState = state;

        switch(state){

        case FORWARD:
            if(isNewState){
                stateTimer = 0;
                Motor_Forward(14999, 14999);
            }

            if(bumpFlag){
                bumpFlag = 0;
                state = BACKWARD;
            }
            break;

        case BACKWARD:
            if(isNewState){
                stateTimer = 0;
                Motor_Backward(14999, 14999);
            }

            if(stateTimer >= 25){
                state = STOP_STATE;
            }
            break;

        case STOP_STATE:
            if(isNewState){
                stateTimer = 0;
                Motor_Stop();
            }

            if(stateTimer >= 50){
                if(bumpCount > 0)
                    state = TURN_LEFT;
                else
                    state = TURN_RIGHT;
            }
            break;

        case TURN_LEFT:
            if(isNewState){
                stateTimer = 0;
                Motor_Left(14999, 14999);
            }

            if(stateTimer >= 50){
                bumpCount = 0;
                bumpFlag = 0;
                state = FORWARD;
            }
            break;

        case TURN_RIGHT:
            if(isNewState){
                stateTimer = 0;
                Motor_Right(14999, 14999);
            }

            if(stateTimer >= 50){
                bumpCount = 0;
                bumpFlag = 0;
                state = FORWARD;
            }
            break;

        default:
            state = FORWARD;
            break;
        }

        stateTimer++;
        Clock_Delay1ms(20);


    } //while
}
