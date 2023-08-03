/* 
 * File:   mcal_external_interrupt.c
 * Author: Rabeh Mohamed
 *
 * Created on August 1, 2023, 11:48 PM
 */
#include "mcal_external_interrupt.h"

static void (*INT0_InterruptHandler)(void) = NULL;
static void (*INT1_InterruptHandler)(void) = NULL;
static void (*INT2_InterruptHandler)(void) = NULL;

static void (*RB4_InterruptHandler_HIGH)(void) = NULL;
static void (*RB4_InterruptHandler_LOW)(void) = NULL;
static void (*RB5_InterruptHandler_HIGH)(void) = NULL;
static void (*RB5_InterruptHandler_LOW)(void) = NULL;
static void (*RB6_InterruptHandler_HIGH)(void) = NULL;
static void (*RB6_InterruptHandler_LOW)(void) = NULL;
static void (*RB7_InterruptHandler_HIGH)(void) = NULL;
static void (*RB7_InterruptHandler_LOW)(void) = NULL;


static std_ReturnType Interrupt_INTx_enable(const interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_disable(const interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_priority_init(const interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_edge_init(const interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_pin_init(const interrupt_INTx_t * int_obj);
static std_ReturnType Interrupt_INTx_clear_flag(const interrupt_INTx_t * int_obj);

static std_ReturnType INT0_setInterruptHandler(void (*InterruptHandler) (void));
static std_ReturnType INT1_setInterruptHandler(void (*InterruptHandler) (void));
static std_ReturnType INT2_setInterruptHandler(void (*InterruptHandler) (void));
static std_ReturnType Interrupt_INTX_setInterruptHandler(const interrupt_INTx_t * int_obj );


/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
       /*Disable Interrupt*/
        ret = Interrupt_INTx_disable(int_obj);
       /*Clear Interrupt Flag*/
        ret = Interrupt_INTx_clear_flag(int_obj);
        /*Configure Edge*/
        ret = Interrupt_INTx_edge_init(int_obj);
        /*Configure Priority*/
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        ret = Interrupt_INTx_priority_init(int_obj);
        #endif
        /*Configure I/O Ports*/
        ret = Interrupt_INTx_pin_init(int_obj);
        /*Configure Callback function*/
        ret = Interrupt_INTX_setInterruptHandler(int_obj);
       /*Enable Interrupt*/
        ret = Interrupt_INTx_enable(int_obj);
    }
    return ret;
}

void INT0_ISR(void){
    /*Clear Flag*/
    INT0_INTERRUPT_FLAG_CLEAR();
    /*Code*/
    
    /*Call back Function : contains function ISR */
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
    else {}
}

void INT1_ISR(void){
    /*Clear Flag*/
    INT1_INTERRUPT_FLAG_CLEAR();
    /*Code*/
    
    /*Call back Function : contains function ISR */
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void){
    /*Clear Flag*/
    INT2_INTERRUPT_FLAG_CLEAR();
    /*Code*/
    
    /*Call back Function : contains function ISR */
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}
/**
 * 
 * @param int_obj
 * @return 
 */
std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = Interrupt_INTx_disable(int_obj);
    }
    return ret;
}

// HELPER FUNCTIONS
static std_ReturnType Interrupt_INTx_enable(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source){
            case INTERRUPT_int0 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_GlobalInterruptHighPriorityEnable();
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                INT0_INTERRUPT_ENABLE();  
                ret = E_OK;
                break;
            case INTERRUPT_int1:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                        INTERRUPT_GlobalInterruptHighPriorityEnable();
                    }
                    else if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                        INTERRUPT_GlobalInterruptLowPriorityEnable();
                    }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                INT1_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){
                        INTERRUPT_GlobalInterruptHighPriorityEnable();
                    }
                    else if(int_obj->priority == INTERRUPT_LOW_PRIORITY){
                        INTERRUPT_GlobalInterruptLowPriorityEnable();
                    }
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                INT2_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
    return ret;
}

static std_ReturnType Interrupt_INTx_disable(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source){
            case INTERRUPT_int0 : 
                INT0_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case INTERRUPT_int1:
                INT1_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                INT2_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
    return ret;
}

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
static std_ReturnType Interrupt_INTx_priority_init(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
         switch(int_obj->source){
            case INTERRUPT_int1:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){INT1_INTERRUPT_LowPriorty();  }
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){INT1_INTERRUPT_HighPriorty();}
                else{}
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                if(int_obj->priority == INTERRUPT_LOW_PRIORITY){INT2_INTERRUPT_LowPriorty();}
                else if(int_obj->priority == INTERRUPT_HIGH_PRIORITY){INT2_INTERRUPT_HighPriorty();}
                else{}
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
    return ret;
}
#endif

static std_ReturnType Interrupt_INTx_edge_init(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->edge){
            case INTERRUPT_int0 : 
                if(int_obj->edge == INTERRUPT_RAISING_EDGE){INT0_INTERRUPT_RisingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_FALLING_EDGE){INT0_INTERRUPT_FallingEdgeSet(); }
                else{}
                ret = E_OK;
                break;
            case INTERRUPT_int1:
                if(int_obj->edge == INTERRUPT_RAISING_EDGE){INT1_INTERRUPT_RisingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_FALLING_EDGE){INT1_INTERRUPT_FallingEdgeSet(); }
                else{}
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                if(int_obj->edge == INTERRUPT_RAISING_EDGE){INT2_INTERRUPT_RisingEdgeSet();}
                else if(int_obj->edge == INTERRUPT_FALLING_EDGE){INT2_INTERRUPT_FallingEdgeSet(); }
                else{}
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
    return ret;
}

static std_ReturnType Interrupt_INTx_pin_init(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        ret = gpio_pin_direction_initialize(&(int_obj->pin));
    }
    return ret;
}

static std_ReturnType Interrupt_INTx_clear_flag(const interrupt_INTx_t * int_obj){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        switch(int_obj->source){
            case INTERRUPT_int0 : 
                INT0_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            case INTERRUPT_int1:
                INT1_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                INT2_INTERRUPT_FLAG_CLEAR();
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
    return ret;
}

static std_ReturnType INT0_setInterruptHandler(void (*InterruptHandler) (void)){
    std_ReturnType ret = E_NOT_OK;
    if(InterruptHandler == NULL){
        ret = E_NOT_OK;
    }
    else { 
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
     
    return ret;
}

static std_ReturnType INT1_setInterruptHandler(void (*InterruptHandler) (void)){
    std_ReturnType ret = E_NOT_OK;
    if(INT0_InterruptHandler == NULL){
        ret = E_NOT_OK;
    }
    else { 
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
     
    return ret;
}

static std_ReturnType INT2_setInterruptHandler(void (*InterruptHandler) (void)){
    std_ReturnType ret = E_NOT_OK;
    if(INT0_InterruptHandler == NULL){
        ret = E_NOT_OK;
        ret = E_OK;
    }
    else { 
        INT2_InterruptHandler = InterruptHandler;
    }
     
    return ret;
}

static std_ReturnType Interrupt_INTX_setInterruptHandler(const interrupt_INTx_t * int_obj ){
    std_ReturnType ret = E_NOT_OK;
    if(int_obj == NULL){
        ret = E_NOT_OK;
    }
    else { 
        switch(int_obj->source){
            case INTERRUPT_int0 : 
                ret = INT0_setInterruptHandler(int_obj->INTERRUPT_HANDLER);     
                ret = E_OK;
                break;     
            case INTERRUPT_int1:
                ret = INT1_setInterruptHandler(int_obj->INTERRUPT_HANDLER);  
                ret = E_OK;
                break;
            case INTERRUPT_int2:
                ret = INT2_setInterruptHandler(int_obj->INTERRUPT_HANDLER);  
                ret = E_OK;
                break;
            default: ret = E_NOT_OK;               
        }           
    }
     
    return ret;
}

std_ReturnType interrupt_RBx_init(const interrupt_RBx_t * rb_obj){
    std_ReturnType ret = E_NOT_OK;
    if(rb_obj == NULL){
        ret = E_NOT_OK;
    }
    else {
        /*Disable*/
        RBx_INTERRUPT_DISABLE(); 
        /*Clear flag*/
        RBx_INTERRUPT_FLAG_CLEAR();
        /*Priority*/
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(rb_obj->priority == INTERRUPT_HIGH_PRIORITY){
                INTERRUPT_GlobalInterruptHighPriorityEnable();
                RBx_INTERRUPT_HighPriorty(); 
            }else if(rb_obj->priority == INTERRUPT_LOW_PRIORITY){
                INTERRUPT_GlobalInterruptLowPriorityEnable();
                RBx_INTERRUPT_LowPriorty(); 
            }else{}       
        #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
        #endif
        /*Pin initialize*/
        ret = gpio_pin_direction_initialize(&(rb_obj->pin));
        /*Function pointer*/
        switch(rb_obj->pin.pin){
            case GPIO_PIN4 :
                RB4_InterruptHandler_HIGH = rb_obj->INTERRUPT_HANDLER_HIGH;
                RB4_InterruptHandler_LOW = rb_obj->INTERRUPT_HANDLER_LOW;
                break;
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = rb_obj->INTERRUPT_HANDLER_HIGH;
                RB5_InterruptHandler_LOW = rb_obj->INTERRUPT_HANDLER_LOW;
                break;
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = rb_obj->INTERRUPT_HANDLER_HIGH;
                RB6_InterruptHandler_LOW = rb_obj->INTERRUPT_HANDLER_LOW;
                break;
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = rb_obj->INTERRUPT_HANDLER_HIGH;
                RB7_InterruptHandler_LOW = rb_obj->INTERRUPT_HANDLER_LOW;
                break; 
            default : 
                ret = E_NOT_OK;
        }
        /*Enable*/
        RBx_INTERRUPT_ENABLE();
        ret = E_OK;
    }
    return ret;
}

void RB4_ISR(uint8 rb4_source){
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(rb4_source == 0){
        if(RB4_InterruptHandler_HIGH){ RB4_InterruptHandler_HIGH(); }
    }else if (rb4_source == 1){
        if(RB4_InterruptHandler_LOW){ RB4_InterruptHandler_LOW(); }
    }else{}
}

void RB5_ISR(uint8 rb5_source){
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(rb5_source == 0){
        if(RB5_InterruptHandler_HIGH){ RB5_InterruptHandler_HIGH(); }
    }else if (rb5_source ==1) {
        if(RB5_InterruptHandler_LOW){ RB5_InterruptHandler_LOW(); }
    }else{}
}

void RB6_ISR(uint8 rb6_source){
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(rb6_source == 0){
        if(RB6_InterruptHandler_HIGH){ RB6_InterruptHandler_HIGH(); }
    }else if (rb6_source ==1) {
        if(RB6_InterruptHandler_LOW){ RB6_InterruptHandler_LOW(); }
    }else{}
}

void RB7_ISR(uint8 rb7_source){
    RBx_INTERRUPT_FLAG_CLEAR();
    
    if(rb7_source == 0){
        if(RB7_InterruptHandler_HIGH){ RB7_InterruptHandler_HIGH(); }
    }else if (rb7_source ==1) {
        if(RB7_InterruptHandler_LOW){ RB7_InterruptHandler_LOW(); }
    }else{}
}



std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t * rb_obj);
