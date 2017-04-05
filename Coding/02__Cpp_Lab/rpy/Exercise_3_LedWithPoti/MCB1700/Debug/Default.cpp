/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## classInstance itsLedBar
#include "LedBar.h"
//## package Default


//## classInstance itsLedBar
LedBar itsLedBar(2,1000);

void Default_initRelations() {
    {
        {
            itsLedBar.setShouldDelete(false);
        }
    }
}

bool Default_startBehavior() {
    bool done = true;
    done &= itsLedBar.startBehavior();
    return done;
}

//#[ ignore
Default_OMInitializer::Default_OMInitializer() {
    Default_initRelations();
    Default_startBehavior();
}

Default_OMInitializer::~Default_OMInitializer() {
}
//#]

/*********************************************************************
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/
