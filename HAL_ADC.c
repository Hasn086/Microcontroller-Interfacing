#include "HAL_ADC.h"
static inline void adc_input_channel_port_confg(ADC_channel_select _channel);
static inline void Select_result_format(const ADC_CONFG_t *_adc);
static inline void Select_Voltage_Reference(const ADC_CONFG_t *_adc);
#if ADC_Interrupt_Feature_Enable == FEATURE_ENABLE
static void (* ADC_interruptHandler)(void)=NULL;
#endif
/**
 * 
 * @param _adc
 * @return 
 */
std_returntype ADC_Init(const ADC_CONFG_t *_adc){
    std_returntype RET=E_OK;
    if(NULL == _adc){
       RET=E_NOK; 
    }
    else{
        /*disable the ADC*/
        ADC_Converter_disabled();
        /*Configuring Acquisition Time*/
        ADCON2bits.ACQT=_adc->Acquisition_Time;
        /*Conversion Clock Select*/
        ADCON2bits.ADCS= _adc->Conversion_Clock;
        /* Analog Channel Select*/
        ADCON0bits.CHS=_adc->channel_select;
        adc_input_channel_port_confg(_adc->channel_select);
        /*Configuring result format*/
         Select_result_format(_adc);
        /*Configuring thr interrupt*/
       #if ADC_Interrupt_Feature_Enable == FEATURE_ENABLE
        ADC_INTERRUPTENABLE();
        ADC_INTERRUPTFLAGCLEAR();
        #if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY==_adc->priority){ADC_HighPrioritySet();}
        else if(INTERRUPT_LOW_PRIORITY==_adc->priority){ ADC_LowPrioritySet();}
        else{/*Nothing*/}
        
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();    
#endif
         ADC_interruptHandler=_adc->ADC_InterruptHandler;
#endif
        /*Configuring Voltage Reference*/
        Select_Voltage_Reference(_adc);
        /*enable the ADC*/
        ADC_Converter_enabled();
    }
     return RET;
}
/**
 * 
 * @param _adc
 * @return 
 */
std_returntype ADC_DeInit(const ADC_CONFG_t *_adc){
   std_returntype RET=E_OK;
    if(NULL == _adc){
       RET=E_NOK; 
    }
    else{
        /*disable the ADC*/
        ADC_Converter_disabled();
        /*Configuring thr interrupt*/
        #if ADC_Interrupt_Feature_Enable == FEATURE_ENABLE
        ADC_INTERRUPTDISABLE();
#endif
        RET=E_OK;
       
    }
     return RET; 
}
/**
 * 
 * @param _adc
 * @param _channel
 * @return 
 */
std_returntype ADC_SELECTCHANNEL(const ADC_CONFG_t *_adc,ADC_channel_select _channel){
    std_returntype RET=E_OK;
    if(NULL == _adc){
       RET=E_NOK; 
    }
    else{
       /* Analog Channel Select*/
        ADCON0bits.CHS=_channel;
        adc_input_channel_port_confg(_channel); 
    }
     return RET;
}
/**
 * 
 * @param _adc
 * @return 
 */
std_returntype ADC_StartConversion(const ADC_CONFG_t *_adc){
    std_returntype RET=E_OK;
    if(NULL == _adc){
       RET=E_NOK; 
    }
    else{
        ADC_start_Conversion();
        RET=E_OK;
    }
     return RET;
}
/**
 * 
 * @param _adc
 * @param conversion_stutuse
 * @return 
 */
std_returntype ADC_isConversionDone(const ADC_CONFG_t *_adc,uint8 *conversion_stutuse){
    std_returntype RET=E_OK;
    if((NULL == _adc)||(NULL == conversion_stutuse)){
       RET=E_NOK; 
    }
    else{
        *conversion_stutuse=(uint8)(!(ADCON0bits.GO_nDONE));
                RET=E_OK;
    }
     return RET;
}
/**
 * 
 * @param _adc
 * @param conversion_results
 * @return 
 */
std_returntype ADC_Conversionresults (const ADC_CONFG_t *_adc,uint16 *conversion_results){
    std_returntype RET=E_OK;
    if((NULL == _adc)||(NULL == conversion_results)){
       RET=E_NOK; 
    }
    else{
    if(ADC_RIGHT_FORMAT==_adc->select_format){ 
      *conversion_results=(uint16)((ADRESH << 8) + ADRESL);
    }
    else if(ADC_LEFT_FORMAT==_adc->select_format){
      *conversion_results=((uint16)((ADRESH << 8) + ADRESL)>>6);
    }
    else{ *conversion_results=(uint16)((ADRESH << 8) + ADRESL);}
    }
     return RET; 
}
/**
 * 
 * @param _adc
 * @param _channel
 * @param conversion_results
 * @return 
 */
std_returntype ADC_GetConversion(const ADC_CONFG_t *_adc,ADC_channel_select _channel,
                                 uint16 *conversion_results){
    std_returntype RET=E_OK;
    uint8 l_conversion_results=0;
    if((NULL == _adc)||(NULL == conversion_results)){
       RET=E_NOK; 
    }
    else{
        RET=ADC_SELECTCHANNEL(_adc,_channel);
         ADC_Converter_enabled();
        RET=ADC_StartConversion(_adc);
        /*check if the */
        while(ADCON0bits.GO_DONE);
        RET=ADC_Conversionresults(_adc,conversion_results);
       
    }
     return RET;
}
static inline void adc_input_channel_port_confg(ADC_channel_select _channel){
    switch(_channel){
        case ADC_CHANNEL_AN0: set_bit(TRISA,_TRISA_RA0_POSN); break; 
        case ADC_CHANNEL_AN1: set_bit(TRISA,_TRISA_RA1_POSN); break; 
        case ADC_CHANNEL_AN2: set_bit(TRISA,_TRISA_RA2_POSN); break; 
        case ADC_CHANNEL_AN3: set_bit(TRISA,_TRISA_RA3_POSN); break; 
        case ADC_CHANNEL_AN4: set_bit(TRISA,_TRISA_RA5_POSN); break; 
        case ADC_CHANNEL_AN5: set_bit(TRISE,_TRISE_RE0_POSN); break; 
        case ADC_CHANNEL_AN6: set_bit(TRISE,_TRISE_RE1_POSN); break; 
        case ADC_CHANNEL_AN7: set_bit(TRISE,_TRISE_RE2_POSN); break; 
        case ADC_CHANNEL_AN8: set_bit(TRISB,_TRISB_RB2_POSN); break; 
        case ADC_CHANNEL_AN9: set_bit(TRISB,_TRISB_RB3_POSN); break; 
        case ADC_CHANNEL_AN10: set_bit(TRISB,_TRISB_RB1_POSN); break; 
        case ADC_CHANNEL_AN11: set_bit(TRISB,_TRISB_RB4_POSN); break; 
        case ADC_CHANNEL_AN12: set_bit(TRISB,_TRISB_RB0_POSN); break; 
        default:;
    }
}

static inline void Select_result_format(const ADC_CONFG_t *_adc){
  if(ADC_RIGHT_FORMAT==_adc->select_format){ 
    ADC_RESULT_RIGHT_FORMAT();  
  }
  else if(ADC_LEFT_FORMAT==_adc->select_format){
     ADC_RESULT_LEFT_FORMAT(); 
  }
  else{ADC_RESULT_RIGHT_FORMAT();}
}


static inline void Select_Voltage_Reference(const ADC_CONFG_t *_adc){
  if(ADC_ENABLE_Voltage_Reference==_adc->Voltage_Reference){ 
   ADC_Voltage_Reference_ENABLE();  
  }
  else if(ADC_DISABLE_Voltage_Reference==_adc->Voltage_Reference){
   ADC_Voltage_Reference_DISABLE(); 
  }
  else{  ADC_Voltage_Reference_DISABLE(); } 
}
std_returntype ADC_StartConversion_interrupt(const ADC_CONFG_t *_adc,ADC_channel_select _channel){
    
    std_returntype RET=E_OK;
    uint8 l_conversion_results=0;
    if(NULL == _adc){
        RET=E_NOK;
    }
    else{
        RET=ADC_SELECTCHANNEL(_adc,_channel);
         ADC_Converter_enabled();
        RET=ADC_StartConversion(_adc);
        
        RET=E_OK;
    }
    return RET;
}

void ADC_ISR(void){
    ADC_INTERRUPTFLAGCLEAR();
    if(ADC_interruptHandler){
    ADC_interruptHandler();
    }
}