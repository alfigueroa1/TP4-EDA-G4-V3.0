#ifndef _FSMSTRING_H
#define _FSMSTRING_H

#include "genericFSM.h"
#include "events.h"
#include "FSMstates.h"

class FSMString:public genericFSM{

public:
	FSMString() {												//Constructor
		rowCount = 6;
		done = false;
		state = strState0;										//Estado inicial
	}
	virtual int filterEvents(eventType ev) {					//Filtro de eventos a evaluar
		switch (ev) {
		case '"':
			return 1;
		case EOF:
			return 2;
		case '/':
			return 3;
		case 'f':case 'n':case 'r':case 't':case 'u':case 'b':
			return 4;
		default:
			return 6;
		}
	}
	virtual void cycle(eventType* ev) {
		eventType evento;
		int i = 0, j = 0;
		evento = filterEvents(*ev);
		i = evento;
		switch (state) {
		case strState0:	j = 0; break;							//Como los estados estan predefinidos con numeros desordenados, este switch
		case strState1:	j = 1; break;							//los traspasa al numero que representarian en esta FSM en particular
		case strState2:	j = 2; break;
		case strState3:	j = 3; break;
		case strState4:	j = 4; break;
		}
		state = FSMTable[(j * rowCount) + (evento - 1)].nextState;
		FSMTable[(j * rowCount) + (evento - 1)].action;
	}

private:
#define SX(x) (static_cast<void (genericFSM::* )(eventType*)>(&FSMString::x))

    const fsmCell FSMTable[30] = {								//Tabla de estados

            // Recibir "				// Recibir EOF			// Recibir \				// Recibir chars				// Recibir 4hex         // Recibir others
            {strState1, SX(strNop)},	{ERROR, SX(strNop)},	{ERROR, SX(strNop)},		{ERROR, SX(strNop)},		{ERROR, SX(strNop)},		{ERROR, SX(strNop)},
            {strState4, SX(strNop)},			{ERROR, SX(strNop)},	{strState2, SX(strNop)},	{strState1, SX(strNop)},	{strState1, SX(strNop)},    {strState1, SX(strNop)},
            {strState3, SX(strNop)},	{ERROR, SX(strNop)},	{strState3, SX(strNop)},	{strState3, SX(strNop)},	{ERROR, SX(strNop)},		{ERROR, SX(strNop)},
            {strState4, SX(strNop)},			{ERROR, SX(strNop)}, 	{strState2, SX(strNop)},	{strState1, SX(strNop)},	{strState1, SX(strNop)},    {strState1, SX(strNop)},
			{FIN, SX(strNop)},			{FIN, SX(strNop)}, 		{FIN, SX(strNop)},			{FIN, SX(strNop)},			{FIN, SX(strNop)},			{FIN, SX(strNop)}
			//     {ERROR, SX(strNop)},		{ERROR, SX(strNop)},	{ERROR, SX(strNop)},		{ERROR, SX(strNop)},		{strState3, SX(strNop)},    {ERROR, SX(strNop)}
    };
	void strNop(eventType* ev) {								//Acciones
		return;
	}

};

#endif //_FSMSTRING_H
