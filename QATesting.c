#include "QATesting.h"

void initLEDsQA() {
    TRISDbits.TRISD0 = 0;
    LATDbits.LATD0 = 0;
}

void delayUsTest() {
    initLEDsQA();

    while (1) {
        LATDbits.LATD0 = 1;
        delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        LATDbits.LATD0 = 0;
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
        delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);
delayUs(20000);

    }

    //int i = 0;


    /*for(i=1;i<60000;i++){
        LATDbits.LATD0 = 1;
        delayUs(i);
        LATDbits.LATD0 = 0;
        delayUs(i);
    }*/
}
