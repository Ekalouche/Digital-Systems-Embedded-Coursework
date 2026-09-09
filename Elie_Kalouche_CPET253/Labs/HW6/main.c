// Joshua Bernberg

#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"

#define LA 54545
#define LAS 51484
#define LB 48594
#define LC 45867
#define LCS 43293
#define LD 40863
#define LDS 38569
#define LE 36405
#define LF 34361
#define LFS 32433
#define LG 30613
#define LGS 28894
#define MA 27273
#define MAS 25742
#define MB 24297
#define MC 22934
#define MCS 21646
#define MD 20431
#define MDS 19285
#define ME 18202
#define MF 17181
#define MFS 16216
#define MG 15306
#define MGS 14447
#define HA 13636
#define QUARTER 400
#define HALF 800


void TimerA0_Init (void)
{
    TA0CTL &= ~0x0030; //stop timer
    TA0CTL |= 0x0200; TA0CTL &= ~0x0100; //smclk select
    TA0CTL &= ~0x00C0; //select divide by 1
    TA0CCTL1 = 0x00E0; //outmod enable
    TA0CCR0 = 59999; //counts
    TA0CCR1 = 29999; //duty cycle 50%
}

void Port2_Init(void)
{
    P2DIR |= 0b00010000;
    P2SEL1 &= ~0b00010000;
    P2SEL0 |= 0b00010000;
}

void playnote(uint16_t note, uint16_t delay)
{
    TA0CCR0 = note;
    TA0CCR1 = note / 2;
    TA0CTL |= 0x0010; //start timer in up mode
    Clock_Delay1ms(delay);
    TA0CTL &= ~0x0030; //stop timer
    Clock_Delay1ms(50);
}



void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    Clock_Init48MHz();
    Port2_Init();
    TimerA0_Init();

	playnote(LC, QUARTER);
	playnote(LC, QUARTER);
	playnote(LG, QUARTER);
	playnote(LG, QUARTER);
	playnote(MA, QUARTER);
	playnote(MA, QUARTER);
	playnote(LG, HALF);
	playnote(LF, QUARTER);
	playnote(LF, QUARTER);
	playnote(LE, QUARTER);
	playnote(LE, QUARTER);
	playnote(LD, QUARTER);
	playnote(LD, QUARTER);
	playnote(LC, HALF);

	playnote(LG, QUARTER);
	playnote(LG, QUARTER);
	playnote(LF, QUARTER);
	playnote(LF, QUARTER);
	playnote(LE, QUARTER);
	playnote(LE, QUARTER);
	playnote(LD, HALF);
    playnote(LG, QUARTER);
    playnote(LG, QUARTER);
    playnote(LF, QUARTER);
    playnote(LF, QUARTER);
    playnote(LE, QUARTER);
    playnote(LE, QUARTER);
    playnote(LD, HALF);

    playnote(LC, QUARTER);
    playnote(LC, QUARTER);
    playnote(LG, QUARTER);
    playnote(LG, QUARTER);
    playnote(MA, QUARTER);
    playnote(MA, QUARTER);
    playnote(LG, HALF);
    playnote(LF, QUARTER);
    playnote(LF, QUARTER);
    playnote(LE, QUARTER);
    playnote(LE, QUARTER);
    playnote(LD, QUARTER);
    playnote(LD, QUARTER);
    playnote(LC, HALF);
}
