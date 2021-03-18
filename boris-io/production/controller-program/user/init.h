#ifndef __INIT_H
#define __INIT_H

#include "stm32f10x.h"

// For store tick counts in us
static __IO uint32_t usTicks;



void Clk_Init(void);
void InitializeTimer(void);
void GPIOC_Init(void);
void GPIOB_Init(void);
void GPIOD_Init(void);
void GPIOE_Init(void);
void USART2_Init(void);
void EXTI1_Config(void);
void EXTI2_Config(void);
void GPIOA_Init(void);
void lcd_input(void);
void lcd_output(void);
void InitializeTimer3(void);
void DelayUs(uint32_t us);
void EXTI4_Config(void);
void EXTI4_DISABLE(void);

void EXTI4_ENABLE(void);


//extern unsigned int v;


#endif
