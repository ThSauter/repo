/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: PotiObserver
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\PotiObserver.h
*********************************************************************/

#ifndef PotiObserver_H
#define PotiObserver_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## operation update(PotiSubject)
class PotiSubject;

//## package Default

//## class PotiObserver
class PotiObserver {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    PotiObserver();
    
    //## auto_generated
    virtual ~PotiObserver();
    
    ////    Operations    ////
    
    //## operation update(PotiSubject)
    virtual void update(PotiSubject* potiSubject) = 0;
    
    ////    Additional operations    ////
    
    //## auto_generated
    PotiSubject* getItsPotiSubject() const;
    
    //## auto_generated
    void setItsPotiSubject(PotiSubject* p_PotiSubject);

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Relations and components    ////
    
    PotiSubject* itsPotiSubject;		//## link itsPotiSubject
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void __setItsPotiSubject(PotiSubject* p_PotiSubject);
    
    //## auto_generated
    void _setItsPotiSubject(PotiSubject* p_PotiSubject);
    
    //## auto_generated
    void _clearItsPotiSubject();
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\PotiObserver.h
*********************************************************************/
