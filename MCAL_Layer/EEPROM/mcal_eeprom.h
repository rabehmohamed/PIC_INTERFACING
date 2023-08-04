/* 
 * File:   mcal_eeprom.h
 * Author: Rabeh Mohamed
 *
 * Created on August 4, 2023, 12:25 AM
 */

#ifndef MCAL_EEPROM_H
#define	MCAL_EEPROM_H

/*---------Includes-----------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/*---------Macros Declarations----------*/
#define ACCESS_FLASH_PROGRAM_MEMORY      1
#define ACCESS_EPROM_PROGRAM_MEMORY      0
#define ACCESS_CONFIG_REGISTER           1
#define ALLOW_WRITE_CYCLE                1
#define INITIATE_DATA_EEPROM_WRITE_ERASE 1
#define ALLOW_READ_DATA_EEPROM           1

/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/
std_ReturnType Data_EEPROM_WriteByte (uint8 address , uint8 data);
std_ReturnType Data_EEPROM_ReadByte (uint8 address , uint8 *data);

#endif	/* MCAL_EEPROM_H */

