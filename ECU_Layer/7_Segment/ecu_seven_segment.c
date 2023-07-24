
/* 
 * File:   ecu_seven_segment_config.h
 * Author: Rabeh Mohamed
 *
 * Created on July 24, 2023, 1:29 AM
 */

#include "ecu_seven_segment.h"

/**
 * 
 * @param seg
 * @return 
 */
std_ReturnType seven_segment_initialize(const segment_t * seg){
    std_ReturnType ret = E_OK;
    if(seg == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_initialize(&(seg->segment_pins[0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[3]));
    }
    
    return ret;
}


std_ReturnType seven_segment_write_number(const segment_t * seg , uint8 number){
    std_ReturnType ret = E_OK;
    if((seg == NULL) &&(number > 9) ){
        ret = E_NOT_OK;
    }
    else {
       ret =  gpio_pin_write_logic(&(seg->segment_pins[0]) , number&0x01);
       ret =  gpio_pin_write_logic(&(seg->segment_pins[1]) , (number>>1) & 0x01);
       ret =  gpio_pin_write_logic(&(seg->segment_pins[2]) , (number>>2) & 0x01);
       ret =  gpio_pin_write_logic(&(seg->segment_pins[3]) , (number>>3) & 0x01);
    }
    
    return ret; 
}