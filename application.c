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



dc_motor_t dc_motor_1 = {
  .dc_motor[0].port = PORTC_INDEX,
  .dc_motor[0].pin = GPIO_PIN0,
  .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
  
  .dc_motor[1].port = PORTC_INDEX,
  .dc_motor[1].pin = GPIO_PIN1,
  .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
};

dc_motor_t dc_motor_2 = {
  .dc_motor[0].port = PORTC_INDEX,
  .dc_motor[0].pin = GPIO_PIN2,
  .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
  
  .dc_motor[1].port = PORTC_INDEX,
  .dc_motor[1].pin = GPIO_PIN3,
  .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
  .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
};

std_ReturnType ret = E_NOT_OK;

void application_initialize(void);
int main() {
    
    application_initialize();
    
    
    while(1){
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_right(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_left(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_stop(&dc_motor_1);
        ret = dc_motor_stop(&dc_motor_2);
        __delay_ms(3000);
        ret = dc_motor_move_right(&dc_motor_1);
        ret = dc_motor_move_left(&dc_motor_2);
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    ret = dc_motor_initialize(&dc_motor_1);
    ret = dc_motor_initialize(&dc_motor_2);
}