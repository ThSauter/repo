/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Wed, 29, Mar 2017  
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/

#ifndef Default_H
#define Default_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## classInstance itsBoard
class Board;

//## auto_generated
class LedBar;

//#[ ignore
#define switchLed_Default_id 18601
//#]

//## package Default


//## classInstance itsBoard
extern Board itsBoard;

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

//## event switchLed(int)
class switchLed : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    switchLed(int p_ledNr);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    int ledNr;		//## auto_generated
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/
