/* 
 * File:   ECU_EEPROM.h
 * Author: HASAN  ISMAIL 
 *
 * Created on 01 ????, 2024, 03:09 ?
 */
#include "ECU_EEPROM.h"


/**
 * @Summary Writes a data byte to Data EEPROM
 * @Description This routine writes a data byte to given Data EEPROM location
 * @Preconditions None
 * @param bAdd - Data EEPROM location to which data to be written
 * @param bData - Data to be written to Data EEPROM location
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 * @Example ret = Data_EEPROM_WriteByte(0x3ff, 0);
 */
std_returntype Data_EEPROM_WriteByte(uint16 bAdd,uint8 data){
    std_returntype RET=E_OK;
    /* Read the Interrupt Status "Enabled or Disabled" */
    uint8 Global_interrupt_statuse= INTCONbits.GIE;
    /* Update the Address Registers */
    EEADRH=(uint8)((bAdd >> 8)& 0x03);
    EEADR=(uint8)(bAdd & 0xFF);
    /* Update the Data Register */
    EEDATA= data;       
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD= Access_data_EEPROM_memory;
    EECON1bits.CFGS= Access_Flashprogram_data_EEPROM_memory ;
    /* Allows write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = Allows_write_cycles_to_Flashprogram_data_EEPROM;
    /* Disable all interrupts "General Interrupt" */
    INTERRUPT_GlobalInterruptDisable();
    /* Write the required sequence : 0x55 -> 0xAA */
    EECON2=0x55;
    EECON2=0xAA;
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR=INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
    /* Wait for write to complete */
    while(EECON1bits.WR){
        /* Inhibits write cycles to Flash program/data EEPROM */
         EECON1bits.WREN= INHIBTS_WRITE_CYCLES_FLASH_EEPROM;
         /* Restore the Interrupt Status "Enabled or Disabled" */
         INTCONbits.GIE = Global_interrupt_statuse ;
    }
    return RET;
}
std_returntype Data_EEPROM_ReadByte(uint16 bAdd,uint8 *data){
     std_returntype RET=E_OK;
     if(NULL==data){
         RET=E_NOK;
     }
     else{
         RET=E_OK;
     } 
    return RET;
    
}