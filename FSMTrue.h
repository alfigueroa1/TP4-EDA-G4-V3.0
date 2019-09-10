#pragma once
#include "genericFSM.h"
#include "FSMstates.h"
#include "events.h"
/*************************************************************
 *                        TRUE FSM
 ************************************************************/
class FSMTrue :public genericFSM {

public:
	FSMTrue() {										//Constructor
		rowCount = 5;
		done = false;
		state = trueState0;							//Estado inicial
	}
	virtual int filterEvents(eventType ev) {		//Filtro de eventos a evaluar
		switch (ev) {
		case 't':
			return 1;
		case 'r':
			return 2;
		case 'u':
			return 3;
		case 'e':
			return 4;
		default:
			return 5;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case trueState0:	j = 0; break;			//Como los estados estan predefinidos con numeros desordenados, este switch
		case trueState1:	j = 1; break;			//los traspasa al numero que representarian en esta FSM en particular
		case trueState2:	j = 2; break;
		case trueState3:    j = 3; break;
		case trueState4:	j = 4; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;		//Nuevo estado
		FSMTable[(j * rowCount) + (evento - 1)].action;
	}

private:
#define QX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMTrue::x))

	//const fsmCell fsmTable[4][6] = {
	const fsmCell FSMTable[25] = {					//Tabla de estados
		//Recibir 't'				Recibir 'r'					Recibir 'u'					Recibir 'e'				Recibir others		
		{trueState1, QX(valueNop)},	{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop) },		{trueState2, QX(valueNop) }, {ERROR, QX(valueNop) },	{ERROR, QX(valueNop) },	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{trueState3, QX(valueNop)},	{ERROR, QX(valueNop)},	{ERROR, QX(valueNop)},
		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{ERROR, QX(valueNop)},		{trueState4, QX(valueNop)},	{ERROR, QX(valueNop)},
		{FIN, QX(valueNop)},		{FIN, QX(valueNop)},		{FIN, QX(valueNop)},		{FIN, QX(valueNop)},	{FIN, QX(valueNop)}
	};
	void valueNop(eventType* ev) {					//Acciones
		return;
	}
	void valueOk(eventType* ev) {
		done = true;
		return;
	}
};