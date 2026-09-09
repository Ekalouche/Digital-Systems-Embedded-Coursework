#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include "..\inc\Clock.h"
#include "..\inc\CortexM.h"
#include "..\inc\Init_Ports.h"
#include "..\inc\Init_Timers.h"
#include "..\inc\motor.h"


/**
 Elie Kalouche
 Generates PWM clock signal when button is pressed 40Hz 70% duty cycle
*/


void main(void)
{
    Clock_Init48MHz();  // makes bus clock 48 MHz
          Port1_Init(); // calles port1
          Port7_Init(); //called port 7
          TimerA1_Init(); //calls Timer1

    while(1)
    {
        //Test code for ossiliscope
        //TA1CTL = 0x0210;


      if((P1IN & 0b00000010) == 0) //checks in button is pressed
        {
          TA1CTL = 0x0210; //sets to upmode
        }
      else
      {
          TA1CTL = 0x0200; //sets to Stopmode
      }

    }
}
