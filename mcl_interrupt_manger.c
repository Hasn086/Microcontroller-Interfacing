
#include "mcl_interrupt_manger.h"

#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
void __interrupt() interruptMangerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
         INT0_ISR();
    }
}
void __interrupt(low_priority) interruptMangerLow(void){

}
    
    
    
#else
void __interrupt() interruptMangerHigh(void){
    if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
        //PIR1bits.ADIF=0;
    }
    else{}
    
   /* if((INTERRUPT_ENABLE == INTCONbits.TMR0IE)&&(INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TMR0_ISR();
        INTCONbits.TMR0IF=0;
    }
    else{} */
    
}
#endif