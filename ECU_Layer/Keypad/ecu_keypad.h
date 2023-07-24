/* 
 * File:   ecu_keypad.h
 * Author: Rabeh Mohamed
 *
 * Created on July 24, 2023, 11:41 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*---------Includes-----------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_keypad_config.h"
/*---------Macros Declarations----------*/
#define ECU_KEYPAD_ROWS 4
#define ECU_KEYPAD_COLUMNS 4
/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/
typedef struct{
    pin_config_t keypad_rows_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;
/*--------Function Declarations*/
std_ReturnType keypad_initialize(const keypad_t * keypad);
std_ReturnType keypad_get_value(const keypad_t * keypad , uint8 * value);



#ifdef	__cplusplus
}
#endif

#endif	/* ECU_KEYPAD_H */

