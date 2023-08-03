/* 
 * File:   mcal_interrupt_manager.h
 * Author: Rabeh Mohamed
 *
 * Created on August 1, 2023, 11:48 PM
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H


/*---------Includes-----------*/
#include "mcal_interrupt_config.h"
/*---------Macros Declarations----------*/


/*---------Macro Functions Declarations-----------*/

/*--------Data type Declarations------------------*/

/*--------Function Declarations*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 rb4_source);
void RB5_ISR(uint8 rb5_source);
void RB6_ISR(uint8 rb6_source);
void RB7_ISR(uint8 rb7_source);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

