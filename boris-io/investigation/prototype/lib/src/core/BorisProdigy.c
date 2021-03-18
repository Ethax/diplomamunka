#include <core/BorisProdigy.h>
#include <serialcomm/Serial.h>

/*
 * A k�relmek v�rakoz�si sor�nak deklar�l�sa.
 */
volatile RequestQueue requestQueue;

/*
 * Az eszk�z sorozatsz�m�nak deklar�l�sa �s inicializ�l�sa.
 */
uint8_t serialNumber[] = "SO3715-1H.110"; //{ 'S', 'O', '3', '7', '1', '5', '-', '1', 'H', '.', '1', '1', '0', '\0' };

/*
 * Inicializ�lja a mikrovez�rl� I/O portjait, a perif�ri�it �s az  alkalmaz�st
 * a hozz� kapcsol�d� �sszes modullal egy�tt.
 */
void BorisProdigy_initialize() {
  /* Az A/D �s D/A �talak�t�k, illetve a kompar�torok kikapcsol�sa. */
  ADCON0 = ADCON1 = ADCON2 = 0x00;
  CM1CON0 = CM2CON0 = VREFCON0 = VREFCON1 = VREFCON2 =  0x00;
  
  /* Minden I/O port standard jelv�ltoz�si sebess�g� digit�lis bemenetre
  konfigur�l�sa, �s a hozz�juk tartoz� t�rol�k t�rl�se. */
  ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = 0x00;
  SLRCON = LATA = LATB = LATC = LATD = LATE = 0x00;
  TRISA = TRISB = TRISC = TRISD = TRISE = 0xFF;

  /* A B �s C portok digit�lis kimenetre konfigur�l�sa a LED-ek
  m�k�dtet�s�hez. */
  TRISB = TRISD = 0x00;

  /* Az alkalmaz�s moduljainak inicializ�l�sa. */
  requestQueue.begin = requestQueue.end = 0;
  Serial_initialize(BAUD_9600);
}

/*
 * Elt�rolja a megadott k�relmet a k�relmek v�rakoz�si sor�nak soron k�vetkez�
 * rekesz�be.
 */
void BorisProdigy_setRequest(enum RequestType type, uint8_t data_h, uint8_t data_l) {
  /* A v�rakoz�si sor k�vetkez� elem�nek fel�l�r�sa a megadott k�relem
  param�terekkel. */
  requestQueue.requests[requestQueue.end].type = type;
  requestQueue.requests[requestQueue.end].dataHigh = data_h;
  requestQueue.requests[requestQueue.end].dataLow = data_l;
  
  /* A sor utols� elem�re mutat� sz�ml�l� n�vel�se. */
  requestQueue.end = (requestQueue.end + 1) % REQUEST_QUEUE_SIZE;

  /* A v�rakoz�si sorban lev� k�vetkez� k�relem kijel�l�se, amennyiben a
  v�rakoz�si sorban t�lcsordul�s keletkezett. (A legr�gebbi k�relem el fog
  veszni.) */
  if(requestQueue.end == requestQueue.begin)
    requestQueue.begin = (requestQueue.begin + 1) % REQUEST_QUEUE_SIZE;
}

/*
 * Feldolgozza a soron k�vetkez� k�relmet a k�relmek v�rakoz�si sor�b�l,
 * amennyiben a sor nem �res.
 */
void BorisProdigy_handleRequests() {
  /* A bemenet beolvas�sa ut�n annak a jelenlegi �llapotait t�rol� t�mb. */
  uint8_t port_data[2] = { 0 };
  
  /* Azonnali visszat�r�s a f�ggv�nyb�l, ha a v�rakoz�si sor �res. */
  if(requestQueue.begin == requestQueue.end) return;

  /* A soron k�vetkez� k�relem feldolgoz�sa. */
  switch(requestQueue.requests[requestQueue.begin].type) {
  case REQUEST_GET_DEVICE_TYPE:
    Serial_sendData(serialNumber, 14);
    break;
  case REQUEST_GET_INPUT:
    port_data[0] = PORTA;
    port_data[1] = 0 | (PORTC & 0x0F) | ((PORTE & 0x0F) << 4);
    Serial_sendData(port_data, 2);
    break;
  case REQUEST_SET_OUTPUT:
    LATB = requestQueue.requests[requestQueue.begin].dataHigh;
    LATD = requestQueue.requests[requestQueue.begin].dataLow;
    break;
  }

  /* A v�rakoz�si sorban lev� k�vetkez� k�relem kijel�l�se. */
  requestQueue.begin = (requestQueue.begin + 1) % REQUEST_QUEUE_SIZE;
}

/*
 * Enged�lyezi a glob�lis megszak�t�sokat �s v�gtelen ciklusban v�grehajtja a
 * be�kez� k�relmeket.
 */
void BorisProdigy_run() {
  /* A megszak�t�sok priorit�skezel�s�nek tilt�sa, majd a periferi�lis �s
  glob�lis megszak�t�sok enged�lyez�se. */
  IPEN_bit = false;
  PEIE_bit = GIE_bit = true;

  /* A be�rkezett k�relmek folyamatos feldolgoz�sa �s a megfelel� m�veletek
  v�grehajt�sa. */
  requestQueue.begin = requestQueue.end = 0;
  while(true)
    BorisProdigy_handleRequests();
}