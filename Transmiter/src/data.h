#ifndef _DATA
#define _DATA
#define CASA 1
#define ESTUDIO 2
#define LOCAL ESTUDIO

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
#endif

#endif
