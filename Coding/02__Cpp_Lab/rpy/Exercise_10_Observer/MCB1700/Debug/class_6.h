/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: class_6
//!	Generated Date	: Tue, 18, Apr 2017  
	File Path	: MCB1700\Debug\class_6.h
*********************************************************************/

#ifndef class_6_H
#define class_6_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## class class_6
#include "PotiObserver.h"
//## operation class_6(Poti*)
class Poti;

//## auto_generated
class PotiSubject;

//## package Default

//## class class_6
class class_6 : public PotiObserver {
    ////    Constructors and destructors    ////
    
public :

    //## operation class_6(Poti*)
    class_6(Poti* poti);
    
    //## auto_generated
    class_6();
    
    //## auto_generated
    virtual ~class_6();
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\class_6.h
*********************************************************************/
