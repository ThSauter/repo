/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: PotiObserver
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\PotiObserver.cpp
*********************************************************************/

//## auto_generated
#include "PotiObserver.h"
//## operation update(PotiSubject)
#include "PotiSubject.h"
//## package Default

//## class PotiObserver
PotiObserver::PotiObserver() {
    itsPotiSubject = NULL;
}

PotiObserver::~PotiObserver() {
    cleanUpRelations();
}

PotiSubject* PotiObserver::getItsPotiSubject() const {
    return itsPotiSubject;
}

void PotiObserver::setItsPotiSubject(PotiSubject* p_PotiSubject) {
    if(p_PotiSubject != NULL)
        {
            p_PotiSubject->_addItsPotiObserver(this);
        }
    _setItsPotiSubject(p_PotiSubject);
}

void PotiObserver::cleanUpRelations() {
    if(itsPotiSubject != NULL)
        {
            PotiSubject* current = itsPotiSubject;
            if(current != NULL)
                {
                    current->_removeItsPotiObserver(this);
                }
            itsPotiSubject = NULL;
        }
}

void PotiObserver::__setItsPotiSubject(PotiSubject* p_PotiSubject) {
    itsPotiSubject = p_PotiSubject;
}

void PotiObserver::_setItsPotiSubject(PotiSubject* p_PotiSubject) {
    if(itsPotiSubject != NULL)
        {
            itsPotiSubject->_removeItsPotiObserver(this);
        }
    __setItsPotiSubject(p_PotiSubject);
}

void PotiObserver::_clearItsPotiSubject() {
    itsPotiSubject = NULL;
}

/*********************************************************************
	File Path	: MCB1700\Debug\PotiObserver.cpp
*********************************************************************/
