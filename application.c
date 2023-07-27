/* 
 * File:   application.c
 * Author: Rabeh Mohamed
 *
 * Created on July 16, 2023, 8:30 PM
 */

#include <stdio.h>
#include <stdlib.h>


#include "application.h"


std_ReturnType ret = E_NOT_OK; 
void application_initialize(void);


lcd_4bit_t lcd1_4 ={
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOW,
  
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOW,
  
  .lcd_data[0].port = PORTC_INDEX,
  .lcd_data[0].pin = GPIO_PIN2,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW, 
  .lcd_data[1].port = PORTC_INDEX,
  .lcd_data[1].pin = GPIO_PIN3,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW, 
  .lcd_data[2].port = PORTC_INDEX,
  .lcd_data[2].pin = GPIO_PIN4,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTC_INDEX,
  .lcd_data[3].pin = GPIO_PIN5,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW,
};

lcd_8bit_t lcd2_8 ={
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN6,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOW,
  
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN7,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOW,
  
  .lcd_data[0].port = PORTD_INDEX,
  .lcd_data[0].pin = GPIO_PIN0,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOW, 
  .lcd_data[1].port = PORTD_INDEX,
  .lcd_data[1].pin = GPIO_PIN1,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOW, 
  .lcd_data[2].port = PORTD_INDEX,
  .lcd_data[2].pin = GPIO_PIN2,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOW,
  .lcd_data[3].port = PORTD_INDEX,
  .lcd_data[3].pin = GPIO_PIN3,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOW,
  .lcd_data[4].port = PORTD_INDEX,
  .lcd_data[4].pin = GPIO_PIN4,
  .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[4].logic = GPIO_LOW,
  .lcd_data[5].port = PORTD_INDEX,
  .lcd_data[5].pin = GPIO_PIN5,
  .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[5].logic = GPIO_LOW,
  .lcd_data[6].port = PORTD_INDEX,
  .lcd_data[6].pin = GPIO_PIN6,
  .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[6].logic = GPIO_LOW,
  .lcd_data[7].port = PORTD_INDEX,
  .lcd_data[7].pin = GPIO_PIN7,
  .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[7].logic = GPIO_LOW,
};
uint8 number = 23;
uint8 number_txt[3];

const uint8 customChar1[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};

const uint8 customChar2[]  = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x00
};

const uint8 customChar3[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x1F,
  0x1F,
  0x1F,
  0x00
};


int main() {
     
    application_initialize();
    ret = lcd_8bit_send_string(&lcd2_8 , "RabehMohamed");
    
    ret = convert_uint8_to_string(number , number_txt);
    ret = lcd_8bit_send_string(&lcd2_8 , number_txt);
    
    
    
    while(1){
        ret = lcd_8bit_send_cutsom_char(&lcd2_8 ,customChar1 , 1 , 12 , 0 );
        ret = lcd_8bit_send_cutsom_char(&lcd2_8 ,customChar2 , 1 , 12 , 0 );
        ret = lcd_8bit_send_cutsom_char(&lcd2_8 ,customChar3 , 1 , 12 , 0 );
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    
    ret = lcd_8bit_initialize(&lcd2_8);
}