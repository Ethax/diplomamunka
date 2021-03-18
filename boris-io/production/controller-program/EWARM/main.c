#include "stm32f10x.h"
#include "init.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

 
/* User defined function prototypes */

#define TBUF_SIZE   256
#define MAX_DATANUMBER 3


void UARTAdatKuld(char data);
void UART_StrKuld(volatile char *s);
unsigned int read_port_input(void);



struct buf_st {
  unsigned int in;                                // Next In Index
  unsigned int out;                               // Next Out Index
  char buf [TBUF_SIZE];                           // Buffer
};


static struct buf_st tbuf = { 0, 0, };
#define SIO_TBUFLEN ((unsigned short)(tbuf.in - tbuf.out))

static unsigned int tx_restart = 1; 


unsigned char receiveddata[MAX_DATANUMBER+1];
unsigned char datanumber;
unsigned int portout,portin;






int main()
{
  
  
 // 
  tbuf.in = 0;                                    // Clear com buffer indexes
  tbuf.out = 0;
  tx_restart = 1;

  
  Clk_Init();
 
 // GPIOC_Init();
  GPIOB_Init();
 GPIOA_Init();
  GPIOD_Init(); 
  GPIOE_Init(); 
  
 
  USART2_Init();
  
  
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
 
 
  while(1)
  {
     
      if ( datanumber!=0)
      {
        switch(receiveddata[0])
        {
        case 0x02:
          UART_StrKuld("SO3715-1H.110");
          datanumber=0; 
        break;
        case 0xb9:
           portin=read_port_input();
           UARTAdatKuld(portin>>8);
           UARTAdatKuld(portin);
           datanumber=0;
          break;
        case 0xba:
          if (datanumber==3)
          {
            portout=receiveddata[1];
            portout=(portout<<8)+receiveddata[2];
            GPIO_Write(GPIOD,(0xFFFF-portout));
            datanumber=0;
          }
          break;
        default:
          datanumber=0;
          break;
        }
      }
  }  
}  
  
 unsigned int read_port_input(void)
 {
   unsigned int input,input_s;
   input_s=GPIO_ReadInputData(GPIOB);
   input=((input_s>>3)&0x007F);
   input=input+ ((input_s<<2)&0xf000);
   input_s=GPIO_ReadInputData(GPIOA);
   input=input+((input_s<<4)&0x0f00);
   input_s=GPIO_ReadInputData(GPIOE);
   input=input+((input_s<<7)&0x0080);
  return (0xffff-input);
   
 }

 

 
/**********************************************************
 * USART1 interrupt request handler: 
 **********************************************************/
void USART2_IRQHandler(void)
{
    struct buf_st *p;
    /* RXNE handler */
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
       receiveddata[datanumber]=USART_ReceiveData(USART2);
       datanumber++;
    }
    /* TXE handler */
    if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
    {
    
      USART2->SR &= ~USART_FLAG_TXE;	          // clear interrupt

      p = &tbuf;

      if (p->in != p->out) {
        USART2->DR = (p->buf [p->out & (TBUF_SIZE-1)] & 0x1FF);
        p->out++;
        tx_restart = 0;
      }
      else 
      {
        tx_restart = 1;
	USART2->CR1 &= ~USART_FLAG_TXE;		      // disable TX interrupt if nothing to send
        
      }
      
    }
}   



void UARTAdatKuld(char data)
{
      struct buf_st *p = &tbuf;                                                        
      p->buf [p->in & (TBUF_SIZE - 1)] = data;           // Add data to the transmit buffer.
      p->in++;
      if (tx_restart) 
      {                               // If transmit interrupt is disabled, enable it
          tx_restart = 0;
          USART_ITConfig(USART2, USART_IT_TXE, ENABLE);		          // enable TX interrupt
      } 
}


void UART_StrKuld(volatile char *s)
{

	while(*s)
        {
                UARTAdatKuld(*s);
		*s++;
	}
         UARTAdatKuld(0x00);
}




