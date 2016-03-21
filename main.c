// ******************************************************************************************* //
//  This comment is a test for the github repository. test again.
// File:         lab2p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "constants.h"
#include "leds.h"
#include "interrupt.h"
#include "switch.h"
#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "keypad.h"
#include "ADC.h"
#include "PWM.h"


typedef enum state_enum {
    INIT, READ_ADC, SET_PWM, SET_DIRECTION, PRINT_LCD, FORWARD, REVERSE
} state_t;


volatile state_t myState;
volatile int read;
volatile int read_reset;    /*integer to store value of the reset button*/
volatile char timer_flag;   /*The timer flag increments every 10ms*/
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    state_t direction = FORWARD;
    int voltageADC = 0;
    int lastVoltage = 0;
    char charToWrite = 0;
    char numberToPrint[5] = {' ', ' ',  ' ',  ' ',  '\0'};
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    myState = INIT;
    initLEDs();
    initTimers();
    initLCD();
    initKeypad();
    initPWM();
    initADC();
    
    while(1)
    {
        switch(myState) {
            case INIT:
                myState = READ_ADC;
                break;
            case READ_ADC:
                voltageADC = ADC1BUF0;
                delayUs(1000);
                myState = SET_DIRECTION;
                break;
            case SET_DIRECTION:
                if(voltageADC >= 512) {
                    direction = FORWARD;
                    LATGbits.LATG13 = ENABLED;
                    LATDbits.LATD5 = DISABLED;
                    LATGbits.LATG15 = ENABLED;
                    LATDbits.LATD11 = DISABLED;
                }
                else {
                    direction = REVERSE;
                    LATDbits.LATD11 = ENABLED;
                    LATGbits.LATG13 = DISABLED;
                    LATDbits.LATD5 = ENABLED;
                    LATGbits.LATG15 = DISABLED;
                    
                }
                
                myState = SET_PWM;
                break;
            case SET_PWM:
                
                if(direction == FORWARD) {
                    //We know the ADC is greater than or equal to 512
                    OC3RS = voltageADC;
                    OC4RS = voltageADC;
                }
                if(direction == REVERSE) {
                    //We know the ADC is less than 512
                    OC3RS = 1023 - voltageADC;
                    OC4RS = 1023 - voltageADC;
                }
                
                if(voltageADC != lastVoltage) {
                    lastVoltage = voltageADC;
                    myState = PRINT_LCD;
                }
                else {
                    myState = READ_ADC;
                }
                break;
            case PRINT_LCD:
                itoa(numberToPrint, voltageADC, 10);
                clearLCD();
                delayUs(10000);
                moveCursorLCD(0, 5);
                printStringLCD(numberToPrint);
                delayUs(30000);
                myState = READ_ADC;
                break;
        }
    }
    
    return 0;
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) timer1Handler(void){
    IFS0bits.T1IF = FLAG_DOWN;
    TMR1 = 0;
}

/*
** The change notification interrupt handles the start/stop button and the 
** reset button logic, hence its length. There are really only two switch statements
** in the ISR, so it really doesn't have to make many decisions that would 
** bloat the ISR.
*/

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button
    PORTB;
    IFS1bits.CNBIF = FLAG_DOWN;
    IFS0bits.T4IF = 0;      //lower timer 4 flag for delay
    TMR4 = 0;  
    PR4 = 10000;//manually clear timer 4 register
    T4CONbits.ON = 1;       //turn timer 4 on.
    while(IFS0bits.T4IF != 1){};    //5ms delay
    T4CONbits.ON = 0;       //turn off timer 4
    IFS0bits.T4IF = 0;
    read = PORTBbits.RB12;
    if(1){
        switch(myState) {
            default:
                myState = myState;
                break;
        }
    } else {
        myState = myState;
    }
}
