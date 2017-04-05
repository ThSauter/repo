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
//## auto_generated
#include <stdio.h>
//## classInstance itsBoard
class Board;

//## auto_generated
class Display;

//## auto_generated
class LedBar;

//## auto_generated
class Poti;

//#[ ignore
#define evSwitchLed_Default_id 18601

#define evPotiValue_Default_id 18602
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

//## event evSwitchLed(int)
class evSwitchLed : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evSwitchLed(int p_ledNr);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    int ledNr;		//## auto_generated
};

//## event evPotiValue(int)
class evPotiValue : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evPotiValue(int p_potiValue);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    int potiValue;		//## auto_generated
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/
