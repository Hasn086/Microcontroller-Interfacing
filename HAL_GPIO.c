#include "HAL_GPIOI.h"
/* */
 volatile uint8 *tris_register[]={&TRISA ,&TRISB,&TRISC,&TRISD,&TRISE};
 volatile uint8 *lat_register[]={&LATA,&LATB,&LATC,&LATD,&LATE};
 volatile uint8 *port_register[]={&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
 std_returntype RET ;
#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_direction_intialize(const pin_config_t *_pin_config){
std_returntype RET = E_OK;
if(NULL==_pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET=E_OK;
}else{
switch(_pin_config->direction){
    case OUTPUT:
        clear_bit(*tris_register[_pin_config->port],_pin_config->pin);
        break;
    case INPUT:
        set_bit(*tris_register[_pin_config->port],_pin_config->pin);
        break;
    default :RET=E_NOK;
}
}
return RET;
}
#endif
#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_direction_statuse(const pin_config_t *_pin_config,direction_t *dir_statuse){
std_returntype RET = E_OK;
if(NULL==_pin_config||NULL==dir_statuse|| _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET= E_NOK;
}else{
*dir_statuse=RED_Bit(*tris_register[_pin_config->port],_pin_config->pin);
}
return RET;
}
#endif
#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_write_logic(const pin_config_t *_pin_config,logic_t logic){
std_returntype RET = E_OK;
if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET= E_NOK;
}else{
    switch(logic){
        case LOW:
            clear_bit(*lat_register[_pin_config->port],_pin_config->pin);
            break;
        case HIGH:
            set_bit(*lat_register[_pin_config->port],_pin_config->pin);
            break;
        default : RET = E_NOK;    
    }
}
return RET;

}
#endif

#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_read_logic(const pin_config_t *_pin_config,logic_t *logic){
std_returntype RET = E_OK;
if(NULL==_pin_config||NULL==logic||_pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET= E_NOK;
}else{
*logic=RED_Bit(*port_register[_pin_config->port],_pin_config->pin);
}
return RET;

}
#endif
#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_toggle_logic(const pin_config_t *_pin_config){
std_returntype RET = E_OK;
if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET= E_NOK;
}else{
toggle_bit(*lat_register[_pin_config->port],_pin_config->pin);
}
return RET;
}
#endif
#if GPIO_pin_configrations == CONFIG_ENABLE
std_returntype  gpio_pin_intialize(const pin_config_t *_pin_config){
std_returntype RET = E_OK;
if(NULL==_pin_config||_pin_config->pin > PORT_PIN_MAX_NUMBER-1){
    RET= E_NOK;
}else{
RET=gpio_pin_direction_intialize(_pin_config);
RET=gpio_pin_write_logic(_pin_config,_pin_config->logic);
}
return RET;

}
#endif
#if GPIO_PORT_configrations == CONFIG_ENABLE
std_returntype  gpio_port_direction_intialize(PORT_index_t port,uint8 dir_statuse){
std_returntype RET = E_OK;
if(port>PORT_MAX_NUMBER-1){
    RET=E_NOK;
}
else{
    dir_statuse=(*tris_register[port]);
}
return RET;

}
#endif
#if GPIO_PORT_configrations == CONFIG_ENABLE
std_returntype  gpio_port_get_direction_statuse(PORT_index_t port,uint8 *dir_statuse){
std_returntype RET = E_OK;
if(NULL==dir_statuse||port>PORT_MAX_NUMBER-1){
    RET= E_NOK;
}else{
    *dir_statuse=*tris_register[port];
}
return RET;

}
#endif

#if GPIO_PORT_configrations == CONFIG_ENABLE
std_returntype  gpio_port_write_logic(PORT_index_t port,uint8 logic){
std_returntype RET = E_OK;
if(port>PORT_MAX_NUMBER-1){
    RET=E_NOK;
}
else{
    *lat_register[port]=logic;
}
return RET;
}
#endif
#if GPIO_PORT_configrations == CONFIG_ENABLE
std_returntype  gpio_port_read_logic(PORT_index_t port,uint8 *logic){
if(NULL==logic||port>PORT_MAX_NUMBER-1){
    RET= E_NOK;
}else{
    *logic=*lat_register[port];
}
return RET;
}
#endif
#if GPIO_PORT_configrations == CONFIG_ENABLE
std_returntype  gpio_port_toggle_logic(PORT_index_t port){
std_returntype RET = E_OK;
if(port>PORT_MAX_NUMBER-1){
    RET=E_NOK;
}
else{
    *lat_register[port] ^= PORT_MASK;
}
return RET;


}
#endif