/*#ifndef _BUILTINS_H_
#define _BUILTINS_H_

#include <stdint.h>

// builtin version of nop
#pragma intrinsic(__nop)
extern void __nop(void);

// builtin delay functions
#pragma intrinsic(_delay)
extern __nonreentrant void _delay(uint32_t);
#pragma intrinsic(_delaywdt)
extern __nonreentrant void _delaywdt(uint32_t);
#if defined(_PIC14E) || defined(_PIC14EX) || defined(_PIC18)
#pragma intrinsic(_delay3)
extern __nonreentrant void _delay3(uint8_t);
#endif

// NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
#define __delaywdt_us(x) _delaywdt((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#define __delaywdt_ms(x) _delaywdt((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

#endif // _BUILTINS_H_
*/




/* 
 * File:   GPIO.c
 * Author: hasan
 *
 * Created on 20 ??????, 2023, 07:23 ?
 */


#include "application.h"
#define _XTAL_FREQ 4000000
//#define HWREG(_x)       (*((volatile uint8_t *)(_x)))
/*#define hasan_LATC  (HWREG(0xF8B))
#define hasan_TRISC (HWREG(0xF94))
#define set_bit(REG_ADREES,Bit)    (REG_ADREES |= (1<<Bit))//set 1 by bit manipultion
#define clear_bit(REG_ADREES,Bit)  (REG_ADREES &= ~(1<<Bit))//clear 1 by bit manipultion*/
/*
 * 
 */
/*pin_config_t led_1 = {
.port = PORTC_INDEX,
.pin = PIN0,
.direction = OUTPUT,
.logic = HIGH
};
pin_config_t led_2 = {
.port = PORTC_INDEX,
.pin = PIN1,
.direction = OUTPUT,
.logic = HIGH
};
pin_config_t led_3 = {
.port = PORTC_INDEX,
.pin = PIN2,
.direction = OUTPUT,
.logic = HIGH
};
pin_config_t but_1 = {
.port = PORTD_INDEX,
.pin = PIN7,
.direction = INPUT,
.logic = LOW
};
    std_returntype ret=0;
    direction_t led_st;
    logic_t but_statuse;
    uint8 port_direction_statuse;
int main() {
    //hasan_TRISC =0x00;
    //ret= gpio_port_direction_intialize(PORTC_INDEX,0x55);
    application_initialize();
    while(1){
        
       ret= gpio_pin_toggle_logic(&led_1);
       ret= gpio_pin_toggle_logic(&led_2);
       __delay_ms(2000);
        ret=gpio_pin_read_logic(&but_1,&but_statuse);
        if(but_statuse == HIGH){
        ret=gpio_pin_write_logic(&led_1,HIGH);
        }else{
        
        ret=gpio_pin_write_logic(&led_1,LOW);
        
    
}
    return (EXIT_SUCCESS);
}}*/
/*hasan_LATC=0x00;
    uint8_t counter=0;
       uint8_t bit_shift=7;

   __delay_ms(1000);
   //hasan_LATC |= (_LATC_LATC0_MASK|_LATC_LATC7_MASK);
   for(counter=0;counter<=bit_shift;counter++){
   //hasan_LATC |=(1<<counter);
    //__delay_ms(1000);
   //}
   // hasan_LATC &= ~(_LATC_LATC0_MASK|_LATC_LATC7_MASK);
   set_bit(hasan_LATC,counter);
    __delay_ms(500);
    
    clear_bit(hasan_LATC,counter);
    __delay_ms(500);
   // hasan_LATC |= (_LATC_LATC1_MASK|_LATC_LATC6_MASK);//seting 1 by bit masks
    //__delay_ms(500);
   // hasan_LATC &= ~(_LATC_LATC1_MASK|_LATC_LATC6_MASK);
      //  __delay_ms(500);

   // hasan_LATC |= (_LATC_LATC2_MASK|_LATC_LATC5_MASK);
    //__delay_ms(2000);
    }*/
/*void application_initialize(void){
    //ret=gpio_pin_direction_intialize(&but_1);
    //ret=gpio_pin_direction_intialize(&led_1);
    //ret=gpio_pin_direction_intialize(&led_2);
   // ret=gpio_pin_direction_intialize(&led_3);
   ret= gpio_port_direction_intialize(PORTC_INDEX,0x55);
  ret= gpio_port_get_direction_statuse(PORTC_INDEX,&port_direction_statuse);
}*/