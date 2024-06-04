/* 
 * File:   mcal_external_interrupt.h
 * Author: hasan ismail
 *
 * Created on 08 Nisan, 2024, 12:54 ?
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H
/*section : includes*/
#include "mcal_interrupt_configration.h"
#include "../GPIO_1/HAL_GPIOI.h"
/*section  : macro functions declaretions */
#if EXTERNAL_INTERRUPT_INTx_ENABLE == FEATURE_ENABLE 
#define EXT_INT0_INTERRUPTENABLE()  (INTCONbits.INT0IE=1)
#define EXT_INT0_INTERRUPTDISABLE()  (INTCONbits.INT0IE=0)
#define EXT_INT0_INTERRUPTFLAGCLEAR()  (INTCONbits.INT0IF=0)
#define EXT_INT0_RisingEdgSet()            (INTCON2bits.INTEDG0=1) 
#define EXT_INT0_FallingEdgSet()            (INTCON2bits.INTEDG0=0) 
#define EXT_INT1_INTERRUPTENABLE()  (INTCON3bits.INT1IE=1)
#define EXT_INT1_INTERRUPTDISABLE()  (INTCON3bits.INT1IE=0)
#define EXT_INT1_INTERRUPTFLAGCLEAR()  (INTCON3bits.INT1IF=0)
#define EXT_INT1_RisingEdgSet()            (INTCON2bits.INTEDG1=1) 
#define EXT_INT1_FallingEdgSet()            (INTCON2bits.INTEDG1=0)
#define EXT_INT2_INTERRUPTENABLE()  (INTCON3bits.INT2IE=1)
#define EXT_INT2_INTERRUPTDISABLE()  (INTCON3bits.INT2IE=0)
#define EXT_INT2_INTERRUPTFLAGCLEAR()  (INTCON3bits.INT2IF=0)
#define EXT_INT2_RisingEdgSet()            (INTCON2bits.INTEDG2=1) 
#define EXT_INT2_FallingEdgSet()            (INTCON2bits.INTEDG2=0)
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define  EXT_INT1_HighPrioritySet()         (INTCON3bits.INT1IP=1)
#define  EXT_INT1_LowPrioritySet()          (INTCON3bits.INT1IP=0)
#define  EXT_INT2_LowPrioritySet()          (INTCON3bits.INT2IP=1)
#define  EXT_INT2_HighPrioritySet()         (INTCON3bits.INT2IP=0)

#endif
#endif
#if EXTERNAL_INTERRUPT_Onchange_ENABLE == FEATURE_ENABLE 
#define EXT_RBx_INTERRUPTENABLE()  (INTCONbits.RBIE=1)
#define EXT_RBx_INTERRUPTDISABLE()  (INTCONbits.RBIE=0)
#define EXT_RBx_INTERRUPTFLAGCLEAR()  (INTCONbits.RBIF=0)
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define  EXT_RBx_HighPrioritySet()         (INTCON2bits.RBIP=1)
#define  EXT_RBx_LowPrioritySet()          (INTCON2bits.RBIP=0)
#endif
#endif
/*section : macro declarations */
/*section : data type declaration */
typedef enum{
   INTERRUPT_FALLING_EDGE=0,
   INTERRUPT_RISING_EDGE    
}interrupt_INTx_edg;
typedef enum{
   INTERRUPT_EXTERNAL_INT0=0,
   INTERRUPT_EXTERNAL_INT1,
   INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_source;
typedef struct{
    void (* EXTI_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edg edge;
    interrupt_INTx_source source;
    interrupt_priority_cfg priority;
}interrupt_INTx_t;
typedef struct{
    void (* EXTI_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_priority_cfg priority;
}interrupt_RBx_t;
/*section  :  functions declaretions */
std_returntype INTERRUPT_INTx_Init(const interrupt_INTx_t *int_obj);
std_returntype INTERRUPT_INTx_DeInit(const interrupt_INTx_t *int_obj);
std_returntype INTERRUPT_RBx_Init(const interrupt_RBx_t *int_obj);
std_returntype INTERRUPT_RBx_DeInit(const interrupt_RBx_t *int_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

