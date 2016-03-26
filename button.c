
#include <proc/p32mx470f512l.h>
#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
//#include "led.h"
#include "constants.h"
#include "interrupt.h"
#include "button.h"


void initButton(void) {
    //asm volatile("di");h
    //Used to be D6, now D2
    TRISDbits.TRISD7 = INPUT;   //enable the button pin as an input
    CNCONDbits.ON = 1;
    CNENDbits.CNIED7 = 1;       // Enable interrupt for button
    CNPUDbits.CNPUD7 = 1;        // Enable Internal Pull-up resistor
    IPC8bits.CNIP = 7; //CHANGED THIS!!!!
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    
    // INTEnableSystemMultiVectoredInt();
    //asm volatile("ei");
    return;
}
