/* 
 * File:   mcal_external_interrupt.h
 * Author: Rabeh Mohamed
 *
 * Created on August 1, 2023, 11:48 PM
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H


/*---------Includes-----------*/
#include "mcal_interrupt_config.h"
#include "mcal_interrupt_manager.h"
/*---------Macros Declarations----------*/

/*---------Macro Functions Declarations-----------*/
#if EXTERNAL_INTERRUPT_INTx_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    #define INT0_INTERRUPT_ENABLE()          (INTCONbits.INT0IE = 1)
    #define INT0_INTERRUPT_DISABLE()         (INTCONbits.INT0IE = 0)
    #define INT0_INTERRUPT_FLAG_CLEAR()      (INTCONbits.INT0IF = 0)
    #define INT0_INTERRUPT_RisingEdgeSet()   (INTCON2bits.INTEDG0 = 1)
    #define INT0_INTERRUPT_FallingEdgeSet()  (INTCON2bits.INTEDG0 = 0)

    #define INT1_INTERRUPT_ENABLE()          (INTCON3bits.INT1IE = 1)
    #define INT1_INTERRUPT_DISABLE()         (INTCON3bits.INT1IE = 0)
    #define INT1_INTERRUPT_FLAG_CLEAR()      (INTCON3bits.INT1IF = 0)
    #define INT1_INTERRUPT_RisingEdgeSet()   (INTCON2bits.INTEDG1 = 1)
    #define INT1_INTERRUPT_FallingEdgeSet()  (INTCON2bits.INTEDG1 = 0)

    #define INT2_INTERRUPT_ENABLE()          (INTCON3bits.INT2IE = 1)
    #define INT2_INTERRUPT_DISABLE()         (INTCON3bits.INT2IE = 0)
    #define INT2_INTERRUPT_FLAG_CLEAR()      (INTCON3bits.INT2IF = 0)    
    #define INT2_INTERRUPT_RisingEdgeSet()   (INTCON2bits.INTEDG2 = 1)
    #define INT2_INTERRUPT_FallingEdgeSet()  (INTCON2bits.INTEDG2 = 0)
   
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        #define INT1_INTERRUPT_HighPriorty()     (INTCON3bits.INT1IP = 1)
        #define INT1_INTERRUPT_LowPriorty()      (INTCON3bits.INT1IP = 0 )

        #define INT2_INTERRUPT_HighPriorty()     (INTCON3bits.INT2IP = 1)
        #define INT2_INTERRUPT_LowPriorty()      (INTCON3bits.INT2IP = 0 )

    #endif
#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    #define RBx_INTERRUPT_ENABLE()          (INTCONbits.RBIE = 1)
    #define RBx_INTERRUPT_DISABLE()         (INTCONbits.RBIE = 0)
    #define RBx_INTERRUPT_FLAG_CLEAR()      (INTCONbits.RBIF = 0)

    #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            #define RBx_INTERRUPT_HighPriorty()     (INTCON2bits.RBIP = 1)
            #define RBx_INTERRUPT_LowPriorty()      (INTCON2bits.RBIP = 0 )
    #endif

#endif
/*--------Data type Declarations------------------*/
typedef enum{
    INTERRUPT_int0 = 0,
    INTERRUPT_int1,
    INTERRUPT_int2
}interrupt_INTx_src;

typedef enum{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RAISING_EDGE  
}interrupt_INTx_edge;

typedef struct{
    void (*INTERRUPT_HANDLER)(void);
    pin_config_t pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source ;
    interrupt_priority priority;
}interrupt_INTx_t;

typedef struct{
    void(*INTERRUPT_HANDLER_HIGH)(void);
    void(*INTERRUPT_HANDLER_LOW)(void);
    pin_config_t pin;
    interrupt_priority priority;
}interrupt_RBx_t;

/*--------Function Declarations*/
std_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj);
std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t * int_obj);

std_ReturnType interrupt_RBx_init(const interrupt_RBx_t * rb_obj);
std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t * rb_obj);


#endif	/* MCAL_EXTERNAL_INTERRUPT_H */

