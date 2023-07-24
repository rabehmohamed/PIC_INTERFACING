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
#include "ECU_Layer/Keypad/ecu_keypad.h"

void application_initialize(void);



keypad_t keypad1 ={
  .keypad_rows_pins[0].port = PORTC_INDEX,
  .keypad_rows_pins[0].pin = GPIO_PIN0,
  .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_rows_pins[0].logic = GPIO_LOW,
  
  .keypad_rows_pins[1].port = PORTC_INDEX,
  .keypad_rows_pins[1].pin = GPIO_PIN1,
  .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_rows_pins[1].logic = GPIO_LOW,
  
  .keypad_rows_pins[2].port = PORTC_INDEX,
  .keypad_rows_pins[2].pin = GPIO_PIN2,
  .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_rows_pins[2].logic = GPIO_LOW,
  
  .keypad_rows_pins[3].port = PORTC_INDEX,
  .keypad_rows_pins[3].pin = GPIO_PIN3,
  .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
  .keypad_rows_pins[3].logic = GPIO_LOW,
  
  .keypad_columns_pins[0].port = PORTC_INDEX,
  .keypad_columns_pins[0].pin = GPIO_PIN4 , 
  .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[0].logic = GPIO_LOW,
  
  .keypad_columns_pins[1].port = PORTC_INDEX,
  .keypad_columns_pins[1].pin = GPIO_PIN5, 
  .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[1].logic = GPIO_LOW,
  
  .keypad_columns_pins[2].port = PORTC_INDEX,
  .keypad_columns_pins[2].pin = GPIO_PIN6, 
  .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[2].logic = GPIO_LOW,
  
  .keypad_columns_pins[3].port = PORTC_INDEX,
  .keypad_columns_pins[3].pin = GPIO_PIN7, 
  .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
  .keypad_columns_pins[3].logic = GPIO_LOW,
};

 std_ReturnType ret = E_NOT_OK; 
 uint8 keypad_value = 0;

int main() {
    ret = keypad_initialize(&keypad1);
    application_initialize();
    
    while(1){
        ret = keypad_get_value(&keypad1 , &keypad_value);
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    
}