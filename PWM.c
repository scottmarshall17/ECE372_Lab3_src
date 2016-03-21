/* This file contains the functions necessary to use PWM on the PIC32 */
#include <xc.h>
#include "constants.h"
#include "PWM.h"

void initPWM() {
    TRISGbits.TRISG13 = OUTPUT;     //For first motor - in1
    TRISDbits.TRISD5 = OUTPUT;      //--in2
    TRISGbits.TRISG15 = OUTPUT;     //For second motor - in1
    TRISDbits.TRISD11 = OUTPUT;     //--in2
    
    TRISGbits.TRISG0 = OUTPUT;
    TRISFbits.TRISF1 = OUTPUT;
    
    RPF1Rbits.RPF1R = 0b1011; //Map output to OC3
    RPG0Rbits.RPG0R = 0b1011; //Map output to OC4
    
    //------OC3 Config------------
    
    OC3R = 500;     //initial Duty Cycle
    OC3RS = 500;    //next Duty cycle
    
    OC3CONbits.SIDL = 0;
    OC3CONbits.OC32 = BIT_COMPARE_16;
    OC3CONbits.OCTSEL = TIMER3;
    OC3CONbits.OCM = PWM_MODE;
    
    //------OC4 Config------------
    
    OC4R = 200;     //initial Duty Cycle
    OC4RS = 200;    //next Duty cycle
    
    OC4CONbits.SIDL = 0;
    OC4CONbits.OC32 = BIT_COMPARE_16;
    OC4CONbits.OCTSEL = TIMER3;
    OC4CONbits.OCM = PWM_MODE;
    
    //----Turn On OC3 and OC4-----
    
    T3CONbits.TCKPS = PS_1;
    T3CONbits.ON = ENABLED;
    
    OC3CONbits.ON = ENABLED;
    OC4CONbits.ON = ENABLED;
    
    
    
    return;
}