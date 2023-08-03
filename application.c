/* 
 * File:   application.c
 * Author: Rabeh Mohamed
 *
 * Created on July 16, 2023, 8:30 PM
 */

#include <stdio.h>
#include <stdlib.h>


#include "application.h"



void application_initialize(void);
std_ReturnType ret = E_NOT_OK; 

led_t led1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};
led_t led2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};


void RB4_APP_ISR_HIGH(void){
    led_turn_on(&led1);
    
}
void RB4_APP_ISR_LOW(void){
    led_turn_off(&led1);
}

void RB5_APP_ISR_HIGH(void){
    led_turn_on(&led2);
    
}
void RB5_APP_ISR_LOW(void){
    led_turn_off(&led2);
}



interrupt_RBx_t obj_rb4 = {
    .INTERRUPT_HANDLER_HIGH =RB4_APP_ISR_HIGH,
    .INTERRUPT_HANDLER_LOW = RB4_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .pin.port = PORTB_INDEX,
    .pin.pin = GPIO_PIN4,
    .pin.direction = GPIO_DIRECTION_INPUT,
};

interrupt_RBx_t obj_rb5 = {
    .INTERRUPT_HANDLER_HIGH =RB5_APP_ISR_HIGH,
    .INTERRUPT_HANDLER_LOW = RB5_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .pin.port = PORTB_INDEX,
    .pin.pin = GPIO_PIN5,
    .pin.direction = GPIO_DIRECTION_INPUT,
};

int main() {
    ret = interrupt_RBx_init(&obj_rb4); 
    ret = interrupt_RBx_init(&obj_rb5);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    
    
    application_initialize();
    
    
    
    
    while(1){
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    
}
