/****************************************************************************************
         CPET253 Lab3 - PWM and Motor Drivers

 Jeanne Christman
 original version 6/1/2022

 This program uses a state machine to control the TI-RSLK robot to drive
 in a pattern of forward, right turn, backward, left turn, forward, right turn, ….. 

 To control the motors on the TI-RSLK robot, there are three outputs that need
 to be driven.
    :Pin    :Description            :Notes
    :=======:=======================:=========================
    : P5.5  : Right motor direction : 0=forwards, 1=backwards
    : P3.6  : Right motor sleep     : 0=sleep, 1=awake
    : P2.6  : Right motor PWM       : 0=stop, PWM signal = go
    : P5.4  : Left motor direction  : 0=forwards, 1=backwards
    : P3.7  : Left motor sleep      : 0=sleep, 1= awake
    : P2.7  : Left motor PWM        : 0=stop, PWM signal = go

 Functions in this code:
     -Clock_Init48MHz() - function provided by TI to set system clock
     -Clock_Delay1ms(time) - built in function that delays time ms
     -Port2_Init();
     -Port3_Init();
     -Port5_Init();
     -TimerA0_Init();
     -MotorForward(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorBackward(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorTurnRight(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 
     -MotorTurnLeft(volatile uint16_t rightDuty, volatile uint16_t leftDuty ); 

The state machine has 4 states; forward, right, left, backward
use FSM to make a pattern: Forward, right turn 90 degrees, backwards, left turn 90, forward...
*******************************************************************************************/

#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include "..\inc\Clock.h"
#include "..\inc\CortexM.h"
#include "..\inc\Init_Ports.h"
#include "..\inc\Init_Timers.h"
#include "..\inc\motor.h"


void main(void)
{


       WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
       Clock_Init48MHz();  // makes bus clock 48 MHz
       Port2_Init(); //Call the appropriate functions from Init_Ports.c
       Port3_Init(); //Call the appropriate functions from Init_Timers.c
       Port5_Init();
       TimerA0_Init();
       //These are the four states of the state machine
       enum motor_states {M_Forward,M_Right,M_Back,M_Left} state, prevState;

       state =  M_Forward;                    //start state
       prevState = !M_Forward;               //used to know when the state has changed
       uint16_t stateTimer = 0;       //used to stay in a state
       bool isNewState;           //true when the state has switched
       
       while(1)
       {
           isNewState = (state != prevState);
           prevState = state;  //save state for next time

          switch (state)
          {
          //each case below should have entry housekeeping, state business and exit housekeeping
          //remember to reset the stateTimer each time you enter a new state
          //you must assign a new state when stateTimer reaches the correct value
          case M_Forward:
              if(isNewState)
                 {
                    stateTimer = 0;
                    Motor_Forward(14999,14999);
                 }
                    stateTimer++;
             if(stateTimer >= 150)
                 {
                    state = M_Right;
                 }
                  break;
          case M_Right:
              if(isNewState)
               {
                   stateTimer = 0;
                   Motor_Right(14999,14999);
               }
                   stateTimer++;
              if(stateTimer >= 150)
                  {
                    state = M_Back;
                  }
                  break;
          case M_Back:
              if(isNewState)
              {
                stateTimer = 0;
                Motor_Backward(14999,14999);
              }
                stateTimer++;
          if(stateTimer >= 65)
              {
                state = M_Left;
              }

                  break;
          case M_Left:
          if(isNewState)
                        {
                          stateTimer = 0;
          Motor_Left(14999,14999);
                        }
                          stateTimer++;
                    if(stateTimer >= 150)
                        {
                          state = M_Forward;
                        }

                  break;

          } //switch
          Clock_Delay1ms(10);  //10ms delay so that each increment of statetimer is 10ms
       } //while(1)
   } //main()
