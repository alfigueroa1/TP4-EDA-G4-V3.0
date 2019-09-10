#include <iostream> 
#include "stackManagement.h"

void stackFSMsPush(int instance, genericFSM** stack, uint& stackLevel) {
	genericFSM* newFSM = NULL;
	switch (instance) {
	case NEWELEM:	newFSM = new (std::nothrow) FSMElement;	/*printf("Entering Element FSM\n");*/ break;
	case NEWOBJ:	newFSM = new (std::nothrow) FSMObject;	/*printf("Entering Object FSM\n");*/ break;
	case NEWVALUE:	newFSM = new (std::nothrow) FSMValue;	/*printf("Entering Value FSM\n");*/ break;
	case NEWARRAY: newFSM = new (std::nothrow) FSMArray;	/*printf("Entering Array FSM\n");*/	break;
	case NEWSTRING: newFSM = new (std::nothrow) FSMString;	/*printf("Entering String FSM\n");*/ break;
	case NEWNUM: newFSM = new (std::nothrow) FSMNumber;		/*printf("Entering Number FSM\n"); */ break;
	case NEWTRUE: newFSM = new (std::nothrow) FSMTrue;		/*printf("Entering True FSM\n");*/ break;
	case NEWFALSE: newFSM = new (std::nothrow) FSMFalse;	/*printf("Entering False FSM\n");*/ break;
	case NEWNULL: newFSM = new (std::nothrow) FSMNull;		/*printf("Entering Null FSM\n");*/ break;
	default: genericFSM* newFSM = NULL; break;
	}
	if (newFSM == NULL) {
		printf("Couldn't Create new FSM instance!\n");
	}
	else {
		stackLevel++;									//Aumento stack y guardo nueva FSM
		stack[stackLevel] = newFSM;
	}
}
void stackFSMsPop(genericFSM** stack, uint& stackLevel) {			//Habiendo terminado una FSM, accedo a la que la precede
	if ((stack[stackLevel]) != NULL) {								// Verifico que no sea un error
		delete stack[stackLevel];									// Y elimino
		stackLevel--;					
	}
	//printf("Instance finished, stack poped\n");
	//printf("StackLevel: %d\n", stackLevel);
}

void freeStack(genericFSM** stack, uint& stackLevel) {				//Liberacion de memoria
	for (uint i = stackLevel; i > 0;) {
		stackFSMsPop(stack, i);
	}
}