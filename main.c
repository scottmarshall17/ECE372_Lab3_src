// ******************************************************************************************* //
//  This comment is a test for the github repository. test again.
// File:         lab2p1.c
// Date:         
// Authors:     #Nick is attempting to make a contribution to this group. Woo! 
//              All comments by me will have a '#' sign at the beginning 
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
    //defines the possible states for the FSM
    INIT, READ_ADC, SET_PWM, SET_DIRECTION, PRINT_LCD, FORWARD, REVERSE, IDLE 
} state_t;


volatile state_t direction = FORWARD;   //#Variable to tell us what direction the robot needs to go (used in ISR)
volatile int dir_count = 0;             //#Variable used to tell us where to go from the IDLE state (used in ISR)
volatile state_t myState;
volatile int read;
volatile int read_reset;    /*integer to store value of the reset button*/
volatile char timer_flag;   /*The timer flag increments every 10ms*/
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{
    //state_t direction = FORWARD;                  //#Nick commented this out 
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
                voltageADC = ADC1BUF0;  //0-1023
                delayUs(1000);
                myState = SET_DIRECTION;
                break;
            case SET_DIRECTION:
                if(direction == FORWARD) {
                    //direction = FORWARD;                      //#No longer need this line 
                    LATDbits.LATD5 = DISABLED;                  //#Assuming that D5 moves it backward when set high 
                    LATDbits.LATD11 = DISABLED;                 //#Assuming that D11 moves it backward when set high 
                    LATGbits.LATG13 = ENABLED;                  //#Assuming that G13 moves it forward when set high 
                    LATGbits.LATG15 = ENABLED;                  //#Assuming that G15 moves it forward when set high 
                                                                //#Assuming(D5 and G13)are a pair and(D11 and G15)are a pair 
                    }
                else if (direction == REVERSE){
                    //direction = REVERSE;                      //#No longer need this line 
                    LATDbits.LATD5 = ENABLED;
                    LATDbits.LATD11 = ENABLED;
                    LATGbits.LATG13 = DISABLED;
                    LATGbits.LATG15 = DISABLED;
                    
                }
                else {
                    //#if not FORWARD or REVERSE we must be in IDLE.
                    LATDbits.LATD5 = DISABLED;
                    LATDbits.LATD11 = DISABLED;
                    LATGbits.LATG13 = DISABLED;
                    LATGbits.LATG15 = DISABLED;

                }
                myState = SET_PWM;
                break;
            case SET_PWM:
                
                if(direction == FORWARD) {
                    OC3RS = voltageADC;
                    OC4RS = voltageADC;

                    //#let OC3RS be X
                    //#let OC4RS be 1-X equivalent on the pot
                    
                    if (voltageADC == 511){
                        //#both motors are operate at full speed ahead 
                    }
                    else if(voltageADC > 511){
                        //#OC3RS = full speed ahead
                        //#OC4RS = fractional speed ahead
                    }
                    else {
                        //#voltageADC must be < 511
                        //OC3RS = fractional speed ahead
                        //OC4RS = full speed ahead
                    }

                }
                if(direction == REVERSE) {
                    
                    OC3RS = 1023 - voltageADC;
                    OC4RS = 1023 - voltageADC;
                    
                    //#if the robot turn the wrong way when in reverse 
                    //when we first test it, just flip 
                    //what gets assigned to the OC3RS and OC4RS
                    if (voltageADC == 511){
                        //#both motors are operate at full speed backwards 
                    }
                    else if(voltageADC > 511){
                        //#OC3RS = full speed backwards
                        //#OC4RS = fractional speed backwards
                    }
                    else {
                        //#voltageADC must be < 511
                        //#OC3RS = fractional speed backwards
                        //#OC4RS = full speed backwards
                    }
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
                /*itoa(numberToPrint, voltageADC, 10);
                clearLCD();
                delayUs(10000);
                moveCursorLCD(0, 5);
                printStringLCD(numberToPrint);
                delayUs(30000);
                 */
                printVoltage(voltageADC);
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

//# Totes need to create an ISR for when the button gets pressed. 
//  IDK how to do that tho... this is my best guess
//
// void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void){
//     //puts flag down
//     switch(direction) {
//          case(FORWARD):
//              direction = IDLE;
//              dir_count = 1;
//              break;
//          case(BACKWARD):
//              direction = IDLE;
//              dir_count = 0;
//              break;
//          case(IDLE):
//              if(count == 0){
//                  direction = FORWARD;
//              }
//              else {
//                  //count must be 1.
//                  direction = BACKWARD;
//              }
//              break;
//          }
// }
//
//