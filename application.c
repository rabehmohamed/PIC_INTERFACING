/* 
 * File:   application.c
 * Author: Rabeh Mohamed
 *
 * Created on July 16, 2023, 8:30 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000

#include "application.h"

void application_initialize(void);

pin_config_t segment1_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

pin_config_t segment2_enable = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

segment_t seg1 ={
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0 ,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1 ,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2 ,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3 ,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    
    .segment_type = SEGMENT_COMMON_ANODE 
};


 std_ReturnType ret = E_NOT_OK; 
 uint8 number = 0;
int main() {
    
    application_initialize();
    
    while(1){
         // 23 
        for(int number=0 ; number<=50 ; number++){
            ret = seven_segment_write_number (&seg1 , (uint8)number%10 );
            ret = gpio_pin_write_logic(&segment2_enable , GPIO_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&segment2_enable , GPIO_LOW);

            ret = seven_segment_write_number (&seg1 , (uint8)number/10 );
            ret = gpio_pin_write_logic(&segment1_enable , GPIO_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&segment1_enable , GPIO_LOW);
        }
        number++;   
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret = gpio_pin_initialize(&segment1_enable);
    ret = gpio_pin_initialize(&segment2_enable);
    ret = seven_segment_initialize(&seg1);
    
}