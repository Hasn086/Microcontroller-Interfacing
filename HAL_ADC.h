/* 
 * File:   HAL_ADC.h
 * Author: hasan
 *
 * Created on 04 ????, 2024, 04:26 ?
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H
/*section : includes*/
#include "../mcal_std_types.h"
#include "../interrupt/mcal_internal_interrupt.h"
#include "../GPIO_1/HAL_GPIOI.h"
#include "pic18f4620.h"
#include "HAL_ADC_CONF.h"
/*section : macro declarations */
#define ADC_AN0_ANALOG_FUNCTIONALITY 0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY 0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY 0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY 0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY 0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY 0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY 0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY 0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY 0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY 0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY 0x01

#define ADC_ALL_DIGITAL_FUNCTIONALITY 0x0F

#define ADC_RIGHT_FORMAT  0x01U
#define ADC_LEFT_FORMAT  0x00U

#define ADC_ENABLE_Voltage_Reference 0x01U
#define ADC_DISABLE_Voltage_Reference 0x00U

#define ADC_CONVERSION_COMPLETED  1
#define ADC_CONVERSION_INPROGRESS 0
/*section  : macro functions declaretions */
/*A/D Conversion Status bit : A/D conversion in progress / A/D Idle*/
#define ADC_Conversion_Status()  (ADCON0bits.GO_DONE)
#define ADC_start_Conversion()  (ADCON0bits.GODONE=1)
#define ADC_Converter_enabled()  (ADCON0bits.ADON=1)
#define  ADC_Converter_disabled() (ADCON0bits.ADON=0)
#define ADC_Voltage_Reference_ENABLE()  do{ADCON1bits.VCFG1=1;\
                                            ADCON1bits.VCFG0=1;\
                                           }while(0)
#define ADC_Voltage_Reference_DISABLE()  do{ADCON1bits.VCFG1=0;\
                                             ADCON1bits.VCFG0=0;\
                                            }while(0)
#define ADC_ANALOG_DIGITAL_PORT_CONFG(_CONFG)  (ADCON1bits.PCFG=_CONFG)

#define ADC_RESULT_RIGHT_FORMAT()  (ADCON2bits.ADFM=1)
#define ADC_RESULT_LEFT_FORMAT()  (ADCON2bits.ADFM=0)
/*section : data type declaration */
typedef enum{
    ADC_CHANNEL_AN0=0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11, 
    ADC_CHANNEL_AN12, 
}ADC_channel_select;
typedef enum{
    ADC_0_TAD=0,
    ADC_2_TAD,  
    ADC_4_TAD,
    ADC_8_TAD,  
    ADC_12_TAD,
    ADC_16_TAD,  
    ADC_20_TAD,
}ADC_Acquisition_Time_Select;
typedef enum{
    ADC_Conversion_Clock_FOSC_DIV_2=0,
    ADC_Conversion_Clock_FOSC_DIV_8,
    ADC_Conversion_Clock_FOSC_DIV_32,
    ADC_Conversion_Clock_FOSC_DIV_FRC,
    ADC_Conversion_Clock_FOSC_DIV_4,
    ADC_Conversion_Clock_FOSC_DIV_16,
    ADC_Conversion_Clock_FOSC_DIV_64       
}ADC_Conversion_Clock_Select;
typedef struct{
#if ADC_Interrupt_Feature_Enable == FEATURE_ENABLE 
    void (* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    ADC_Acquisition_Time_Select  Acquisition_Time;
    ADC_Conversion_Clock_Select  Conversion_Clock;
    ADC_channel_select channel_select ;
    uint8 Voltage_Reference :1;
    uint8 select_format :1;
    uint8 ADC_Reserved :6;
}ADC_CONFG_t;
/*section  :  functions declaretions */
std_returntype ADC_Init(const ADC_CONFG_t *_adc);
std_returntype ADC_DeInit(const ADC_CONFG_t *_adc);
std_returntype ADC_SELECTCHANNEL(const ADC_CONFG_t *_adc,ADC_channel_select _channel);
std_returntype ADC_StartConversion(const ADC_CONFG_t *_adc);
std_returntype ADC_isConversionDone(const ADC_CONFG_t *_adc,uint8 *conversion_stutuse);
std_returntype ADC_Conversionresults (const ADC_CONFG_t *_adc,uint16 *conversion_results);
std_returntype ADC_GetConversion(const ADC_CONFG_t *_adc,ADC_channel_select _channel,
                                 uint16 *conversion_results);
std_returntype ADC_StartConversion_interrupt(const ADC_CONFG_t *_adc,ADC_channel_select _channel);
#endif	/* HAL_ADC_H */

