/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: PotiSubject
//!	Generated Date	: Sun, 9, Apr 2017  
	File Path	: MCB1700\Debug\PotiSubject.cpp
*********************************************************************/

//## auto_generated
#include "PotiSubject.h"
//## operation subscribe(PotiObserver)
#include "PotiObserver.h"
//## package Default

//## class PotiSubject
PotiSubject::PotiSubject() {
}

PotiSubject::~PotiSubject() {
    cleanUpRelations();
}

void PotiSubject::notify() {
    //#[ operation notify()
        OMIterator<PotiObserver*> iter(itsPotiObserver);
        while (*iter){
            (*iter)->update(this);
            iter++;
        }
    //#]
}

void PotiSubject::subscribe(PotiObserver* potiObserver) {
    //#[ operation subscribe(PotiObserver)
    itsPotiObserver.add(potiObserver);
    //#]
}

OMIterator<PotiObserver*> PotiSubject::getItsPotiObserver() const {
    OMIterator<PotiObserver*> iter(itsPotiObserver);
    return iter;
}

void PotiSubject::addItsPotiObserver(PotiObserver* p_PotiObserver) {
    if(p_PotiObserver != NULL)
        {
            p_PotiObserver->_setItsPotiSubject(this);
        }
    _addItsPotiObserver(p_PotiObserver);
}

void PotiSubject::removeItsPotiObserver(PotiObserver* p_PotiObserver) {
    if(p_PotiObserver != NULL)
        {
            p_PotiObserver->__setItsPotiSubject(NULL);
        }
    _removeItsPotiObserver(p_PotiObserver);
}

void PotiSubject::clearItsPotiObserver() {
    OMIterator<PotiObserver*> iter(itsPotiObserver);
    while (*iter){
        (*iter)->_clearItsPotiSubject();
        iter++;
    }
    _clearItsPotiObserver();
}

void PotiSubject::cleanUpRelations() {
    {
        OMIterator<PotiObserver*> iter(itsPotiObserver);
        while (*iter){
            PotiSubject* p_PotiSubject = (*iter)->getItsPotiSubject();
            if(p_PotiSubject != NULL)
                {
                    (*iter)->__setItsPotiSubject(NULL);
                }
            iter++;
        }
        itsPotiObserver.removeAll();
    }
}

void PotiSubject::_addItsPotiObserver(PotiObserver* p_PotiObserver) {
    itsPotiObserver.add(p_PotiObserver);
}

void PotiSubject::_removeItsPotiObserver(PotiObserver* p_PotiObserver) {
    itsPotiObserver.remove(p_PotiObserver);
}

void PotiSubject::_clearItsPotiObserver() {
    itsPotiObserver.removeAll();
}

/*********************************************************************
	File Path	: MCB1700\Debug\PotiSubject.cpp
*********************************************************************/
