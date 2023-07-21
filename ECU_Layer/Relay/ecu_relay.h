/* 
 * File:   ecu_relay.h
 * Author: Rabeh Mohamed
 *
 * Created on July 22, 2023, 12:20 AM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*---------Includes-----------*/
#include "ecu_relay_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*---------Macros Declarations----------*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U
/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/
typedef struct {
    uint8 relay_port : 4;
    uint8 relay_pin :3;
    uint8 relay_status : 1;
}relay_t;
/*--------Function Declarations*/
std_ReturnType relay_initialize(const relay_t *relay);
std_ReturnType relay_turn_on(const relay_t *relay);
std_ReturnType relay_turn_off(const relay_t *relay);
std_ReturnType relay_toggle(const relay_t *relay);


#endif	/* ECU_RELAY_H */

