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
  ENTER_PHASE, SCANNING_R0, SCANNING_R1, SCANNING_R2, SCANNING_R3, READ_INPUT, WRITELCD, PASS_CHECK,
          VALID, INVALID, SET_PASS, STORE_PASS
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
    
    SYSTEMConfigPerformance(10000000);
    enableInterrupts();
    myState = ENTER_PHASE;
    initLEDs();
    initTimers();
    initLCD();
    initKeypad();
    moveCursorLCD(0, 0);
    
    while(1)
    {
        switch(myState) {
            case ENTER_PHASE:
                
                break;
            case SCANNING_R0:
               
                break;
            case SCANNING_R1:
               
                break;
            case SCANNING_R2:
                
                break;
            case SCANNING_R3:
                
                break;
            case READ_INPUT:
                
                break;
            case WRITELCD:
                
                break;
            case PASS_CHECK:
                
                break;
            case VALID:
                
                break;
            case INVALID:
                
                break;
            case SET_PASS:
                
                break;
            case STORE_PASS:
                
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
    IFS0bits.T3IF = 0;      //lower timer 2 flag for delay
    TMR3 = 0;  
    PR3 = 10000;//manually clear timer 2 register
    T3CONbits.ON = 1;       //turn timer 2 on.
    while(IFS0bits.T3IF != 1){};    //5ms delay
    T3CONbits.ON = 0;       //turn off timer 3
    IFS0bits.T3IF = 0;
    read = PORTBbits.RB12;
    if(1){
        switch(myState) {
            case SCANNING_R0:
                myState = READ_INPUT;
                break;
            case SCANNING_R1:
                myState = READ_INPUT;
                break;
            case SCANNING_R2:
                myState = READ_INPUT;
                break;
            case SCANNING_R3:
                myState = READ_INPUT;
                break;
            default:
                myState = myState;
                break;
        }
    } else {
        myState = myState;
    }
}
