#include <serialcomm/Serial.h>
#include <core/BorisProdigy.h>

/*
 * A be�rkez� adatokat t�rol� fogad� puffer deklar�l�sa �s inicializ�l�sa.
 */
uint8_t receiveBuffer[10] = { 0 };

/*
 * Az elk�ld�sre sz�nt adatokat t�rol� kimen� puffer deklar�l�sa �s
 * inicializ�l�sa.
 */
uint8_t transmitBuffer[20] = { 0 };

/*
 * A be�rkez� adatb�jtokat sz�ml�l� v�ltoz� deklar�l�sa �s inicializ�l�sa.
 */
uint8_t receiveCounter = 0;

/*
 * Inicializ�lja a soros kommunik�ci�s portot �s be�ll�ja az adat�tviteli
 * sebess�get a megadott �rt�knek megfelel�en, majd enged�lyezi a megszak�t�st
 * az adatb�jtok �rkez�s�re.
 */
void Serial_initialize(enum BaudRate baudrate) {
  /* A soros kommunik�ci�s port inicializ�l�sa �s a megadott adat�tviteli
  sebess�g be�ll�t�sa. */
  switch(baudrate) {
  case BAUD_1200:
    UART1_Init(1200); break;
  case BAUD_2400:
    UART1_Init(2400); break;
  case BAUD_4800:
    UART1_Init(4800); break;
  case BAUD_9600:
    UART1_Init(9600); break;
  case BAUD_19200:
    UART1_Init(19200); break;
  case BAUD_38400:
    UART1_Init(38400); break;
  case BAUD_57600:
    UART1_Init(57600); break;
  case BAUD_115200:
    UART1_Init(115200); break;
  }

  /* A soros portra �rkezett adatb�jtokkal j�r� megszak�t�sok enged�lyez�se. */
  RC1IF_bit = false;
  RC1IE_bit = true;
}

/*
 * Kezeli a soros portra �rkezett adatb�jttal j�r� megszak�t�st �s t�rli a
 * megszak�t�s jelz�bitj�t.
 */
void Serial_handleInterrupt() {
  /* A fogadott b�jt kiolvas�sa a soros port puffer�b�l. */
  uint8_t next_byte = UART1_Read();

  /* A fogadott b�jtnak megfelel� k�relem belehelyez�se a k�relmek v�rakoz�si
  sor�ba. */
  switch(next_byte) {
  case 0x02: /* Get Device Type Request */
    BorisProdigy_setRequest(REQUEST_GET_DEVICE_TYPE, 0, 0);
    break;
  case 0xb9: /* Get Input Request */
    BorisProdigy_setRequest(REQUEST_GET_INPUT, 0, 0);
    break;
  case 0xba: /* Set Output Request */
    receiveCounter = 2;
    break;
  }
  
  /* A kimenetet be�ll�t� �j param�terek fogad�sa, amennyiben egy kor�bbi
  utas�t�s az �j param�terek �rkez�s�t jelezte. */
  if(receiveCounter && next_byte != 0xba) {
    receiveBuffer[2 - receiveCounter] = next_byte;
    if(--receiveCounter == 0)
      BorisProdigy_setRequest(REQUEST_SET_OUTPUT, receiveBuffer[0], receiveBuffer[1]);
  }

  /* A lekezelt megszak�t�s jelz�bitj�nek t�rl�se. */
  RC1IF_bit = false;
}

/*
 * Kik�ldi az �tadott karakterl�ncot a soros kommunik�ci�s porton kereszt�l.
 */
void Serial_sendString(char* str) {
  Serial_sendData(str, strlen(str));
}

/*
 * Kik�ldi az �tadott adatt�mb�t a soros kommunik�ci�s porton kereszt�l.
 */
void Serial_sendData(uint8_t* data_ptr, uint8_t size) {
  uint8_t i;
  
  /* A mutatott mem�riater�let �tm�sol�sa a kimen� pufferbe �s a kimen� puffer 
  tartalm�nak kik�ld�se a soros kommunik�ci�s porton kereszt�l. */
  memcpy(transmitBuffer, data_ptr, size);
  for(i = 0; i < size; i++)
    UART1_Write(transmitBuffer[i]);
}