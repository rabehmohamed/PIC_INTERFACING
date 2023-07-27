/* 
 * File:   ecu_lcd.c
 * Author: Rabeh Mohamed
 *
 * Created on July 27, 2023, 1:20 AM
 */


#include "ecu_lcd.h"

static std_ReturnType lcd_send_4bits(const lcd_4bit_t * lcd , uint8 data_command );
static std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t * lcd);
static std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t * lcd);
static std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t * lcd , uint8 row , uint8 column);
static std_ReturnType lcd_4bit_set_cursor(const lcd_8bit_t * lcd , uint8 row , uint8 column);


/**
 * 
 * @param lcd
 * @return 
 */
std_ReturnType lcd_4bit_initialize(const lcd_4bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(uint8 pin = 0 ; pin < 4 ; pin++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[pin]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd,LCD_CLEAR_DISPLAY);
        ret = lcd_4bit_send_command(lcd,LCD_CURSOR_HOME);       
        ret = lcd_4bit_send_command(lcd,LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd,LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd , 0x80);

    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd , uint8 command){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
        ret = lcd_send_4bits(lcd , (command >> 4));
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd , command);
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_4bit_send_char_data(const lcd_4bit_t *lcd , uint8 data){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);
        ret = lcd_send_4bits(lcd , (data >> 4));
        ret = lcd_4bit_send_enable(lcd);
        ret = lcd_send_4bits(lcd , data);
        ret = lcd_4bit_send_enable(lcd);
    }
    return ret;
}


std_ReturnType lcd_4bit_send_data_pos(const lcd_4bit_t *lcd ,uint8 row , uint8 column, uint8 data){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        ret = lcd_4bit_send_char_data(lcd , data);
    }
    return ret;
}


std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd ,uint8 *str){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++);
        }
        
    }
    return ret;
}


std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd ,uint8 *str , uint8 row , uint8 column){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_4bit_set_cursor(lcd , row , column);
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++);
        }
        
    }
    return ret;
}


std_ReturnType lcd_4bit_send_cutsom_char(const lcd_4bit_t *lcd , const uint8 _chr[] , uint8 row , uint8 column , uint8 mem_pos);
/***
 */
std_ReturnType lcd_8bit_initialize(const lcd_8bit_t *lcd){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(uint8 pin = 0 ; pin < 8 ; pin++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[pin]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd,LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd,LCD_CLEAR_DISPLAY);
        ret = lcd_8bit_send_command(lcd,LCD_CURSOR_HOME);       
        ret = lcd_8bit_send_command(lcd,LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd,LCD_CURSOR_OFF_DISPLAY_ON);
        
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd , uint8 command){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW);
        for(uint8 pin = 0 ; pin < 8 ; pin++){
            ret = gpio_pin_write_logic(&lcd->lcd_data[pin] , (command >> pin) & 0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_char_data(const lcd_8bit_t *lcd , uint8 data){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH);     
        for(uint8 pin = 0 ; pin < 8 ; pin++){
            ret = gpio_pin_write_logic(&lcd->lcd_data[pin] , (data >> pin) & 0x01);
        }
        ret = lcd_8bit_send_enable(lcd);
        
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
std_ReturnType lcd_8bit_send_data_pos(const lcd_8bit_t *lcd ,uint8 row , uint8 column, uint8 data){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
         ret = E_NOT_OK;
    }
    else {
        ret = lcd_8bit_set_cursor(lcd , row , column);
        ret = lcd_8bit_send_char_data(lcd , data);
        ret = lcd_8bit_send_enable(lcd);
    }
    return ret;
    
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd ,uint8 *str){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++);
        }
        
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param column
 * @return 
 */
std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd , uint8 row , uint8 column , uint8 *str ){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = lcd_8bit_set_cursor(lcd , row , column);
         while(*str){
            ret = lcd_8bit_send_char_data(lcd , *str++);
        }
        
    }
    return ret;
}


std_ReturnType lcd_8bit_send_cutsom_char(const lcd_8bit_t *lcd , const uint8 _chr[] , uint8 row , uint8 column , uint8 mem_pos){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else 
    {
        ret = lcd_8bit_send_command(lcd , (CGRAM_START+(mem_pos*8)));
        for(uint8 i = 0 ; i<8 ; i++){
            ret = lcd_8bit_send_char_data(lcd , _chr[i]);
        }
        ret = lcd_8bit_send_data_pos(lcd , row , column , mem_pos);
        
    }
    return ret;
}

static std_ReturnType lcd_send_4bits(const lcd_4bit_t * lcd , uint8 data_command ){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]) , (data_command >> 0) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]) , (data_command >> 1) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]) , (data_command >> 2) & (uint8)0x01 );
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]) , (data_command >> 3) & (uint8)0x01 );
    }
    return ret;
}

std_ReturnType convert_uint8_to_string(uint8 value , uint8 *str){
    std_ReturnType ret = E_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = memset(str , '/0' , 4); // 2^8 = 256 , 3 chars and null termination
        ret = sprintf(str , "%i" , value);
    }
    return ret;
}



std_ReturnType convert_uint16_to_string(uint16 value , uint8 *str){
     std_ReturnType ret = E_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = memset(str , '/0' , 6); // 2^16 = 65536 , 5 chars and null termination
        ret = sprintf(str , "%i" , value);
    }
    return ret;
}

std_ReturnType convert_uint32_to_string(uint32 value , uint8 *str){
    std_ReturnType ret = E_OK;
    if(str == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = memset(str , '/0' , 11);
        ret = sprintf(str , "%i" , value);
    }
    return ret;
}

static std_ReturnType lcd_4bit_send_enable(const lcd_4bit_t * lcd){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    }
    return ret;
}

static std_ReturnType lcd_8bit_send_enable(const lcd_8bit_t * lcd){
    std_ReturnType ret = E_OK;
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en) , GPIO_LOW);
    }
    return ret;
}

static std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t * lcd , uint8 row , uint8 column){
    std_ReturnType ret = E_OK;
    column--; // because is starts from 0
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    switch(row){
        case ROW1 : ret = lcd_8bit_send_command(lcd , (0x80 + column));
        break;
        case ROW2 : ret = lcd_8bit_send_command(lcd , (0xC0 + column));
        break;
        case ROW3 : ret = lcd_8bit_send_command(lcd , (0x94 + column));
        break;
        case ROW4 : ret = lcd_8bit_send_command(lcd , (0xD4 + column));
        break;
        default : ;
        
    }
    return ret;
}


static std_ReturnType lcd_4bit_set_cursor(const lcd_8bit_t * lcd , uint8 row , uint8 column){
    std_ReturnType ret = E_OK;
    column--; // because is starts from 0
    if(lcd == NULL){
        ret = E_NOT_OK;
    }
    switch(row){
        case ROW1 : ret = lcd_4bit_send_command(lcd , (0x80 + column));
        break;
        case ROW2 : ret = lcd_4bit_send_command(lcd , (0xC0 + column));
        break;
        case ROW3 : ret = lcd_4bit_send_command(lcd , (0x94 + column));
        break;
        case ROW4 : ret = lcd_4bit_send_command(lcd , (0xD4 + column));
        break;
        default : ;
        
    }
    return ret;
}