/* 
 * File:   mcal_external_interrupt.c
 * Author: hasan ismail
 *
 * Created on 08 Nisan, 2024, 12:54 ?
 */
#include "mcal_external_interrupt.h"

static void (*INT0_interruptHandler)(void)=NULL;
static void (*INT1_interruptHandler)(void)=NULL;
static void (*INT2_interruptHandler)(void)=NULL;

static std_returntype INT0_SetinterruptHandler( void *INT0_interruptHandler);
static std_returntype INT1_SetinterruptHandler( void *INT1_interruptHandler);
static std_returntype INT2_SetinterruptHandler( void *INT2_interruptHandler);

static std_returntype INTERRUPT_INTx_SetinterruptHandler(const interrupt_INTx_t *int_obj);

static std_returntype INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *int_obj);
static std_returntype INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *int_obj);
static std_returntype INTERRUPT_INTx_Priority_init(const interrupt_INTx_t *int_obj);
static std_returntype INTERRUPT_INTx_EDGE_init(const interrupt_INTx_t *int_obj);
static std_returntype INTERRUPT_INTx_PIN_init(const interrupt_INTx_t *int_obj);
static std_returntype INTERRUPT_INTx_Clearflag(const interrupt_INTx_t *int_obj);


static std_returntype INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *int_obj);
static std_returntype INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *int_obj);
static std_returntype INTERRUPT_RBx_Priority_init(const interrupt_RBx_t *int_obj);
static std_returntype INTERRUPT_RBx_PIN_init(const interrupt_RBx_t *int_obj);

std_returntype INTERRUPT_INTx_Init(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        /*Disable the external interrupt*/
       RET=INTERRUPT_INTx_DISABLE(int_obj);
        /*clear interrupt flag : external interrupt did not occur*/
        RET=INTERRUPT_INTx_Clearflag(int_obj);
        /*configure external interrupt edg */
        RET=INTERRUPT_INTx_EDGE_init(int_obj);
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
        /*configure external interrupt priority*/
        RET=INTERRUPT_INTx_Priority_init(int_obj);
#endif
        /*configure external interrupt I/O pin*/
        RET=INTERRUPT_INTx_PIN_init(int_obj);
        /*configure Defult  interrupt callback*/
        RET=INTERRUPT_INTx_SetinterruptHandler(int_obj);
        /*Enable the external interrupt*/
        RET=INTERRUPT_INTx_ENABLE(int_obj);
}
    return RET;
} 
void INT0_ISR(void){
    /*the INT0 External interrupt occureed(must be cleared in software)*/
    EXT_INT0_INTERRUPTFLAGCLEAR();
    /*code*/
    /*callback function gets call every time is ISR executes*/
    if(INT0_interruptHandler){INT0_interruptHandler();}
}
void INT1_ISR(void){
    /*the INT1 External interrupt occureed(must be cleared in software)*/
    EXT_INT1_INTERRUPTFLAGCLEAR();
    /*code*/
    /*callback function gets call every time is ISR executes*/
    if(INT1_interruptHandler){INT1_interruptHandler();}
}
void INT2_ISR(void){
    /*the INT2 External interrupt occureed(must be cleared in software)*/
    EXT_INT2_INTERRUPTFLAGCLEAR();
    /*code*/
    /*callback function gets call every time is ISR executes*/
    if(INT2_interruptHandler){INT2_interruptHandler();}
}
/**
 * 
 * @param pass my int_obj as pointer 
 * @return my standart return type if RET=1 the function faild if RET=0 the function successful
 */
std_returntype INTERRUPT_INTx_DeInit(const interrupt_INTx_t *int_obj){
   std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        RET=INTERRUPT_INTx_DISABLE(int_obj);
}
    return RET; 
}
std_returntype INTERRUPT_RBx_Init(const interrupt_RBx_t *int_obj){
  std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
}
    return RET;  
}
std_returntype INTERRUPT_RBx_DeInit(const interrupt_RBx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
}
    return RET;
}

static std_returntype INTERRUPT_INTx_ENABLE(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT0_INTERRUPTENABLE() ;
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT1_INTERRUPTENABLE() ;
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                EXT_INT2_INTERRUPTENABLE() ;
                RET=E_OK; 
                break;
            default : RET=E_NOK;
}
    
}
    return RET;
}
static std_returntype INTERRUPT_INTx_DISABLE(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_INTERRUPTDISABLE() ;
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_INTERRUPTDISABLE() ;
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_INTERRUPTDISABLE() ;
                RET=E_OK; 
                break;
            default : RET=E_NOK;
} 
}
    return RET;
}
#if INTERRUPT_PRIORITY_Level_ENABLE == FEATURE_ENABLE
static std_returntype INTERRUPT_INTx_Priority_init(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                     EXT_INT1_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT1_HighPrioritySet();}
                else{/*Nothing*/}
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
               if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT2_LowPrioritySet();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){EXT_INT2_HighPrioritySet();}
                else{/*Nothing*/}
                RET=E_OK; 
                break;
            default : RET=E_NOK;
        }
}
    return RET;
}
#endif
static std_returntype INTERRUPT_INTx_EDGE_init(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
       switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_RISING_EDGE==int_obj->edge){EXT_INT0_RisingEdgSet();}
                else if(INTERRUPT_FALLING_EDGE==int_obj->edge){EXT_INT0_FallingEdgSet();}
                else{/**/}
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_RISING_EDGE==int_obj->edge){EXT_INT1_RisingEdgSet();}
                else if(INTERRUPT_FALLING_EDGE==int_obj->edge){EXT_INT1_FallingEdgSet();}
                else{/**/}
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_RISING_EDGE==int_obj->edge){EXT_INT2_RisingEdgSet();}
                else if(INTERRUPT_FALLING_EDGE==int_obj->edge){EXT_INT2_FallingEdgSet();}
                else{/**/}
                RET=E_OK; 
                break;
            default : RET=E_NOK; 
}
    
}
    return RET;
}
static std_returntype INTERRUPT_INTx_PIN_init(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
       gpio_pin_direction_intialize(&(int_obj->mcu_pin)); 
}
    return RET;
}
static std_returntype INTERRUPT_RBx_ENABLE(const interrupt_RBx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
    }
    return RET;
}
static std_returntype INTERRUPT_RBx_DISABLE(const interrupt_RBx_t *int_obj){
   std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
    }
    return RET; 
}
static std_returntype INTERRUPT_RBx_Priority_init(const interrupt_RBx_t *int_obj){
   std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
    }
    return RET; 
}
    
static std_returntype INTERRUPT_RBx_PIN_init(const interrupt_RBx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        
    }
    return RET;
}
static std_returntype INTERRUPT_INTx_Clearflag(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
         switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_INTERRUPTFLAGCLEAR();
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_INTERRUPTFLAGCLEAR();
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_INTERRUPTFLAGCLEAR();
                RET=E_OK; 
                break;
            default : RET=E_NOK;
    }
    
}
    return RET;
}

static std_returntype INTERRUPT_INTx_SetinterruptHandler(const interrupt_INTx_t *int_obj){
    std_returntype RET=E_OK;
    if(NULL == int_obj){
       RET=E_NOK; 
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                RET=INT0_SetinterruptHandler(int_obj->EXTI_InterruptHandler);
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                RET=INT1_SetinterruptHandler(int_obj->EXTI_InterruptHandler);
                RET=E_OK; 
                break;
            case INTERRUPT_EXTERNAL_INT2 : 
                RET=INT2_SetinterruptHandler(int_obj->EXTI_InterruptHandler);
                RET=E_OK;
                break;
            default : RET=E_NOK;
    }
    
}
    return RET;
}
static std_returntype INT0_SetinterruptHandler( void *interruptHandler){
    std_returntype RET=E_OK;
    if(NULL ==interruptHandler ){
       RET=E_NOK; 
    }
    else{
       INT0_interruptHandler=interruptHandler;
       RET=E_OK;
    }
    return RET;
}
static std_returntype INT1_SetinterruptHandler( void *interruptHandler){
    std_returntype RET=E_OK;
    if(NULL == interruptHandler){
       RET=E_NOK; 
    }
    else{
        INT1_interruptHandler=interruptHandler;
       RET=E_OK; 
    }
    return RET;
}
    
static std_returntype INT2_SetinterruptHandler( void *interruptHandler){
    std_returntype RET=E_OK;
    if(NULL == interruptHandler){
       RET=E_NOK; 
    }
    else{
         INT2_interruptHandler=interruptHandler;
       RET=E_OK;
    }
    return RET;
}