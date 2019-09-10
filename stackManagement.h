#pragma once
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

//Esta funcion se encarga de colocar una nueva FSM en la cola de eFSMs. Recibe
//la nueva instancia requerida (numero predefinido), la cola de FSMs, y la linea actual de la cola
void stackFSMsPush(int instance, genericFSM** stack, uint& stackLevel);

//Esta funcion es el opuesto que la anterior, cambia la FSM a analizar por la anterior. Se debiera llamar
//cuando una FSM ha terminado y se quiere acceder a la que la precedia. Recibe la cola FSMs, la linea actual de la misma
void stackFSMsPop(genericFSM** stack, uint& stackLevel);

//Esta funcion libera la memoria dinamica pedida en tiempo de ejecucion para las FSMs
void freeStack(genericFSM** stack, uint& stackLevel);