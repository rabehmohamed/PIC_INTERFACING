/* 
 * File:   button_button.h
 * Author: Rabeh Mohamed
 *
 * Created on July 19, 2023, 8:33 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*-------Includes-------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

#include "ecu_button_config.h"


/*------Macros Declarations-----------*/

/*------Macros Functions Declarations-----------*/

/*------Data Type Declarations-----------*/
typedef enum{
    BUTTON_PRESSED = 0,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_CONNECTION_HIGH ,
    BUTTON_CONNECTION_LOW
}button_connection_t;

typedef struct {
    pin_config_t button_pin;
    button_state_t button_state;
    button_connection_t  button_connection;
}button_t;

/*------Functions Declarations-----------*/
std_ReturnType button_initialize(const button_t * btn );
std_ReturnType button_read_state(const button_t * btn , button_state_t * btn_state );

#endif	/* ECU_BUTTON_H */

