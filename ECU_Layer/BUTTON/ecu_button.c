
/* 
 * File:   ecu_button.c
 * Author: Rabeh Mohamed
 *
 * Created on July 19, 2023, 9:36 PM
 */

#include "ecu_button.h"


/**
 * 
 * @param btn
 * @return Status of function 
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : issue
 */
std_ReturnType button_initialize(const button_t * btn ){
    std_ReturnType ret = E_OK;
    if(btn == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_direction_initialize(&(btn->button_pin));
        
    }
    return ret;
}

/**
 * 
 * @param btn , btn_State
 * @return Status of function 
 *          (E_OK) : the function done successfully
 *          (E_NOT_OK) : issue
 */
std_ReturnType button_read_state(const button_t * btn , button_state_t * btn_state ){
    std_ReturnType ret = E_OK;
    logic_t pin_logic_status = GPIO_LOW; 
    
    if(btn == NULL || btn_state == NULL){
        ret = E_NOT_OK;
    }
    else {
        
        gpio_pin_read_logic(&(btn->button_pin) , &pin_logic_status);
        if(btn->button_connection == BUTTON_CONNECTION_HIGH){
            if(pin_logic_status == GPIO_HIGH){ 
                *btn_state = BUTTON_PRESSED;
            }
            else {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn->button_connection == BUTTON_CONNECTION_LOW){
            if(pin_logic_status == GPIO_HIGH){ 
                *btn_state = BUTTON_RELEASED;
            }
            else {
                *btn_state = BUTTON_PRESSED;  
            }
        }
        else {  
            
         
        ret = E_OK;
    }
    return ret;
}
}