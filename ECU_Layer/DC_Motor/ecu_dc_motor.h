/* 
 * File:   ecu_dc_motor.h
 * Author: LENOVO
 *
 * Created on July 22, 2023, 2:44 AM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*---------Includes-----------*/
#include "ecu_dc_motor_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*---------Macros Declarations----------*/
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U 
/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/
typedef struct {
    pin_config_t dc_motor[2];
}dc_motor_t;
/*--------Function Declarations*/
std_ReturnType dc_motor_initialize(const dc_motor_t * motor);
std_ReturnType dc_motor_move_right(const dc_motor_t * motor);
std_ReturnType dc_motor_move_left(const dc_motor_t * motor);
std_ReturnType dc_motor_stop(const dc_motor_t * motor);



#endif	/* ECU_DC_MOTOR_H */

