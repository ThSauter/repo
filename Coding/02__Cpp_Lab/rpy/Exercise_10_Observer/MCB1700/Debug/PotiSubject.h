/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: PotiSubject
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\PotiSubject.h
*********************************************************************/

#ifndef PotiSubject_H
#define PotiSubject_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## auto_generated
#include <oxf\omcollec.h>
//## operation subscribe(PotiObserver)
class PotiObserver;

//## package Default

//## class PotiSubject
class PotiSubject {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    PotiSubject();
    
    //## auto_generated
    virtual ~PotiSubject();
    
    ////    Operations    ////
    
    //## operation notify()
    void notify();
    
    //## operation subscribe(PotiObserver)
    void subscribe(PotiObserver* potiObserver);
    
    ////    Additional operations    ////
    
    //## auto_generated
    OMIterator<PotiObserver*> getItsPotiObserver() const;
    
    //## auto_generated
    void addItsPotiObserver(PotiObserver* p_PotiObserver);
    
    //## auto_generated
    void removeItsPotiObserver(PotiObserver* p_PotiObserver);
    
    //## auto_generated
    void clearItsPotiObserver();

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Relations and components    ////
    
    OMCollection<PotiObserver*> itsPotiObserver;		//## link itsPotiObserver
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void _addItsPotiObserver(PotiObserver* p_PotiObserver);
    
    //## auto_generated
    void _removeItsPotiObserver(PotiObserver* p_PotiObserver);
    
    //## auto_generated
    void _clearItsPotiObserver();
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\PotiSubject.h
*********************************************************************/
