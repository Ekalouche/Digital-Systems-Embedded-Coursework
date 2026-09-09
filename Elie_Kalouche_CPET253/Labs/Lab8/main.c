// main.c
// Runs on MSP432
// Robotic Arm State Machine
// Controls 8 servos via Bluetooth, SSD1306 OLED status display, buzzer feedback
//
// BLUETOOTH COMMAND KEYS (send single char from any BT terminal app):
// -----------------------------------------------
//   '1' / 'q'  = Servo 1 forward / backward
//   '2' / 'w'  = Servo 2 forward / backward
//   '3' / 'e'  = Servo 3 forward / backward
//   '4' / 'r'  = Servo 4 forward / backward
//   '5' / 't'  = Servo 5 forward / backward
//   '6' / 'y'  = Servo 6 forward / backward
//   '7' / 'u'  = Servo 7 forward / backward
//   '8' / 'i'  = Servo 8 forward / backward
//   'h'         = Home all servos (90 deg)
//   'l'         = LOCATING  - arm searching for item
//   'g'         = GRABBED   - item picked up
//   'n'         = NOT FOUND - item cannot be located
// -----------------------------------------------
//
// STATE MACHINE STATES:
//   ARM_IDLE      - waiting for commands, all servos at home
//   ARM_MOVING    - a servo is being repositioned
//   ARM_LOCATING  - arm scanning for item
//   ARM_GRABBED   - item secured
//   ARM_NOT_FOUND - search failed
//
// OLED MESSAGES per state:
//   ARM_IDLE      : "Arm: IDLE"       / "Waiting..."
//   ARM_MOVING    : "Arm: MOVING"     / "Servo adjusting"
//   ARM_LOCATING  : "Arm: SEARCHING"  / "Item being"  "Located..."
//   ARM_GRABBED   : "Arm: SUCCESS"    / "Item picked up!"
//   ARM_NOT_FOUND : "Arm: FAILED"     / "Item can not"  "be located"
//
// BUZZER SONGS:
//   Startup     : double beep
//   Locating    : ascending C-E-G sweep
//   Grabbed     : happy C-E-G-C fanfare
//   Not Found   : sad G-C descending

#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/SSD1306.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

// ============================================================
// SERVO CCR POSITION CONSTANTS  (6MHz timer clock)
// ============================================================
#define SERVO_MIN   6000    // 1.0ms =   0 degrees
#define SERVO_MID   9000    // 1.5ms =  90 degrees  (home)
#define SERVO_MAX   12000   // 2.0ms = 180 degrees

#define NUM_POSITIONS   3

// ============================================================
// GLOBALS
// ============================================================
volatile uint8_t btRxChar   = 0;   // last byte received over Bluetooth
volatile uint8_t btDataReady = 0;  // flag: new byte waiting to be processed

// Each servo tracks which of the 3 positions it is currently in
// index 0 = MIN, 1 = MID, 2 = MAX
uint8_t servoIndex[8] = {1, 1, 1, 1, 1, 1, 1, 1};   // all start at MID

static const uint16_t servoPositions[NUM_POSITIONS] = {SERVO_MIN, SERVO_MID, SERVO_MAX};

// ============================================================
// UART (BLUETOOTH) - eUSCI_A0, 9600 baud, 8N1, SMCLK 48MHz
// ============================================================
void UART_Init(void)
{
    UCA0CTLW0  = UCSWRST;           // hold in reset while configuring
    UCA0CTLW0 |= UCSSEL__SMCLK;     // clock source = SMCLK (48MHz)
    UCA0BRW    = 312;               // 48MHz / 9600 baud = 5000; with UCOS16
    UCA0MCTLW  = 0x0081;            // UCBRSx=0x00, UCBRFx=8, UCOS16=1
    UCA0CTLW0 &= ~UCSWRST;          // release from reset
    UCA0IE    |= UCRXIE;            // enable RX interrupt
}

// eUSCI_A0 ISR - fires on every byte received from Bluetooth module
void EUSCIA0_IRQHandler(void)
{
    if(UCA0IFG & UCRXIFG){
        btRxChar    = UCA0RXBUF;    // reading RXBUF clears the flag
        btDataReady = 1;
    }
}

// ============================================================
// SERVO HELPERS
// ============================================================

// Write a new CCR value to the correct timer register for servo 0-7
void Servo_SetCCR(uint8_t servoNum, uint16_t ccrValue)
{
    switch(servoNum){
        case 0: TA0CCR1 = ccrValue; break;   // Servo 1  P2.4
        case 1: TA0CCR2 = ccrValue; break;   // Servo 2  P2.5
        case 2: TA1CCR1 = ccrValue; break;   // Servo 3  P2.6
        case 3: TA1CCR2 = ccrValue; break;   // Servo 4  P2.7
        case 4: TA2CCR1 = ccrValue; break;   // Servo 5  P5.6
        case 5: TA2CCR2 = ccrValue; break;   // Servo 6  P5.7
        case 6: TA3CCR1 = ccrValue; break;   // Servo 7  P6.6
        case 7: TA3CCR2 = ccrValue; break;   // Servo 8  P6.7
        default: break;
    }
}

// Advance servo one position toward MAX (clamps at MAX)
// LINKAGE RULES:
//   Servo 7 (index 6) moves -> Servo 6 (index 5) mirrors same position
//   Servo 5 (index 4) moves -> Servos 6 & 7 (index 5,6) move opposite direction
void Servo_Forward(uint8_t servoNum)
{
    if(servoIndex[servoNum] < (NUM_POSITIONS - 1)){
        servoIndex[servoNum]++;
    }
    Servo_SetCCR(servoNum, servoPositions[servoIndex[servoNum]]);

    // Servo 7 forward -> Servo 6 mirrors (same position = forward)
    if(servoNum == 6){
        if(servoIndex[5] < (NUM_POSITIONS - 1)){
            servoIndex[5]++;
        }
        Servo_SetCCR(5, servoPositions[servoIndex[5]]);
    }

    // Servo 5 forward -> Servos 6 & 7 go backward (opposite)
    if(servoNum == 4){
        if(servoIndex[5] > 0){ servoIndex[5]--; }
        Servo_SetCCR(5, servoPositions[servoIndex[5]]);
        if(servoIndex[6] > 0){ servoIndex[6]--; }
        Servo_SetCCR(6, servoPositions[servoIndex[6]]);
    }
}

// Move servo one position toward MIN (clamps at MIN)
// LINKAGE RULES:
//   Servo 7 (index 6) moves -> Servo 6 (index 5) mirrors same position
//   Servo 5 (index 4) moves -> Servos 6 & 7 (index 5,6) move opposite direction
void Servo_Backward(uint8_t servoNum)
{
    if(servoIndex[servoNum] > 0){
        servoIndex[servoNum]--;
    }
    Servo_SetCCR(servoNum, servoPositions[servoIndex[servoNum]]);

    // Servo 7 backward -> Servo 6 mirrors (same position = backward)
    if(servoNum == 6){
        if(servoIndex[5] > 0){
            servoIndex[5]--;
        }
        Servo_SetCCR(5, servoPositions[servoIndex[5]]);
    }

    // Servo 5 backward -> Servos 6 & 7 go forward (opposite)
    if(servoNum == 4){
        if(servoIndex[5] < (NUM_POSITIONS - 1)){ servoIndex[5]++; }
        Servo_SetCCR(5, servoPositions[servoIndex[5]]);
        if(servoIndex[6] < (NUM_POSITIONS - 1)){ servoIndex[6]++; }
        Servo_SetCCR(6, servoPositions[servoIndex[6]]);
    }
}

// Send all 8 servos to home position (MID = 90 deg)
void Servo_HomeAll(void)
{
    uint8_t i;
    for(i = 0; i < 8; i++){
        servoIndex[i] = 1;
        Servo_SetCCR(i, SERVO_MID);
    }
}

// ============================================================
// BUZZER HELPERS  (P3.0, software-toggled, Clock_Delay1us)
// ============================================================

// Play a single tone: frequency in Hz, duration in ms
void Buzzer_Tone(uint32_t freqHz, uint32_t durationMs)
{
    uint32_t halfPeriod_us = 500000 / freqHz;
    uint32_t cycles        = (durationMs * 500) / halfPeriod_us;
    uint32_t i;
    for(i = 0; i < cycles; i++){
        P3OUT |=  0x01;
        Clock_Delay1ms(1);   // close enough for short half-periods
        P3OUT &= ~0x01;
        Clock_Delay1ms(1);
    }
}

// Short silence between notes
void Buzzer_Rest(uint32_t ms)
{
    P3OUT &= ~0x01;
    Clock_Delay1ms(ms);
}

void Buzzer_PlayStartup(void)
{
    Buzzer_Tone(1000, 80);   // 1kHz beep
    Buzzer_Rest(60);
    Buzzer_Tone(1000, 80);   // second beep
    Buzzer_Rest(60);
}

void Buzzer_PlayLocating(void)
{
    Buzzer_Tone(523, 120);   // C5
    Buzzer_Rest(40);
    Buzzer_Tone(659, 120);   // E5
    Buzzer_Rest(40);
    Buzzer_Tone(784, 120);   // G5
    Buzzer_Rest(40);
}

void Buzzer_PlayGrabbed(void)
{
    Buzzer_Tone(523, 100);   // C5
    Buzzer_Rest(30);
    Buzzer_Tone(659, 100);   // E5
    Buzzer_Rest(30);
    Buzzer_Tone(784, 100);   // G5
    Buzzer_Rest(30);
    Buzzer_Tone(1047, 220);  // C6 (hold)
    Buzzer_Rest(30);
}

void Buzzer_PlayNotFound(void)
{
    Buzzer_Tone(784, 180);   // G5
    Buzzer_Rest(50);
    Buzzer_Tone(523, 360);   // C5 (long low note)
    Buzzer_Rest(50);
}

// ============================================================
// MAIN
// ============================================================
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;   // stop watchdog timer
    Clock_Init48MHz();                               // bus clock = 48MHz

    // initialize all ports
    Port1_Init();    // Bluetooth UART RX/TX
    Port2_Init();    // Servos 1-4 PWM
    Port3_Init();    // Buzzer
    Port5_Init();    // Servos 5-6 PWM
    Port6_Init();    // Servos 7-8 PWM
    Port9_Init();    // SSD1306 OLED SPI

    // initialize timers
    TimerA0_Init();  // Servos 1 & 2
    TimerA1_Init();  // Servos 3 & 4
    TimerA2_Init();  // Servos 5 & 6
    TimerA3_Init();  // Servos 7 & 8

    // initialize UART for Bluetooth
    UART_Init();

    // initialize OLED
    SSD1306_Init(SSD1306_SWITCHCAPVCC);
    SSD1306_Clear();

    // enable global interrupts and UART RX IRQ
    __enable_irq();
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);

    // home all servos
    Servo_HomeAll();

    // state machine setup
    // --- states ---
    enum armState {ARM_IDLE, ARM_MOVING, ARM_LOCATING, ARM_GRABBED, ARM_NOT_FOUND} state, prevState;
    state     = ARM_IDLE;
    prevState = -1;          // force isNewState true on first loop

    bool isNewState;

    while(1)
    {
        isNewState = (state != prevState);
        prevState  = state;

        // -------------------------------------------------------
        // STATE OUTPUTS  (only run once when entering a new state)
        // -------------------------------------------------------
        switch(state)
        {
            case ARM_IDLE:
                if(isNewState){
                    SSD1306_Clear();
                    SSD1306_SetCursor(0, 0);
                    SSD1306_OutString("Arm: IDLE");
                    SSD1306_SetCursor(0, 1);
                    SSD1306_OutString("Waiting...");
                }
                break;

            case ARM_MOVING:
                if(isNewState){
                    SSD1306_Clear();
                    SSD1306_SetCursor(0, 0);
                    SSD1306_OutString("Arm: MOVING");
                    SSD1306_SetCursor(0, 1);
                    SSD1306_OutString("Servo adjusting");
                }
                break;

            case ARM_LOCATING:
                if(isNewState){
                    SSD1306_Clear();
                    SSD1306_SetCursor(0, 0);
                    SSD1306_OutString("Arm: SEARCHING");
                    SSD1306_SetCursor(0, 1);
                    SSD1306_OutString("Item being");
                    SSD1306_SetCursor(0, 2);
                    SSD1306_OutString("Located...");
                    Buzzer_PlayLocating();
                }
                break;

            case ARM_GRABBED:
                if(isNewState){
                    SSD1306_Clear();
                    SSD1306_SetCursor(0, 0);
                    SSD1306_OutString("Arm: SUCCESS");
                    SSD1306_SetCursor(0, 1);
                    SSD1306_OutString("Item picked up!");
                    Buzzer_PlayGrabbed();
                }
                break;

            case ARM_NOT_FOUND:
                if(isNewState){
                    SSD1306_Clear();
                    SSD1306_SetCursor(0, 0);
                    SSD1306_OutString("Arm: FAILED");
                    SSD1306_SetCursor(0, 1);
                    SSD1306_OutString("Item can not");
                    SSD1306_SetCursor(0, 2);
                    SSD1306_OutString("be located");
                    Buzzer_PlayNotFound();
                }
                break;

            default:
                state = ARM_IDLE;
                break;
        } // switch state outputs

        // -------------------------------------------------------
        // STATE TRANSITIONS  (check Bluetooth input)
        // -------------------------------------------------------
        if(btDataReady){
            btDataReady = 0;

            switch(btRxChar)
            {
                // Servo 1
                case '1': Servo_Forward(0);   state = ARM_MOVING;    break;
                case 'q': Servo_Backward(0);  state = ARM_MOVING;    break;
                // Servo 2
                case '2': Servo_Forward(1);   state = ARM_MOVING;    break;
                case 'w': Servo_Backward(1);  state = ARM_MOVING;    break;
                // Servo 3
                case '3': Servo_Forward(2);   state = ARM_MOVING;    break;
                case 'e': Servo_Backward(2);  state = ARM_MOVING;    break;
                // Servo 4
                case '4': Servo_Forward(3);   state = ARM_MOVING;    break;
                case 'r': Servo_Backward(3);  state = ARM_MOVING;    break;
                // Servo 5
                case '5': Servo_Forward(4);   state = ARM_MOVING;    break;
                case 't': Servo_Backward(4);  state = ARM_MOVING;    break;
                // Servo 6
                case '6': Servo_Forward(5);   state = ARM_MOVING;    break;
                case 'y': Servo_Backward(5);  state = ARM_MOVING;    break;
                // Servo 7
                case '7': Servo_Forward(6);   state = ARM_MOVING;    break;
                case 'u': Servo_Backward(6);  state = ARM_MOVING;    break;
                // Servo 8
                case '8': Servo_Forward(7);   state = ARM_MOVING;    break;
                case 'i': Servo_Backward(7);  state = ARM_MOVING;    break;
                // Special commands
                case 'h': Servo_HomeAll();    state = ARM_IDLE;       break;
                case 'l':                     state = ARM_LOCATING;   break;
                case 'g':                     state = ARM_GRABBED;    break;
                case 'n':                     state = ARM_NOT_FOUND;  break;
                default: break;
            } // switch btRxChar
        } // if btDataReady

        // After a MOVING state, return to IDLE after a short delay
        // so the display does not stay stuck on "MOVING"
        if(state == ARM_MOVING && !btDataReady){
            Clock_Delay1ms(400);
            state = ARM_IDLE;
        }

        Clock_Delay1ms(10);
    } // while
}
