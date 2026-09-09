// Init_Ports.c
// Runs on MSP432
// Provide functions that initialize ports 
// Prof. Christman
// 1/8/2023

/* These functions will be used in all of the labs for CPET253

There is an initialization function for each of the ports 1-10 and J.

The initializations will be different for each lab.
*/

#include "msp.h"


// ------------Port1_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port1_Init(void){

    P1DIR &= 0b11101101; // PIN1 and PIN4 set as inputs
    P1REN |= 0b00010010; // Enables PullUp on 1 and 4
    P1OUT |= 0b00010010; // sends output of pullups

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port2_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port2_Init(void){

// P2.0, P2.1, P2.2 outputs (LEDs)
    P2DIR |= 0b00000111; // port pins 0,1,2 outputs
    P2OUT &= 0b11111000; // starts with LED off

// P2.6 and P2.7 used for TimerA0 PWM
    P2DIR |= 0b11000000; // set pins 6 and 7 as outputs
    P2SEL0 |= 0b11000000; // SEL0 = 1 for both pins
    P2SEL1 &= 0b00111111; // SEL1 = 0 for both pins

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port3_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port3_Init(void){

// P3.6 and P3.7 are nSLEEP pins for right and left motors
    P3DIR |= 0b11000000; // set pins 6 and 7 as outputs


  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port4_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port4_Init(void){

    // Inputs on P4.7, P4.6, P4.5, P4.3, P4.2, P4.0
        P4DIR &= ~0b11101101;

        // Enable resistors
        P4REN |=  0b11101101;

        // Pull-up resistors
        P4OUT |=  0b11101101;

        // GPIO mode
        P4SEL0 &= ~0b11101101;
        P4SEL1 &= ~0b11101101;


  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port5_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port5_Init(void){

    P5DIR |= 0b00110000;     // set pins 4 and 5 as outputs
    P5DIR |= 0x08;//0000 1000. Set pin 3 as an output for IR sensors

// P5.4 = DIRL, P5.5 = DIRR

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port6_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port6_Init(void){

    // ultrasonic trigger
    P6DIR |= 0b00000100; //P6.2 output
    P6SEL0 &= 0b11111011;
    P6SEL1 &= 0b11111011;

    // ultrasonic echo
    P6DIR &= 0b11110111; //P6.3 input
    P6SEL0 &= 0b11110111;
    P6SEL1 &= 0b11110111;

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port7_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port7_Init(void){
    P7DIR &= ~0xFF;//Make all port 7 pins inputs

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port8_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port8_Init(void){
  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port9_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port9_Init(void){

    P9DIR |= 0b00000100;

  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------Port10_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void Port10_Init(void){
  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}

// ------------PortJ_Init------------
// First set the pin directions
// Enable resistors for inputs
// Set input resistors for pull-up or pull-down
// Enable alternate pin functions, if appliable
// Drive initial values on outputs
// Input: none
// Output: none
void PortJ_Init(void){
  // Use the port direction register to configure pins as inputs and output
  //    -A 1 sets a pin as an output. Use |= with a bit mask to set 1's.
  //    -A 0 sets a pin as an input. Use &= with a bit mask to set 0's.
  // Use the resistor enable register to enable resistors for inputs that need them
  // Use the port output register to configure the resistors as pull-ups or pull-downs
  // Use the PxSEL0 and PxSEL1 registers to enable alternate pin functions, if applicable
  // Use the port output register to put outputs to an initial state
}
