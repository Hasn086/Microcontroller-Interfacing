/* 
 * File:   MCL_TMR0.h
 * Author: hasan
 *
 * Created on 12 ????, 2024, 01:37 ?
 */

#ifndef MCL_TMR0_H
#define	MCL_TMR0_H

/*section : includes*/
#include "../mcal_std_types.h"
#include "pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO_1/HAL_GPIOI.h"
#
/*section : macro declarations */
#define Timer0_Prescaler_Disable_cgf  0u
#define Timer0_Prescaler_Enable_cgf   1u

#define Timer0_Source_Rising_Edge_cgf  1u
#define Timer0_Source_Falling_Edge_cgf 0u

#define Tmr0_Timer_mode  1u
#define Tmr0_counter_mode 0u

#define Timer0_8_Bit_Control_register_mode 1
#define Timer0_16_Bit_Control_register_mode 0

/*section  : macro functions declaretions */
#define Timer0_Prescaler_Disable() (T0CONbits.PSA=1)
#define Timer0_Prescaler_Enable()  (T0CONbits.PSA=0)

#define Timer0_Source_Rising_Edge()  (T0CONbits.T0SE=0)
#define Timer0_Source_Falling_Edge() (T0CONbits.T0SE=1)

#define Timer0_Internal_Clock_Source()  (T0CONbits.T0CS=0)
#define Timer0_External_Clock_Source()  (T0CONbits.T0CS=1)

#define Timer0_8_Bit_Control_register_mode_Enable() (T0CONbits.T08BIT=1)
#define Timer0_16_Bit_Control_register_mode_Enable() (T0CONbits.T08BIT=0)

#define Timer0_Enable()    (T0CONbits.TMR0ON=1)
#define Timer0_Disable()    (T0CONbits.TMR0ON=0)
/*section : data type declaration */
typedef enum{
    Timer0_Prescaler_2=0,
    Timer0_Prescaler_4,
    Timer0_Prescaler_8,
    Timer0_Prescaler_16,
    Timer0_Prescaler_32,
    Timer0_Prescaler_64,
    Timer0_Prescaler_128,
    Timer0_Prescaler_256
}Timer0_Prescaler_Select;
typedef struct{
    #if ADC_Interrupt_Feature_Enable == FEATURE_ENABLE 
    void (* TMR0_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16 tmr0_preload_value ;
    uint8 tmr0_mode          :1;
    uint8 tmr0_counter_edge  :1;
    uint8 Prescaler_enable   :1;
    uint8 tmr0_register_size :1;
    uint8 tmr0_reseerved     :4;
    Timer0_Prescaler_Select Prescaler_value;
}TMR0_conf_t; 
/*section  :  functions declaretions */
std_returntype TMR0_Init(const TMR0_conf_t*_TMR0);
std_returntype TMR0_Dinit(const TMR0_conf_t*_TMR0);
std_returntype TMR0_Write(const TMR0_conf_t*_TMR0,uint16 value);
std_returntype TMR0_Read(const TMR0_conf_t*_TMR0,uint16 *value);
#endif	/* MCL_TMR0_H */

