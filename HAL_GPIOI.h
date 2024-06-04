/* 
 * File:   HAL_GPIOI.h
 * Author: hasan ismail
 *
 *
 */

#ifndef HAL_GPIOI_H
#define	HAL_GPIOI_H

#include <xc.h>
/*section : includes*/
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "builtins.h"
#include "hal_gpio_cfg.h"

/*section : macro declarations */
# define bit_mask     (uint8)1
# define PORT_PIN_MAX_NUMBER   8
# define PORT_MAX_NUMBER   5
#define PORT_MASK         0xFF
/*section  : macro functions declaretions */
#define HWREG8(_x)       (*((volatile uint8_t *)(_x))
#define set_bit(REG_ADREES,Bit)    (REG_ADREES |= (1<<Bit))//set 1 by bit manipultion
#define clear_bit(REG_ADREES,Bit)  (REG_ADREES &= ~(1<<Bit))//clear 1 by bit manipultion
#define toggle_bit(REG_ADREES,Bit) (REG_ADREES ^= (1<<Bit))//toggle  1 by bit manipultion
#define RED_Bit(REG_ADREES,Bit)    ((REG_ADREES >> Bit) & bit_mask)
/*section : data type declaration */
typedef enum{
    LOW = 0,
    HIGH
}logic_t;
typedef enum{
    OUTPUT = 0,
    INPUT
}direction_t;
typedef enum{
    PIN0 = 0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7,
}PIN_index_t;
typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX,
}PORT_index_t;
typedef struct{
    uint8 port :3;       /* @ref PORT_index_t */
    uint8 pin :3;        /* @ref PIN_index_t */
    uint8 direction :1;  /* @ref direction_t */
    uint8 logic :1;      /* @ref logic_t*/
}pin_config_t;
/*section  :  functions declaretions */
std_returntype  gpio_pin_direction_intialize(const pin_config_t *_pin_config);
std_returntype  gpio_pin_direction_statuse(const pin_config_t *_pin_config,direction_t *dir_statuse);
std_returntype  gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic);
std_returntype  gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic);
std_returntype  gpio_pin_toggle_logic(const pin_config_t *_pin_config);
std_returntype  gpio_pin_intialize(const pin_config_t *_pin_config);

std_returntype  gpio_port_direction_intialize(PORT_index_t port,uint8 dir_statuse);
std_returntype  gpio_port_get_direction_statuse(PORT_index_t port,uint8 *dir_statuse);
std_returntype  gpio_port_write_logic(PORT_index_t port,uint8 logic);
std_returntype  gpio_port_read_logic(PORT_index_t port,uint8 *logic);
std_returntype  gpio_port_toggle_logic(PORT_index_t port); 

void application_intialize_1(void);


#endif //_HAL_GPIO_H

