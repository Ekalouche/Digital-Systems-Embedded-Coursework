// main.c
// Runs on MSP432
// Robotic Arm
//
// Bluetooth removed - 'command' variable mimics what BT would send
// Change 'command' in main() and reflash to test
//
// command values:
//   1  = Servo 1 forward
//   2  = Servo 1 backward
//   3  = Servo 2 forward
//   4  = Servo 2 backward
//   5  = Servo 3 forward
//   6  = Servo 3 backward
//   7  = Servo 4 forward  (servo 5 & 6 go backward)
//   8  = Servo 4 backward (servo 5 & 6 go forward)
//   9  = Servo 5 & 6 forward
//   10 = Servo 5 & 6 backward
//   11 = Hand open
//   12 = Hand close
//   13 = Rotate forward
//   14 = Rotate backward
//   15 = Home all servos
//   16 = LOCATING state
//   17 = GRABBED state
//   18 = NOT FOUND state
//
// SERVO MAP:
//   0 = Servo 1  P7.7  TA1CCR1
//   1 = Servo 2  P7.6  TA1CCR2
//   2 = Servo 3  P7.5  TA1CCR3
//   3 = Servo 4  P7.4  TA1CCR4
//   4 = Servo 5  P10.5 TA3CCR1
//   5 = Servo 6  P9.2  TA3CCR3
//   6 = Hand     P9.3  TA3CCR4
//   7 = Rotate   P8.2  TA3CCR2

#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/UART0.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

// ============================================================
// SERVO VALUES
// ============================================================
#define SERVO_MIN   700     // full backward
#define SERVO_MID   3500    // home
#define SERVO_MAX   7000    // full forward
#define STEP        500     // counts per move
#define HAND_OPEN   3500
#define HAND_CLOSE  700

// ============================================================
// SERVO SET - same as test file
// ============================================================
void ServoSet(uint8_t servoNum, uint16_t val)
{
    if(val < SERVO_MIN) { val = SERVO_MIN; }
    if(val > SERVO_MAX) { val = SERVO_MAX; }

    switch(servoNum)
    {
        case 0: TA1CCR1 = val; break;   // Servo 1  P7.7
        case 1: TA1CCR2 = val; break;   // Servo 2  P7.6
        case 2: TA1CCR3 = val; break;   // Servo 3  P7.5
        case 3: TA1CCR4 = val; break;   // Servo 4  P7.4
        case 4: TA3CCR1 = val; break;   // Servo 5  P10.5
        case 5: TA3CCR3 = val; break;   // Servo 6  P9.2
        case 6: TA3CCR4 = val; break;   // Hand     P9.3
        case 7: TA3CCR2 = val; break;   // Rotate   P8.2
        default: break;
    }
}

// ============================================================
// SERVO POSITION TRACKING
// reads current CCR values from timer registers on startup
// so position is remembered across resets
// ============================================================
uint16_t pos[8];

void Pos_Init(void)
{
    pos[0] = TA1CCR1;
    pos[1] = TA1CCR2;
    pos[2] = TA1CCR3;
    pos[3] = TA1CCR4;
    pos[4] = TA3CCR1;
    pos[5] = TA3CCR3;
    pos[6] = TA3CCR4;
    pos[7] = TA3CCR2;

    // if any CCR is 0 (timer just initialized) default to MID
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(pos[i] == 0)
        {
            pos[i] = SERVO_MID;
        }
    }
}

// ============================================================
// I2C LCD 1602  (eUSCI_B3, P10.2=SDA P10.3=SCL, address 0x27)
// PCF8574 backpack bit map:
//   bit7=D7 bit6=D6 bit5=D5 bit4=D4 bit3=BL bit2=EN bit1=RW bit0=RS
// ============================================================
#define LCD_ADDR  0x27
#define LCD_BL    0x08
#define LCD_EN    0x04
#define LCD_RS    0x01

void I2C_Init(void)
{
    UCB3CTLW0  = UCSWRST;
    UCB3CTLW0 |= UCMODE_3 | UCMST | UCSYNC | UCSSEL__SMCLK;
    UCB3BRW    = 480;
    UCB3I2CSA  = LCD_ADDR;
    UCB3CTLW0 &= ~UCSWRST;
}

void I2C_SendByte(uint8_t data)
{
    while(UCB3STATW & UCBBUSY);
    UCB3CTLW0 |= UCTR | UCTXSTT;
    while(!(UCB3IFG & UCTXIFG0));
    UCB3TXBUF  = data;
    while(!(UCB3IFG & UCTXIFG0));
    UCB3CTLW0 |= UCTXSTP;
    while(UCB3CTLW0 & UCTXSTP);
}

void LCD_PulseEnable(uint8_t data)
{
    I2C_SendByte(data |  LCD_EN | LCD_BL);
    Clock_Delay1ms(1);
    I2C_SendByte((data & ~LCD_EN) | LCD_BL);
    Clock_Delay1ms(1);
}

void LCD_SendNibble(uint8_t nibble, uint8_t rs)
{
    LCD_PulseEnable((nibble & 0xF0) | rs);
}

void LCD_SendByte(uint8_t byte, uint8_t rs)
{
    LCD_SendNibble( byte & 0xF0,       rs);
    LCD_SendNibble((byte << 4) & 0xF0, rs);
}

void LCD_Command(uint8_t cmd)
{
    LCD_SendByte(cmd, 0x00);
    Clock_Delay1ms(2);
}

void LCD_Data(uint8_t data)
{
    LCD_SendByte(data, LCD_RS);
    Clock_Delay1ms(1);
}

void LCD_Init(void)
{
    Clock_Delay1ms(50);
    LCD_SendNibble(0x30, 0);  Clock_Delay1ms(5);
    LCD_SendNibble(0x30, 0);  Clock_Delay1ms(1);
    LCD_SendNibble(0x30, 0);  Clock_Delay1ms(1);
    LCD_SendNibble(0x20, 0);  Clock_Delay1ms(1);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
    Clock_Delay1ms(2);
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
    Clock_Delay1ms(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    LCD_Command((row == 0) ? (0x80 + col) : (0xC0 + col));
}

void LCD_Print(const char *str)
{
    while(*str)
    {
        LCD_Data((uint8_t)*str++);
    }
}

void LCD_Update(const char *row0, const char *row1)
{
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_Print(row0);
    LCD_SetCursor(1, 0);
    LCD_Print(row1);
}

// ============================================================
// BUZZER (P6.3)
// ============================================================
#define LD   294    // D4
#define LE   330    // E4
#define LG   392    // G4
#define MA   440    // A4
#define MC   523    // C5
#define ME   659    // E5
#define MG   784    // G5
#define HA   880    // A5
#define HALF 600
#define REST  50

void playnote(uint16_t freqHz, uint16_t dur)
{
    // freqHz = frequency in Hz, dur = duration in ms
    uint32_t halfPeriod = 500000 / freqHz;   // half period in microseconds
    uint32_t cycles     = ((uint32_t)dur * freqHz) / 1000;
    uint32_t i;
    for(i = 0; i < cycles; i++)
    {
        P6OUT |=  0x08;
        Clock_Delay1us(halfPeriod);
        P6OUT &= ~0x08;
        Clock_Delay1us(halfPeriod);
    }
    P6OUT &= ~0x08;
    Clock_Delay1ms(REST);
}

void Buzzer_PlayStartup(void)
{
    playnote(LD, 80);  playnote(LE, 80);  playnote(LG, 80);  playnote(MA, 80);
    playnote(MC, 80);  playnote(ME, 80);  playnote(MG, 80);  playnote(HA, HALF);
    Clock_Delay1ms(80);
    playnote(MG, 60);  playnote(ME, 60);  playnote(MC, 80);
}

void Buzzer_PlayLocating(void)
{
    playnote(MC, 80);  Clock_Delay1ms(40);
    playnote(MC, 80);  Clock_Delay1ms(40);
    playnote(MC, 80);  Clock_Delay1ms(80);
    playnote(ME, 100); Clock_Delay1ms(40);
    playnote(MG, 100); Clock_Delay1ms(40);
    playnote(MA, 150);
}

void Buzzer_PlayGrabbed(void)
{
    playnote(MC, 80);  Clock_Delay1ms(30);
    playnote(MC, 80);  Clock_Delay1ms(30);
    playnote(MC, 80);  Clock_Delay1ms(30);
    playnote(ME, 120);
    playnote(MG, 120);
    playnote(HA, HALF);
}

void Buzzer_PlayNotFound(void)
{
    playnote(HA, 100);
    playnote(MG, 100);
    playnote(ME, 100);
    playnote(MC, 150);
    Clock_Delay1ms(80);
    playnote(LD, 80);  Clock_Delay1ms(40);
    playnote(LD, 80);  Clock_Delay1ms(40);
    playnote(MC, HALF);
}

// ============================================================
// HOME ALL SERVOS  (command 15)
// ============================================================
void HomeAll(void)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        pos[i] = SERVO_MID;
        ServoSet(i, SERVO_MID);
    }
    pos[6] = HAND_OPEN;
    ServoSet(6, HAND_OPEN);
}

// ============================================================
// MOVE ROBOT
// ============================================================
void MoveRobot(uint8_t command)
{
    switch(command)
    {
        case 1:   // Servo 1 forward
            if(pos[0] + STEP <= SERVO_MAX)
            {
                pos[0] += STEP;
            }
            ServoSet(0, pos[0]);
            break;

        case 2:   // Servo 1 backward
            if(pos[0] - STEP >= SERVO_MIN)
            {
                pos[0] -= STEP;
            }
            ServoSet(0, pos[0]);
            break;

        case 3:   // Servo 2 forward
            if(pos[1] + STEP <= SERVO_MAX)
            {
                pos[1] += STEP;
            }
            ServoSet(1, pos[1]);
            break;

        case 4:   // Servo 2 backward
            if(pos[1] - STEP >= SERVO_MIN)
            {
                pos[1] -= STEP;
            }
            ServoSet(1, pos[1]);
            break;

        case 5:   // Servo 3 forward
            if(pos[2] + STEP <= SERVO_MAX)
            {
                pos[2] += STEP;
            }
            ServoSet(2, pos[2]);
            break;

        case 6:   // Servo 3 backward
            if(pos[2] - STEP >= SERVO_MIN)
            {
                pos[2] -= STEP;
            }
            ServoSet(2, pos[2]);
            break;

        case 7:   // Servo 4 forward + 5&6 backward
            if(pos[3] + STEP <= SERVO_MAX)
            {
                pos[3] += STEP;
            }
            ServoSet(3, pos[3]);
            if(pos[4] - STEP >= SERVO_MIN)
            {
                pos[4] -= STEP;
                pos[5] -= STEP;
            }
            ServoSet(4, pos[4]);
            ServoSet(5, pos[5]);
            break;

        case 8:   // Servo 4 backward + 5&6 forward
            if(pos[3] - STEP >= SERVO_MIN)
            {
                pos[3] -= STEP;
            }
            ServoSet(3, pos[3]);
            if(pos[4] + STEP <= SERVO_MAX)
            {
                pos[4] += STEP;
                pos[5] += STEP;
            }
            ServoSet(4, pos[4]);
            ServoSet(5, pos[5]);
            break;

        case 9:   // Servo 5 & 6 forward
            if(pos[4] + STEP <= SERVO_MAX)
            {
                pos[4] += STEP;
                pos[5] += STEP;
            }
            ServoSet(4, pos[4]);
            ServoSet(5, pos[5]);
            break;

        case 10:  // Servo 5 & 6 backward
            if(pos[4] - STEP >= SERVO_MIN)
            {
                pos[4] -= STEP;
                pos[5] -= STEP;
            }
            ServoSet(4, pos[4]);
            ServoSet(5, pos[5]);
            break;

        case 11:  // Hand open
            pos[6] = HAND_OPEN;
            ServoSet(6, pos[6]);
            break;

        case 12:  // Hand close
            pos[6] = HAND_CLOSE;
            ServoSet(6, pos[6]);
            break;

        case 13:  // Rotate forward
            if(pos[7] + STEP <= SERVO_MAX)
            {
                pos[7] += STEP;
            }
            ServoSet(7, pos[7]);
            break;

        case 14:  // Rotate backward
            if(pos[7] - STEP >= SERVO_MIN)
            {
                pos[7] -= STEP;
            }
            ServoSet(7, pos[7]);
            break;

        case 15:  // Home all
            HomeAll();
            LCD_Update("Arm: HOME       ", "All servos reset");
            break;

        case 16:  // Locating
            LCD_Update("Arm: SEARCHING  ", "Item being      ");
            LCD_SetCursor(1, 0);
            LCD_Print("Located...      ");
            Buzzer_PlayLocating();
            break;

        case 17:  // Grabbed
            LCD_Update("Arm: SUCCESS    ", "Item picked up! ");
            Buzzer_PlayGrabbed();
            break;

        case 18:  // Not found
            LCD_Update("Arm: FAILED     ", "Item can not be ");
            LCD_SetCursor(1, 0);
            LCD_Print("located         ");
            Buzzer_PlayNotFound();
            break;

        default:
            break;
    }
    UART0_OutString("Working\r\n");
}

// ============================================================
// MAIN
// ============================================================
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;   // stop watchdog timer
    Clock_Init48MHz();
    UART0_Init();

    // call all port initialization functions
    Port6_Init();    // buzzer
    Port7_Init();    // servos 1-4
    Port8_Init();    // rotate
    Port9_Init();    // servo 6 + hand
    Port10_Init();   // servo 5 + I2C LCD (P10.2=SDA P10.3=SCL P10.5=servo5)

    // call all timer initialization functions
    TimerA1_Init();
    TimerA3_Init();

    // read current servo positions from timer registers
    Pos_Init();

    // init I2C and LCD
    I2C_Init();
    Clock_Delay1ms(100);
    LCD_Init();

    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    // $$$                                                $$$
    // $$$   CHANGE THE NUMBER BELOW TO TEST A COMMAND   $$$
    // $$$                                                $$$
    // $$$   0  = no command, servos stay as they are    $$$
    // $$$   1  = Servo 1 forward                        $$$
    // $$$   2  = Servo 1 backward                       $$$
    // $$$   3  = Servo 2 forward                        $$$
    // $$$   4  = Servo 2 backward                       $$$
    // $$$   5  = Servo 3 forward                        $$$
    // $$$   6  = Servo 3 backward                       $$$
    // $$$   7  = Servo 4 forward  (5&6 go backward)     $$$
    // $$$   8  = Servo 4 backward (5&6 go forward)      $$$
    // $$$   9  = Servo 5 & 6 forward                    $$$
    // $$$   10 = Servo 5 & 6 backward                   $$$
    // $$$   11 = Hand open                               $$$
    // $$$   12 = Hand close                              $$$
    // $$$   13 = Rotate forward                          $$$
    // $$$   14 = Rotate backward                         $$$
    // $$$   15 = Home all servos to center               $$$
    // $$$   16 = Locating                                $$$
    // $$$   17 = Grabbed                                 $$$
    // $$$   18 = Not found                               $$$
    // $$$                                                $$$
    // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


    uint8_t command = 8;   // <--- CHANGE THIS NUMBER

    LCD_Update("Robotic Arm     ", "Ready!          ");
    Buzzer_PlayStartup();

    if(command != 0)
    {
        MoveRobot(command);
    }

    while(1)
    {
        // servos hold last position
        // change command above and reflash to test
    }
}
