#include <iostream>
#include <stdlib.h>
#include "events.h"
#include "genericFSM.h"
#include "FSMElement.h"
#include "FSMValue.h"
#include "FSMObject.h"
#include "FSMArray.h"
#include "FSMNumber.h"
#include "FSMString.h"
#include "FSMTrue.h"
#include "FSMFalse.h"
#include "FSMNull.h"
#include "parseCmdLine.h"
#include "userData.h"
#include "stackManagement.h"


void stackFSMsPush(int instance, genericFSM** stack, uint &stackLevel);
void stackFSMsPop(genericFSM** stack, uint& stackLevel);
void freeStack(genericFSM** stack, uint& stackLevel);
void checkNewInstance(genericFSM** stackFSMs, uint& stackLevel, eventType* ev);

int main(int argc, char** argv) {
	argTypes archivo;
	if (parseCmdLine(argc, argv, parseCallback, &archivo) != -1)						//Parseo datos de entrada por linea de comandos
	{

		genericFSM* stackFSMs[100];														//stack de Fsms
		FSMElement element;
		int error = 0, line = 1;														//Flag de error y numero de linea que se analiza
		bool quit = false;
		int instance = 0;
		eventType ev = NOEVENT;															//Inicializo variable de evento
		stackFSMs[0] = &element;														//Seteo la primer FSM con una del tipo objeto

		unsigned int stackLevel = 0, last = 0;
		while (ev != EOF && !quit) {													//Ejecuto mientras no haya llegado al final del archivo
			ev = getNextEvent(archivo.file, line);										//Leo dato
			if (ev != NOEVENT) {														//Analizo si es un evento que sea de interes
				//printf("Event detected: %c at line %d\n", ev, line);
				stackFSMs[stackLevel]->cycle(&ev);										//Si lo es, ejecuto un ciclo de FSM
				if ((stackFSMs[stackLevel]->getState()) == ERROR) {
					quit = true;														//En caso de haber llegado a error, activo el flag y salgo
					printf("Error Found at line %d!\n", line);							//Imprimo linea de error
				}
				else if ((stackFSMs[stackLevel]->getState()) == FIN) {
					if (stackLevel == 0)												//Si llega al final de una FSM, pregunto si es la ultima
						break;															//De serlo, significara que ya he terminado
					else {
						stackFSMsPop(stackFSMs, stackLevel);							//Caso contrario, llamo a la que la precede
						while (stackFSMs[stackLevel]->getDone()) {						//Analizo si la actual FSM solo esperaba que terminara una que contenia
							if (stackLevel == 0)
								break;													//Si era la ultima salgo
							else
								stackFSMsPop(stackFSMs, stackLevel);					//Miro las siguientes	
						}
						stackFSMs[stackLevel]->cycle(&ev);								//Ni bien se cambia de FSM, para conservar el ultimo digito se ejecuta un ciclo de FSM
						checkNewInstance(stackFSMs, stackLevel, &ev);					//Y se chequea la necesidad de una nueva instancia
					}
				}
				else
					checkNewInstance(stackFSMs, stackLevel, &ev);						//Resta preguntar si el ciclo respondio con una nueva FSM necesaria
			}
		}
		freeStack(stackFSMs, stackLevel);												//Libero memoria
		if (quit)
			printf("Invalid sintaxis in file\n");										//Imprimo	
		else
			printf("Valid File\n");
		fclose(archivo.file);

	}
	else
		printf("Invalid File\n");
	return 0;
}

void checkNewInstance(genericFSM** stackFSMs, uint& stackLevel, eventType *ev) {
	while ((stackFSMs[stackLevel]->getState()) == NEWELEM || (stackFSMs[stackLevel]->getState()) == NEWOBJ || (stackFSMs[stackLevel]->getState()) == NEWARRAY
		|| (stackFSMs[stackLevel]->getState()) == NEWTRUE || (stackFSMs[stackLevel]->getState()) == NEWFALSE || (stackFSMs[stackLevel]->getState()) == NEWNULL
		|| (stackFSMs[stackLevel]->getState()) == NEWVALUE || (stackFSMs[stackLevel]->getState()) == NEWSTRING || (stackFSMs[stackLevel]->getState()) == NEWNUM) {
		stackFSMsPush(stackFSMs[stackLevel]->getState(), stackFSMs, stackLevel);
		//printf("New FSM instance needed!\n");
		//printf("StackLevel: %d\n", stackLevel);
		stackFSMs[stackLevel]->cycle(ev);
	}
	return;
}