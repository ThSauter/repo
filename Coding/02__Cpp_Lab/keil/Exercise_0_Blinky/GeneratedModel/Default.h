/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/

#ifndef Default_H
#define Default_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## classInstance itsLed
class Led;

//## package Default


//## classInstance itsLed
extern Led itsLed;

//## classInstance itsLed_1
extern Led itsLed_1;

//## auto_generated
void Default_initRelations();

//## auto_generated
bool Default_startBehavior();

//#[ ignore
class Default_OMInitializer {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    Default_OMInitializer();
    
    //## auto_generated
    virtual ~Default_OMInitializer();
};
//#]

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/
