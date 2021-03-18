#ifndef INC_SERIAL_H_
#define INC_SERIAL_H_

#include <common.h>

/**
 * A be�ll�that� adat�tviteli sebess�gek felsorol�sa.
 */
enum BaudRate {
  BAUD_1200, BAUD_2400, BAUD_4800, BAUD_9600, BAUD_19200, BAUD_38400,
  BAUD_57600, BAUD_115200
};

/**
 * @breif Inicializ�lja a soros kommunik�ci�s portot �s be�ll�ja az adat�tviteli
 * sebess�get a megadott �rt�knek megfelel�en, majd enged�lyezi a megszak�t�st
 * az adatb�jtok �rkez�s�re.
 *
 * @param baudrate A be�ll�tani k�v�nt adat�tviteli sebess�g.
 */
void Serial_initialize(enum BaudRate baudrate);

/**
 * @brief Kezeli a soros portra �rkezett adatb�jttal j�r� megszak�t�st �s t�rli
 * a megszak�t�s jelz�bitj�t.
 *
 * Annak �rdek�ben, hogy a megszak�t�s le legyen kezelve annak bek�vetkez�sekor,
 * ennek a f�ggv�nynek megszak�t�sokat kiszolg�l� rutinban kell lennie.
 */
void Serial_handleInterrupt();

/**
 * @brief Kik�ldi az �tadott karakterl�ncot a soros kommunik�ci�s porton
 * kereszt�l.
 *
 * @param str A kik�ld�sre sz�nt karakterl�nc els� elem�re mutat� pointer.
 */
void Serial_sendString(char* str);

/**
 * @brief Kik�ldi az �tadott adatt�mb�t a soros kommunik�ci�s porton kereszt�l.
 *
 * @param str A kik�ld�sre sz�nt adatt�mb els� elem�re mutat� pointer.
 * @param size Az adatt�mb m�rete.
 */
void Serial_sendData(uint8_t* data_ptr, uint8_t size);

#endif /* INC_SERIAL_H_ */