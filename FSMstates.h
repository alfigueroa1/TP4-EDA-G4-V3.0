#pragma once

//Estados predefinidos

enum FSMStates {
	FIN, ERROR, NEWELEM, NEWOBJ, NEWARRAY, NEWVALUE, NEWSTRING, NEWNUM, NEWTRUE, NEWFALSE, NEWNULL,
	objectState0, objectState1, objectState2, objectState3, objectState4,
	arrayState0, arrayState1, arrayState2, arrayState3,
	valueState0,
	strState0, strState1, strState2, strState3, strState4,
	numState0, numState1, numState2, numState3, numState4, numState5, numState6, numState7, numState8,
	elementState0, elementState1, elementState2,
	trueState0, trueState1, trueState2, trueState3, trueState4,
	falseState0, falseState1, falseState2, falseState3, falseState4, falseState5,
	nullState0, nullState1, nullState2, nullState3, nullState4
};