
#ifndef EVENTS_H
#define EVENTS_H
#include <stdlib.h>
typedef short eventType;
typedef unsigned int uint;

#define NOEVENT '$'

//Esta funcion devuelve el caracter a analizar del texto. Recibe un puntero al archivo requerido y un puntero a un contador de lineas recorridas
eventType getNextEvent(FILE * m, int &line);	

#endif /* EVENTS_H */

