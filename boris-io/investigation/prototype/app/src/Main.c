#include <common.h>
#include <core/BorisProdigy.h>
#include <serialcomm/Serial.h>

/**
 * @brief A magas priorit�s� megszak�t�sokat kiszolg�l� rutin.
 *
 * Amennyiben a priorit�skezel�s nincs enged�lyezve, minden megszak�t�s ide fut
 * be.
 */
void interrupt() {
  /* Az UART fogad� puffer�be �rkezett adat hat�s�ra bek�vetkezett megszak�t�s
  kezel�se. */
  if(RC1IF_bit && RC1IE_bit)
    Serial_handleInterrupt();
}

/**
 * @brief A program fut�s�nak kezd�pontja.
 */
void main() {
  /* Az alkalmaz�s inicializ�l�sa �s futtat�sa. */
  BorisProdigy_initialize();
  BorisProdigy_run();
}