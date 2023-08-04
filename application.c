/* 
 * File:   application.c
 * Author: Rabeh Mohamed
 *
 * Created on July 16, 2023, 8:30 PM
 */

#include <stdio.h>
#include <stdlib.h>


#include "application.h"

void Int_ISR(void);

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



interrupt_INTx_t intter1 = {
  .INTERRUPT_HANDLER = Int_ISR,
  .edge = INTERRUPT_RAISING_EDGE,
  .priority = INTERRUPT_HIGH_PRIORITY,
  .source = INTERRUPT_int0,
  .pin.direction = GPIO_DIRECTION_INPUT,
  .pin.logic = GPIO_LOW ,
  .pin.port = PORTB_INDEX,
  .pin.pin = GPIO_PIN0
          
};

void program1 (void){
   led_turn_on(&led1);
   __delay_ms(250);
   led_turn_on(&led1);
   __delay_ms(250);
}

void program2 (void){
   led_turn_on(&led2);
   __delay_ms(250);
   led_turn_on(&led2);
   __delay_ms(250);
}

volatile uint8 program_select =0;
uint8 eeprom_data = 0;
uint32 eeprom_value = 0;

void Int_ISR(void){
        program_select++;
        if(program_select == 3){
            program_select = 0 ;
        }
        Data_EEPROM_WriteByte(0x3FF ,program_select );
    };
    
int main() {
    
   //ret = Data_EEPROM_WriteByte(0x3FF , 0);
    ret = interrupt_INTx_init(&intter1);
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ;
    ret = Data_EEPROM_ReadByte(0x3FF , &program_select);
    
    
    while(1){
        
        
        if(program_select == 1){
            program1();
        }
        else if(program_select == 2){
            program2();
            
        }
        else {
            
            led_turn_off(&led1);
            led_turn_off(&led2);
        }
       
        
        
    }
    return (EXIT_SUCCESS);
}
void application_initialize(void){
    
}
