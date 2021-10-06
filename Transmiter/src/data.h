#ifndef _DATA
#define _DATA
#define CASA 1
#define ESTUDIO 2
#define PRODUCAO 3
#define LOCAL PRODUCAO

#if LOCAL == ESTUDIO
  #define PORT 5005
  #define DEST "192.168.0.161"
  #define SSID "EGR Network"
  #define PASS "egrequena1"

#elif LOCAL == CASA
  #define PORT 5005
  #define DEST "192.168.15.2"
  #define SSID "StarFox"
  #define PASS "doabarrelroll64"

#elif LOCAL == PRODUCAO
  #define PORT 5005
  #define DEST "192.168.0.99"
  #define SSID "HERMES_SYS"
  #define PASS "losCavalos0412"
  #define ADMIN_PASS "losCavalos"
#endif

#endif
