
#ifndef GENERICFSM_H
#define GENERICFSM_H

#include "events.h"
#include "FSMstates.h"

typedef unsigned int stateTypes;

class genericFSM;

struct fsmCell{									//Celda de cada Tabla de FSMs
    stateTypes nextState;								//Sigueiente estado
    void (genericFSM::*action)(eventType*);				//Accion
};


class genericFSM{
public:
	genericFSM() {								//Constructor
		state = elementState0;
		rowCount = 0;
		columnCount = 0;
		done = false;
	}
	virtual void cycle(eventType* ev) = 0;		//Funcion que ejecuta un "paso" en la FSM. Es virtual porque cada clase derivada debe definir una propia
	stateTypes getState() {						//Devuelve estado actual
		return state;
	}
	bool getDone() {							//evuelve estado absoluto de la FSM, si ha termiando o no
		return done;
	}
    //char* getErrorCode();
	virtual int filterEvents(eventType) = 0;	//Se usa en cycle, por eso tambien es virtual, y se encarga de filtrar cada evento distinto en los que a la FSM le interesan 
protected:    
	stateTypes state;							//Estado actual
    unsigned int rowCount;						//Filas
	bool done;									//Estado absoluto
private:
    unsigned int columnCount;					//Columnas
    //fsmCell * FSMTAble; 
};

#endif /* GENERICFSM_H */

