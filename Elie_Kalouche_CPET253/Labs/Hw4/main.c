#include "msp.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"

/*
Reaction Timer
Button:  P5.6
LEDs:    P5.0 Red, P5.1 Yellow, P5.2 Green
*/

#define RED    BIT0
#define YELLOW BIT1
#define GREEN  BIT2
#define BTN    BIT6

volatile bool buttonPressed = false;

void PinInit(void) {
    // LEDs output
    P5DIR |= (RED | YELLOW | GREEN);
    P5OUT &= ~(RED | YELLOW | GREEN);

    // Button input with pull-up
    P5DIR  &= ~BTN;
    P5REN  |=  BTN;
    P5OUT  |=  BTN;          // pull-up resistor
    P5SEL0 &= ~BTN;          // GPIO
    P5SEL1 &= ~BTN;
    return;
}

void InterruptInit(void) {
    P5IE  |= BTN;            // enable interrupt on P5.6
    P5IES |= BTN;            // falling edge
    P5IFG &= ~BTN;           // clear flag

    // Port 5 interrupt is number 39, so bit 7 is set in ISER[1]
    // (interrupt 32 is bit 0)
    NVIC->ISER[1] |= 0x00000080;

    EnableInterrupts();      // global interrupt enable
    return;
}

void TimerA0SeedInit(void) {
    // free running timer used for random seed
    TA0CTL = TASSEL__SMCLK | MC__CONTINUOUS | TACLR;
    return;
}

void PORT5_IRQHandler(void) {
    uint16_t status = P5IV;  // find which pin caused interrupt

    // P5IV = 2*(n+1), for P5.6 -> 2*(6+1)=14 -> 0x0E
    if (status == 0x0E) {
        buttonPressed = true;
        P5IFG &= ~BTN;       // clear flag
        return;
    }
}

void AllLEDsOff(void) {
    P5OUT &= ~(RED | YELLOW | GREEN);
    return;
}

int main(void) {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;  // stop watchdog
    Clock_Init48MHz();                           // needed for Clock_Delay1ms
    PinInit();
    TimerA0SeedInit();
    InterruptInit();

    uint32_t randomDelayMs;
    uint32_t reactMs;
    uint32_t reactionWindowMs = 500;             // 0.5 second

    printf("reaction timer ready \n");
    printf("press button to start \n");

    while (1) {

        // wait for start press
        AllLEDsOff();
        buttonPressed = false;
        while (!buttonPressed) { }
        buttonPressed = false;

        printf("round started \n");

        // random delay BEFORE yellow turns on
        srand((unsigned)TA0R);                   // seed using changing timer value
        randomDelayMs = (rand() % 3001) + 1000;  // 1000 to 4000 ms
        printf("waiting for %d ms before yellow turns on \n", (int)randomDelayMs);

        Clock_Delay1ms(randomDelayMs);

        // yellow ON and start reaction timing
        P5OUT &= ~(RED | GREEN);
        P5OUT |= YELLOW;

        printf("yellow LED ON \n");
        printf("press the button now \n");

        reactMs = 0;
        buttonPressed = false;

        // 500ms window to press
        while ((reactMs < reactionWindowMs) && (!buttonPressed)) {
            Clock_Delay1ms(1);
            reactMs++;
        }

        // yellow OFF
        P5OUT &= ~YELLOW;
        printf("yellow LED OFF \n");

        // win/lose
        if (buttonPressed) {
            P5OUT |= GREEN;
            printf("you won \n");
            printf("reaction time = %d ms \n", (int)reactMs);
        } else {
            P5OUT |= RED;
            printf("you lost \n");
            printf("time limit was %d ms \n", (int)reactionWindowMs);
        }

        // delay after the result
        Clock_Delay1ms(800);
        printf("press button to play again \n");
    }
}
