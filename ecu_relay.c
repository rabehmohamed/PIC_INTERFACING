/* 
 * File:   ecu_relay.c
 * Author: Rabeh Mohamed
 *
 * Created on July 22, 2023, 12:21 AM
 */

#include "ECU_Layer/Relay/ecu_relay.h"

/**
 * 
 * @param relay
 * @return 
 */
std_ReturnType relay_initialize(const relay_t *relay){
    std_ReturnType ret = E_OK;
    
    
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else{
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status};
        ret = gpio_pin_initialize(&pin_obj);
    }
    return ret;
}

std_ReturnType relay_turn_on(const relay_t *relay){
     std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj , GPIO_HIGH);
    }
    return ret;
}

std_ReturnType relay_turn_off(const relay_t *relay){
    std_ReturnType ret = E_OK;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status};
        ret = gpio_pin_write_logic(&pin_obj , GPIO_LOW);
    }
    return ret;
}

std_ReturnType relay_toggle(const relay_t *relay){
    std_ReturnType ret = E_OK;;
    if(relay == NULL){
        ret = E_NOT_OK;
    }
    else {
        pin_config_t pin_obj = {.port = relay->relay_port , .pin = relay->relay_pin , .direction = GPIO_DIRECTION_OUTPUT , .logic = relay->relay_status};
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;
}
