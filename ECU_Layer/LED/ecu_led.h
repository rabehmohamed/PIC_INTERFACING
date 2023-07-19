/* 
 * File:   ecu_led.h
 * Author: Rabeh Mohamed
 *
 * Created on July 16, 2023, 8:44 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*---------Includes-----------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_config.h"
/*---------Macros Declarations----------*/
#define LED_CONFIG ECU_LED_ENABLE
/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/
typedef enum{
    LED_OFF,
    LED_ON
}LED_STATUS;

typedef struct{
    uint8 port : 4;
    uint8 pin : 3;
    uint8 led_status;
}led_t;
/*--------Function Declarations*/
std_ReturnType led_initialize(const led_t *led);
std_ReturnType led_turn_on(const led_t *led);
std_ReturnType led_turn_off(const led_t *led);
std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

