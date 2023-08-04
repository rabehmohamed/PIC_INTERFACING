/* 
 * File:   mcal_eeprom.c
 * Author: Rabeh Mohamed
 *
 * Created on August 4, 2023, 12:27 AM
 */

#include "mcal_eeprom.h"

std_ReturnType Data_EEPROM_WriteByte (uint8 address , uint8 data){
    std_ReturnType ret = E_OK;
    /*Read Interrupt Status */
    uint8 interrupt_status = INTCONbits.GIE;
    /*Update Address Registers : 10 bits */
    EEADRH = (uint8)((address >> 8) & 0x03);
    EEADR = (uint8) (address & 0xFF);
    /*Update Data Register*/
    EEDATA = data;
    /*Select Data EEPROM Memory*/
    EECON1bits.EEPGD = ACCESS_EPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EPROM_PROGRAM_MEMORY;
    /*Allow write cycle*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLE;
    /*Disable Interrupt*/
    INTERRUPT_GlobalInterruptEnable();
    /*Write sequence */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*Initiate data EEPROM write*/
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /*Wait till it's complete*/
    while(EECON1bits.WR);
    /*Disable write cycle*/
    EECON1bits.WREN = 0;
    /*Enable Interrupt*/
    INTERRUPT_GlobalInterruptDisable();

    return ret;
    
}
std_ReturnType Data_EEPROM_ReadByte (uint8 address , uint8 *data){
    std_ReturnType ret = E_OK;
    if(data == NULL){
        ret = E_NOT_OK;
    }
    /*Update Address registers*/
    EEADRH = (uint8)((address >> 8) & 0x03);
    EEADR = (uint8) (address & 0xFF);
    /*Select Data EEPROM Memory*/
    EECON1bits.EEPGD = ACCESS_EPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_EPROM_PROGRAM_MEMORY;
    /*Allow Read bit*/
    EECON1bits.RD = ALLOW_READ_DATA_EEPROM;
    NOP();
    NOP();
    /*Read data*/
    *data = EEDATA;
    
    return ret;
}