/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Tue, 18, Apr 2017  
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
//## classInstance itsDisplay
class Display;

//## classInstance itsLedBar
class LedBar;

//## classInstance itsPoti
class Poti;

//## auto_generated
class PotiObserver;

//## auto_generated
class PotiSubject;

//## package Default


//#[ ignore
// 12 bit ADC converter
#define ADC_FullRangeDeflection 4096-1
//#]

//## classInstance itsPoti
extern Poti itsPoti;

//## classInstance itsLedBar
extern LedBar itsLedBar;

//## classInstance itsDisplay
extern Display itsDisplay;

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
