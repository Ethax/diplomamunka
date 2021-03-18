#ifndef INC_BORISPRODIGY_H_
#define INC_BORISPRODIGY_H_

#include <common.h>

/**
 * @brief Az k�relmek v�rakoz�si sor�nak m�rete.
 */
#define REQUEST_QUEUE_SIZE 20

/**
 * A be�rkezett k�relmek t�pusainak felsorol�sa.
 */
enum RequestType {
  REQUEST_GET_DEVICE_TYPE,
  REQUEST_GET_INPUT,
  REQUEST_SET_OUTPUT
};

/**
 * @brief A be�rkezett k�relem strukt�r�ja.
 */
typedef struct request_entry_t {
  /**
   * A be�rkezett k�relem t�pusa.
   */
  enum RequestType type;
  
  /**
   * A be�rkezett k�relem els� adatb�jtja.
   */
  uint8_t dataHigh;
  
  /**
   * A be�rkezett k�relem m�sodik adatb�jtja.
   */
  uint8_t dataLow;
} RequestEntry;

/**
 * @brief A be�rkezett k�relmek v�rakoz�si sor�nak strukt�r�ja.
 */
typedef struct request_queue_t {
  /**
   * A v�rakoz�si sor utols� elem�nek sorsz�ma.
   */
  uint8_t end;

  /**
   * A v�rakoz�si sor els� elem�nek sorsz�ma.
   */
  uint8_t begin;

  /**
   * A be�rkezett k�relmeket t�rol� t�mb.
   */
  RequestEntry requests[REQUEST_QUEUE_SIZE];
} RequestQueue;

/**
 * @brief Inicializ�lja a mikrovez�rl� I/O portjait, a perif�ri�it �s az
 * alkalmaz�st a hozz� kapcsol�d� �sszes modullal egy�tt.
 */
void BorisProdigy_initialize();

/**
 * @brief Elt�rolja a megadott k�relmet a k�relmek v�rakoz�si sor�nak soron
 * k�vetkez� rekesz�be.
 *
 * @param type A k�relem t�pusa.
 * @param data_h A k�relem els� adatb�jtja.
 * @param data_l A k�relem m�sodik adatb�jtja.
 */
void BorisProdigy_setRequest(enum RequestType type, uint8_t data_h, uint8_t data_l);

/**
 * @brief Feldolgozza a soron k�vetkez� k�relmet a k�relmek v�rakoz�si sor�b�l,
 * amennyiben a sor nem �res.
 */
void BorisProdigy_handleRequests();

/**
 * @brief Enged�lyezi a glob�lis megszak�t�sokat �s v�gtelen ciklusban
 * v�grehajtja a be�kez� k�relmeket.
 */
void BorisProdigy_run();

#endif /* INC_BORISPRODIGY_H_ */