#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        OBJECT FSM
 ************************************************************/
class FSMElement :public genericFSM {

public:
	FSMElement() {								//Constructor
		rowCount = 0;
		done = true;
		state = elementState0;					//Estado inicial					
	}
	virtual int filterEvents(eventType ev) {	//Filtro de caracteres a evaluar
		return 0;
	}
	virtual void cycle(eventType* ev) {
		state = FSMTable[0].nextState;
		FSMTable[0].action;
	}

private:
#define FX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMElement::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[1] = {					//Tabla de estados
		//ANYTHING
		{NEWVALUE, FX(elementOk)}		
	};
	void elementOk(eventType* ev) {					//Acciones
		done = true;
		return;
	}

};
