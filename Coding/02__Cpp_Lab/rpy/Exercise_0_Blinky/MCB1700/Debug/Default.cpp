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
//## classInstance itsLed
#include "Led.h"
//## package Default


//## classInstance itsLed
Led itsLed(2,100);

//## classInstance itsLed_1
Led itsLed_1(3,50);

void Default_initRelations() {
    {
        {
            itsLed.setShouldDelete(false);
        }
        {
            itsLed_1.setShouldDelete(false);
        }
    }
}

bool Default_startBehavior() {
    bool done = true;
    done &= itsLed.startBehavior();
    done &= itsLed_1.startBehavior();
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
