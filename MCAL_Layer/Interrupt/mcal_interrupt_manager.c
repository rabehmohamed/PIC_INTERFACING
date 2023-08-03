/* 
 * File:   mcal_interrupt_manager.c
 * Author: Rabeh Mohamed
 *
 * Created on August 1, 2023, 11:48 PM
 */

#include "mcal_interrupt_manager.h"
static volatile uint8 RB4_FLAG = 1,RB5_FLAG = 1,RB6_FLAG=1,RB7_FLAG=1;




#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptHighPriority(void){
    if( (INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)  ){
        INT0_ISR();
    }
    else {}
    if( (INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)  ){
        INT2_ISR();
    }
    else {} 
}

void __interrupt(low_priority) InterruptLowPriority(void){
    if( (INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)  ){
        INT1_ISR();
    }
    else {}
}

#else
void __interrupt() InterruptNoPriority(void){
    if( (INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_OCCUR)  ){
        INT0_ISR();
    }
    else {}
    if( (INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_OCCUR)  ){
        INT1_ISR();
    }
    else {}
    if( (INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_OCCUR)  ){
        INT2_ISR();
    }
    else {}  
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_FLAG == 1)){
        RB4_FLAG=0;
        RB4_ISR(0);     
    }
    else{}
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_FLAG == 0)){
        RB4_FLAG=1;
        RB4_ISR(1);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_FLAG == 1)){
        RB5_FLAG=0;
        RB5_ISR(1);     
    }
    else{}
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_FLAG == 0)){
        RB5_FLAG=1;
        RB5_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_FLAG == 1)){
        RB6_FLAG=0;
        RB6_ISR(1);     
    }
    else{}
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB6 == GPIO_LOW) && (RB6_FLAG == 0)){
        RB6_FLAG=1;
        RB6_ISR(0);
    }
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_FLAG == 1)){
        RB7_FLAG=0;
        RB7_ISR(1);     
    }
    else{}
    if((INTCONbits.RBIE == INTERRUPT_ENABLE ) && (INTCONbits.RBIF == INTERRUPT_OCCUR) && (PORTBbits.RB7 == GPIO_LOW) && (RB7_FLAG == 0)){
        RB7_FLAG=1;
        RB7_ISR(0);
    }
    
    
}


#endif