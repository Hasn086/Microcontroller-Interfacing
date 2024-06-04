/* 
 * File:   ECU_EEPROM.h
 * Author: HASAN  ISMAIL 
 *
 * Created on 01 ????, 2024, 03:09 ?
 */

#ifndef ECU_EEPROM_H
#define	ECU_EEPROM_H
/*section : includes*/
#include "../mcal_std_types.h"
#include "pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"
/*section : macro declarations */
#define Access_Flash_program_memory 1
#define Access_data_EEPROM_memory  0
#define  Access_Configuration_registers  1  
#define Access_Flashprogram_data_EEPROM_memory  0
#define Allows_write_cycles_to_Flashprogram_data_EEPROM  1
#define Inhibits_write_cycles_to_Flashprogram_data_EEPROM 0
#define INHIBTS_WRITE_CYCLES_FLASH_EEPROM 0
/*section  : macro functions declaretions */

/*section : data type declaration */

/*section  :  functions declaretions */
std_returntype Data_EEPROM_WriteByte(uint16 bAdd,uint8 data);
std_returntype Data_EEPROM_ReadByte(uint16 bAdd,uint8 *data);

#endif	/* ECU_EEPROM_H */

