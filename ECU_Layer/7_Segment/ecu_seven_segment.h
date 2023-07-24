/* 
 * File:   ecu_seven_segment.h
 * Author: Rabeh Mohamed
 *
 * Created on July 24, 2023, 1:27 AM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/*----------INCLUDES--------------*/
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_seven_segment_config.h"

/*----------MACRO DECLARTATIONS----------*/

/*----------MACRO FUNCTION DECLARTIONS-------------*/

/*----------DATA TYPE DECLARTIONS------------------*/
typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,     
}segment_type_t;

typedef struct {
    pin_config_t segment_pins[4]; // DECODER PINS
    segment_type_t segment_type;
}segment_t;
/*----------FUNCTION DECLARTIONS-------------------*/
std_ReturnType seven_segment_initialize(const segment_t * seg);
std_ReturnType seven_segment_write_number(const segment_t * seg , uint8 number);

#endif	/* ECU_SEVEN_SEGMENT_H */

