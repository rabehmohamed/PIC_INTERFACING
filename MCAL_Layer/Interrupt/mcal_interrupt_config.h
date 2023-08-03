/* 
 * File:   mcal_interrupt_config.h
 * Author: Rabeh Mohamed
 *
 * Created on August 1, 2023, 11:47 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H
/*---------Includes-----------*/
#include "../pic18.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "mcal_interrupt_gen_config.h"
/*---------Macros Declarations----------*/
#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0
/*---------Macro Functions Declarations-----------*/
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

    #define INTERRUPT_PriorityLevelsEnable() (RCONbits.IPEN = 1)
    #define INTERRUPT_PriorityLevelsDisable() (RCONbits.IPEN = 0)
    #define INTERRUPT_GlobalInterruptHighPriorityEnable() (INTCONbits.GIEH = 1)
    #define INTERRUPT_GlobalInterruptHighPriorityDisable() (INTCONbits.GIEH = 0)
    #define INTERRUPT_GlobalInterruptLowPriorityEnable() (INTCONbits.GIEL = 1)
    #define INTERRUPT_GlobalInterruptLowPrioritDisable() (INTCONbits.GIEL = 0)

#else

    #define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
    #define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
    #define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
    #define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)


#endif
/*--------Data type Declarations------------------*/
typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority;
/*--------Function Declarations*/



#endif	/* MCAL_INTERRUPT_CONFIG_H */

