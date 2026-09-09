// Init_Timers.c
// Runs on MSP432
// Provide functions that initialize Timers 
// Prof. Christman
// 6/28/2023

/* These functions will be used for labs 3-8 in CPET253

There is an initialization function for each instantiation of TimerA;
TimerA0, TimerA1, TimerA2, TimerA3

*/

#include "msp.h"


// ------------TimerA0_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA0_Init(void){

// Choose a clock source (SMLCLK)
   TA0CTL = 0b0000001001000000;


// Load CCR0 with counts for 10 ms period
    TA0CCR0 = 59999;

// CCR3 PWM output
    TA0CCTL3 = 0b0000000011100000; // should be 0b0000000011100000 --> want reset/set but currently using set/reset --fixed

// CCR4 PWM output
    TA0CCTL4 = 0b0000000011100000; //

// Initialize duty cycles
    TA0CCR3 = 14999;
    TA0CCR4 = 14999;

  // In the TA0CTL register:
  //    Disable timer for initialization
  //    Choose a clock source
  //    Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA0EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA0CCTLn register
  //    set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA0CCR0 with clock
  //    counts for desired period
}

// ------------TimerA1_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA1_Init(void){
  // In the TA1CTL register:
  //    Disable timer for initialization
  //    Choose a clock source
  //    Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA1EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA1CCTLn register
  //    set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA1CCR0 with clock
  //    counts for desired period
}

// ------------TimerA2_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA2_Init(void){

    TA2CTL = 0; //stop timer


    TA2CTL = 0b0000001000011000; //smclk, continuous, divider of 8
    TA2EX0 = 0; //no extra divider
    TA2R = 0; //reset timer

  // In the TA2CTL register:
  //    Disable timer for initialization
  //    Choose a clock source
  //    Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA2EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA2CCTLn register
  //    set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA2CCR0 with clock
  //    counts for desired period
}

// ------------TimerA3_Init------------
// Before initializing the timer, do the calculations:
//      Elapsed Time = clock counts * (N/Clock Frequency)
//      clock counts cannot exceed 65,535
//      N is the clock scaler

// Input: none
// Output: none
void TimerA3_Init(void){

    TA3CTL = 0b0000001001000000; //SMCLK, up mode /4
    TA3CCR0 = 59999;
    TA3CCTL3 = 0b0000000011100000; //OUTMOD_7 (reset/set)
    TA3CCR3 = 4500; //~1.5ms pulse

  // In the TA3CTL register:
  //    Disable timer for initialization
  //    Choose a clock source
  //    Select a clock scaler if needed
  //    Enable overflow interrupt if needed
  // In the TA3EX0 register:
  //    Select a second clock scaler if needed
  // For EACH CCRn being used, in the TA3CCTLn register
  //    set the PWM outmode if needed
  //    Enable the CCRn match interrupt if needed
  // For PWM, Load TA3CCR0 with clock
  //    counts for desired period
}
