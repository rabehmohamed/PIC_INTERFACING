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

button_t btn1 = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_connection = BUTTON_CONNECTION_HIGH,
    .button_state = BUTTON_RELEASED
};

relay_t relay1 ={
    .relay_port = PORTC_INDEX,
    .relay_pin = GPIO_PIN0,
    .relay_status = RELAY_OFF_STATUS
};

std_ReturnType ret = E_NOT_OK;


int main() {
    

    ret = relay_initialize(&relay1);

    while(1){
        ret = relay_turn_on(&relay1);
        __delay_ms(5000);
        ret = relay_turn_off(&relay1);
        __delay_ms(5000);
    }
    return (EXIT_SUCCESS);
}
