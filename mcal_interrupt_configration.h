/* 
 * File:   mcal_interrupt_configration.h
 * Author: hasan ismail 
 *
 * Created on 08 ?????, 2024, 12:47 ?
 */

#ifndef MCAL_INTERRUPT_CONFIGRATION_H
#define	MCAL_INTERRUPT_CONFIGRATION_H
/*section : includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_cfg.h" 
/*section : macro declarations */
#define INTERRUPT_ENABLE              1 
#define INTERRUPT_DISABLE             0 
#define INTERRUPT_OCCUR               1 
#define INTERRUPT_NOR_OCCUR           0 
#define INTERRUPT_PRIORITY_ENABLE     1 
#define INTERRUPT_PRIORITY_DINTERRUPT_PRIORITY_ENABLEISABLE    0 


/*section  : macro functions declaretions */
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define INTERRUPT_PRIORITYLevelENABLE()    (RCONbits.IPEN=1)
#define INTERRUPT_PRIORITYLevelDISABLE()    (RCONbits.IPEN=0)
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH=1) // This macro will enable high priority global interrupt
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH=0) // This macro will disnable high priority global interrupt
#define INTERRUPT_GlobalInterruptLowEnable()  (INTCONbits.GIEL=1) // This macro will enable low priority global interrupt
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL=0) // This macro will disable low  priority global interrupt
#else
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE=1) // This macro will enable  global interrupt
#define INTERRUPT_GlobalInterruptDisable()  (INTCONbits.GIE=0) // This macro will disnable  global interrupt

#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE=1) // This macro will enable preipheral interrupt
#define INTERRUPT_PeripheralInterruptDisnable()  (INTCONbits.PEIE=0) // This macro will disable peripheral interrupt
#endif
/*section : data type declaration */
typedef enum {
    INTERRUPT_LOW_PRIORITY=0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_cfg;
/*section  :  functions declaretions */


#endif	/* MCAL_INTERRUPT_CONFIGRATION_H */

