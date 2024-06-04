/* 
 * File:   mcal_internal_interrupt.h
 * Author: hasan  ismail
 *
 * Created on 08 Nisan, 2024, 12:53 ?
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H
/*section : includes*/
#include "../ADC/HAL_ADC_CONF.h"
#include "../TMR0/MCL_TMR0_CONFG.h"
#include "../TMR1/MCAL_TMR1_CONF.h"
#include "mcal_interrupt_configration.h"
/*section  : macro functions declaretions */
//---------------ADC----------------//
#if ADC_Interrupt_Feature_Enable ==  FEATURE_ENABLE 
#define ADC_INTERRUPTDISABLE()  (PIE1bits.ADIE=0)
#define ADC_INTERRUPTENABLE()  (PIE1bits.ADIE=1)
#define ADC_INTERRUPTFLAGCLEAR()  (PIR1bits.ADIF=0)
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define  ADC_HighPrioritySet()         (IPR1bits.ADIP=1)
#define  ADC_LowPrioritySet()          (IPR1bits.ADIP=0)
#endif
#endif

//---------------TMR0----------------//
#if TMR0_Interrupt_Feature_Enable ==  FEATURE_ENABLE 
#define TMR0_INTERRUPTDISABLE()  (INTCONbits.TMR0IE=0)
#define TMR0_INTERRUPTENABLE()  (INTCONbits.TMR0IE=1)
#define TMR0_INTERRUPTFLAGCLEAR()  (INTCONbits.TMR0IF=0)
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define  TMR0_HighPrioritySet()         (INTCON2bits.TMR0IP=1)
#define  TMR0_LowPrioritySet()          (INTCON2bits.TMR0IP=0)
#endif
#endif
//---------------TMR1----------------//
/*#if TMR1_Interrupt_Feature_Enable ==  FEATURE_ENABLE 
#define TMR1_INTERRUPTDISABLE()  (=0)
#define TMR1_INTERRUPTENABLE()  (=1)
#define TMR1_INTERRUPTFLAGCLEAR()  (=0)
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
#define  TMR1_HighPrioritySet()         (INTCON2bits.TMR0IP=1)
#define  TMR1_LowPrioritySet()          (INTCON2bits.TMR0IP=0)
#endif
#endif*/
/*section : data type declaration */
/*section : macro declarations */
/*section  :  functions declaretions */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

