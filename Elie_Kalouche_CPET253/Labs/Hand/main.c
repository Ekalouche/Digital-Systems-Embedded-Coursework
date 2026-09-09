#include <stdint.h>
#include <stdbool.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

// ============================================================
// SERVO CONSTANTS (6 MHz timer clock)
// ============================================================
#define SERVO_PERIOD 119999

#define S_0      6000
#define S_90     9000
#define S_180    12000

// ============================================================
// UART GLOBALS
// ============================================================
#define UART_BUFSIZE 32
static char uartBuf[UART_BUFSIZE];
static uint8_t uartPos = 0;
volatile uint8_t lineReady = 0;

// ============================================================
// UART INITIALIZATION (WORKING VERSION)
// ============================================================
void UART0_Init_9600(void)
{
    P1SEL0 |= 0x0C;   // P1.2 RX, P1.3 TX
    P1SEL1 &= ~0x0C;

    UCA0CTLW0 = UCSWRST;
    UCA0CTLW0 |= UCSSEL__SMCLK;

    UCA0BRW = 312;        // 48MHz / 9600
    UCA0MCTLW = 0x0000;   // no modulation

    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
}

void UART0_SendChar(uint8_t c)
{
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = c;
}

void UART0_SendString(const char *str)
{
    while(*str) UART0_SendChar(*str++);
}

void EUSCIA0_IRQHandler(void)
{
    if(UCA0IFG & UCRXIFG){
        char c = UCA0RXBUF;

        UART0_SendChar(c); // echo

        if(c == '\n' || c == '\r'){
            uartBuf[uartPos] = '\0';
            if(uartPos > 0) lineReady = 1;
            uartPos = 0;
        } else {
            if(uartPos < UART_BUFSIZE - 1)
                uartBuf[uartPos++] = c;
        }

        UCA0IFG &= ~UCRXIFG;
    }
}

// ============================================================
// SERVO OUTPUT FUNCTIONS
// ============================================================
void Servo1(uint16_t x){ TA1CCR0 = SERVO_PERIOD; TA1CCR1 = x; TA1CTL |= 0x0010; }
void Servo2(uint16_t x){ TA1CCR0 = SERVO_PERIOD; TA1CCR2 = x; TA1CTL |= 0x0010; }
void Servo3(uint16_t x){ TA1CCR0 = SERVO_PERIOD; TA1CCR3 = x; TA1CTL |= 0x0010; }
void Servo4(uint16_t x){ TA1CCR0 = SERVO_PERIOD; TA1CCR4 = x; TA1CTL |= 0x0010; }
void Servo5(uint16_t x){ TA3CCR0 = SERVO_PERIOD; TA3CCR1 = x; TA3CTL |= 0x0010; }
void Servo6(uint16_t x){ TA3CCR0 = SERVO_PERIOD; TA3CCR3 = x; TA3CTL |= 0x0010; }

// ============================================================
// GESTURES (Converted from Arduino version)
// ============================================================
void OpenHand(void)
{
    Servo1(S_90);
    Servo2(S_0);
    Servo3(S_180);
    Servo4(S_0);
    Servo5(S_180);
    Servo6(S_90);
}

void CloseHand(void)
{
    Servo1(3000);
    Servo2(S_180);
    Servo3(S_0);
    Servo4(S_180);
    Servo5(S_0);
}

void Point(void)
{
    Servo1(3000);
    Servo2(S_180);
    Servo3(S_180);
    Servo4(S_180);
    Servo5(S_0);
}

void FlickOff(void)
{
    Servo1(3000);
    Servo2(S_180);
    Servo3(S_0);
    Servo4(S_0);
    Servo5(S_0);
}

void Peace(void)
{
    Servo1(3000);
    Servo2(S_180);
    Servo3(S_180);
    Servo4(S_0);
    Servo5(S_0);
}

void Three(void)
{
    Servo1(3000);
    Servo2(S_0);
    Servo3(S_180);
    Servo4(S_0);
    Servo5(S_0);
}

void Thumbs(void)
{
    Servo1(3000);
    Servo2(S_0);
    Servo3(S_0);
    Servo4(S_180);
    Servo5(S_0);
}

void OpenCloseHand(void)
{
    OpenHand();
    Clock_Delay1ms(1000);
    CloseHand();
    Clock_Delay1ms(1000);
    OpenHand();
}

void Count(void)
{
    CloseHand(); Clock_Delay1ms(1000);

    Servo3(S_180); Clock_Delay1ms(1000);
    Servo4(S_0);   Clock_Delay1ms(1000);
    Servo2(S_0);   Clock_Delay1ms(1000);

    Servo2(S_180);
    Servo3(S_0);
    Servo4(S_0);
    Clock_Delay1ms(3000);

    OpenHand();
}

// ============================================================
// COMMAND PARSER
// ============================================================
uint8_t StrEqualCI(const char *a, const char *b)
{
    while(*a && *b){
        char ca = (*a >= 'A' && *a <= 'Z') ? (*a + 32) : *a;
        char cb = (*b >= 'A' && *b <= 'Z') ? (*b + 32) : *b;
        if(ca != cb) return 0;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}

void MoveHand(const char *cmd)
{
    if(StrEqualCI(cmd,"Open"))       OpenHand();
    else if(StrEqualCI(cmd,"Close")) CloseHand();
    else if(StrEqualCI(cmd,"Point")) Point();
    else if(StrEqualCI(cmd,"Flick")) FlickOff();
    else if(StrEqualCI(cmd,"Peace")) Peace();
    else if(StrEqualCI(cmd,"Three")) Three();
    else if(StrEqualCI(cmd,"Thumb")) Thumbs();
    else if(StrEqualCI(cmd,"Count")) Count();
    else if(StrEqualCI(cmd,"OpenClose")) OpenCloseHand();
    else UART0_SendString("Unknown command\r\n");
}

// ============================================================
// MAIN
// ============================================================
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    Clock_Init48MHz();

    Port7_Init();
    Port9_Init();
    Port10_Init();

    TimerA1_Init();
    TimerA3_Init();

    UART0_Init_9600();
    __enable_irq();
    NVIC->ISER[0] |= 1 << (EUSCIA0_IRQn & 31);

    OpenHand();

    UART0_SendString("\r\nRobotic Hand Ready\r\n");
    UART0_SendString("Commands: Open Close Point Flick Peace Three Thumb Count OpenClose\r\n");

    while(1){
        if(lineReady){
            lineReady = 0;
            MoveHand(uartBuf);
            UART0_SendString("\r\nCommand received: ");
            UART0_SendString(uartBuf);
            UART0_SendString("\r\n");
        }
    }
}
