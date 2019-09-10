#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        ARRAY FSM
 ************************************************************/
class FSMArray :public genericFSM {

public:
	FSMArray(){												//Constructor
		rowCount = 4;
		done = false;
		state = arrayState0;								//Estado inicial
	}
	virtual int filterEvents(eventType ev) {				//Filtro de caracteres a evaluar
		switch (ev) {
		case '[':
			return 1;
		case ']':
			return 2;
		case ',':
			return 3;
		default:
			return 4;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);						
		i = evento;
		switch (state) {
		case arrayState0:	j = 0; break;					//Como los estados estan predefinidos con numeros desordenados, este switch
		case arrayState1:	j = 1; break;					//los traspasa al numero que representarian en esta FSM en particular
		case NEWVALUE:		j = 2; break;					
		case FIN:	j = 2; evento = 2; break;
		case arrayState2:   j = 3; break;
		case arrayState3:   j = 4; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;		//Ejecuto celda
		FSMTable[(j * rowCount) + (evento - 1)].action;
		//this.*(this->FSMTable[(j * rowCount) + (evento - 1)].action)();
	}

private:

#define AX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMArray::x))

	//const fsmCell FSMTable[2][3] = {
	const fsmCell FSMTable[20] = {						//Tabla de estados(FSM)
		//Recibir '['					RECIBIR ']'					//RECIBIR ','				//Other
		{arrayState1, AX(arrayOk)},		{ERROR, AX(arrayError)},	{ERROR, AX(arrayError)},	{ERROR, AX(arrayError)},//arrayState0
		{NEWVALUE, AX(arrayOk)},		{arrayState3, AX(arrayOk)},	{ERROR, AX(arrayOk)},		{NEWVALUE, AX(arrayOk)},//arraySate1
		{ERROR, AX(arrayError)},		{arrayState3, AX(arrayOk)},	{arrayState2, AX(arrayOk)},	{ERROR, AX(arrayError)},	//NEWVALUE
		{NEWVALUE, AX(arrayOk)},		{NEWVALUE, AX(arrayOk)},	{NEWVALUE, AX(arrayOk)},	{NEWVALUE, AX(arrayError)},
		{FIN, AX(arrayOk)},				{FIN, AX(arrayOk)},			{FIN, AX(arrayOk)},			{FIN, AX(arrayOk)}

	};

	void arrayError(eventType* ev) {			//Acciones
		state = ERROR;
	}
	void arrayOk(eventType* ev) {
		return;
	}
};