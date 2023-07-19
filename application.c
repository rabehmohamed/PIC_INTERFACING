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
led_t led1 ={
  .port = PORTC_INDEX,
  .pin = GPIO_PIN0,
  .led_status = LED_OFF
};

led_t led2 ={
  .port = PORTC_INDEX,
  .pin = GPIO_PIN1,
  .led_status = LED_OFF
};

int main() {
    
    application_initialize();
    while(1){
        led_turn_on(&led1);
        __delay_ms(500);
        led_turn_off(&led1);
        led_turn_on(&led2);
        __delay_ms(500);
        led_toggle(&led1);
        led_toggle(&led2);
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void){
    std_ReturnType ret = E_NOT_OK;
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
}