#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        NULL FSM
 ************************************************************/
class FSMNull :public genericFSM {

public:
	FSMNull() {								//Constructor
		rowCount = 4;	
		done = false;
		state = nullState0;					//Estado inicial
	}
	virtual int filterEvents(eventType ev) {	//Filtro de eventos a evaluar
		switch (ev) {
		case 'n':
			return 1;
		case 'u':
			return 2;
		case 'l':
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
		case nullState0:	j = 0; break;		//Como los estados estan predefinidos con numeros desordenados, este switch
		case nullState1:	j = 1; break;		//los traspasa al numero que representarian en esta FSM en particular
		case nullState2:	j = 2; break;
		case nullState3:    j = 3; break;
		case nullState4:    j = 4; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(j * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMNull::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[20] = {				//Tabla de eventos
		//Recibir 'n'				Recibir 'u'					Recibir 'l'				Recibir others
		{nullState1, QX(valueNop)},	{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop) },		{nullState2, QX(valueNop)}, {ERROR, QX(valueNop) },	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{nullState3, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{nullState4, QX(valueNop)},	{ERROR, QX(valueNop)},
		{FIN, QX(valueNop)},		{FIN, QX(valueNop)},		{FIN, QX(valueNop)},	{FIN, QX(valueNop)},
	};
	void valueNop(eventType* ev) {				//Acciones
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};