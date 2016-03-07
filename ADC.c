
#include <xc.h>
#include "constants.h"
#include "ADC.h"

void initADC() {
    //Use AN2/RB2 as the ADC pin
    ANSELBbits.ANSB2 = ENABLED;
    TRISBbits.TRISB2 = INPUT;
    
    AD1CON1bits.SIDL = 0;
    AD1CON1bits.FORM = INTEGER;
    AD1CON1bits.SSRC = AUTO;
    AD1CON1bits.CLRASAM = 0;
    AD1CON1bits.ASAM = 1;
    AD1CON2bits.VCFG = 0x00;
    AD1CON2bits.OFFCAL = 0;
    AD1CON2bits.CSCNA = NO_SCAN;
    AD1CON2bits.BUFM = 0;
    AD1CON2bits.SMPI = 15;
    AD1CON2bits.ALTS = 0;
    AD1CON3bits.ADRC = 0;
    AD1CON3bits.SAMC = 3;
    AD1CON3bits.ADCS = 8;
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 2;
    
    AD1CON1bits.ON = ENABLED;
    
    
    return;
}