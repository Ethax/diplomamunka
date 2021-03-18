#include "init.h"


/***********************************************
 * Initialize clock                          *
 ***********************************************/
 
void Clk_Init(void)
{
      RCC_HSICmd(ENABLE);
       // várunk míg  HSI nem kész
       while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
       RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI); // 8 MHz
       
      // engedélyezzük a külsõ 8MHz-es oszcillátort
       RCC_HSEConfig(RCC_HSE_ON);
       // várunk míg  HSE nem kész
       while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);
       
       //belsõ PLL-lel felszorozzuk 72MHz-re
       RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9); // 72MHz
       RCC_PLLCmd(ENABLE);
       while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
       
       
       // 4. Set system clock dividers
       //két perifériabusz
      RCC_PCLK2Config(RCC_HCLK_Div1);  // 8 MHz
      RCC_PCLK1Config(RCC_HCLK_Div1);  // 8 MHz
      RCC_HCLKConfig(RCC_SYSCLK_Div1);  // 8 MHz
      //Ezután inicializáljuk a FLASH késleltetést:
      #ifdef EMB_FLASH
      // 5. Init Embedded Flash
      // Zero wait state, if 0 < HCLK 24 MHz
      // One wait state, if 24 MHz < HCLK 56 MHz
      // Two wait states, if 56 MHz < HCLK 72 MHz
      // Flash wait state
      FLASH_SetLatency(FLASH_Latency_2);
      // Half cycle access
      FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
      // Prefetch buffer
      FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
      #endif // EMB_FLASH
      // 6. Clock system from PLL
      RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
        
}
/***********************************************
 * Initialize Timer2                           *
 ***********************************************/
void InitializeTimer(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    timerInitStructure.TIM_Prescaler = 7200;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 4000;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

    //Enabled TIM2_IRQn
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
   
}

/***********************************************
 * Initialize Timer3                           *
 ***********************************************/
void InitializeTimer3(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    timerInitStructure.TIM_Prescaler = 7200;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 4000;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &timerInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3, ENABLE);

    //Enabled TIM3_IRQn
    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
   
}


/***********************************************
 * Initialize GPIOB PIN3-13 as input
 ***********************************************/
void GPIOB_Init(void)
{
    /* Bit configuration structure for GPIOB */
    GPIO_InitTypeDef gpiob_init_struct;
   
    gpiob_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpiob_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    gpiob_init_struct.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13;
    /* Initialize GPIOB: 50MHz, PINB,  */
   /* Enable PORT B clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_Init(GPIOB, &gpiob_init_struct);
      
    
    
    
    
}  
    

/***********************************************
 * Initialize GPIOC PIN13 as push-pull output
 ***********************************************/




void GPIOD_Init(void)
{
      GPIO_InitTypeDef gpiod_init_struct;
     
      gpiod_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
      gpiod_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
      gpiod_init_struct.GPIO_Pin = GPIO_Pin_All;
      
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
      GPIO_Init(GPIOD, &gpiod_init_struct);
      GPIO_Write(GPIOD,0xFFFF);

}


/***********************************************
 * Initialize GPIOA push-pull output
 ***********************************************/
void GPIOA_Init(void)
{
    /* Bit configuration structure for GPIOA */
    GPIO_InitTypeDef gpioa_init_struct;
   
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 |  GPIO_Pin_6| GPIO_Pin_7;
    
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    /* Initialize GPIOA: 50MHz, PINB,  */
 
   GPIO_Init(GPIOA, &gpioa_init_struct);
   
    
}



void GPIOE_Init(void)
{
    /* Bit configuration structure for GPIOE */
    GPIO_InitTypeDef gpioe_init_struct;
   
    gpioe_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioe_init_struct.GPIO_Mode = GPIO_Mode_IPU;
    gpioe_init_struct.GPIO_Pin = GPIO_Pin_0;
    
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    /* Initialize GPIOE: 50MHz, PINE,  */
  
    GPIO_Init(GPIOE, &gpioe_init_struct);
   
    
}


 
/*****************************************************
 * Initialize USART1: enable interrupt on reception
 * of a character
 *****************************************************/
void USART2_Init(void)
{
    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart2_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;
     
    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

    /* GPIOA PIN2 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_2;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN3 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_3;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);
 
    /* Enable USART1 */
    USART_Cmd(USART2, ENABLE);  
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart2_init_struct.USART_BaudRate = 9600;   
    usart2_init_struct.USART_WordLength = USART_WordLength_8b;  
    usart2_init_struct.USART_StopBits = USART_StopBits_1;   
    usart2_init_struct.USART_Parity = USART_Parity_No ;
    usart2_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart2_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART2 */
    USART_Init(USART2, &usart2_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    /* Enable USART2 global interrupt */
    NVIC_EnableIRQ(USART2_IRQn);
}




