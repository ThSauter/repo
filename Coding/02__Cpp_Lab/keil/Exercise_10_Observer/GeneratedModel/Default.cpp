/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Tue, 18, Apr 2017  
	File Path	: MCB1700\Debug\Default.cpp
*********************************************************************/

//## auto_generated
#include "Default.h"
//## classInstance itsDisplay
#include "Display.h"
//## classInstance itsLedBar
#include "LedBar.h"
//## classInstance itsPoti
#include "Poti.h"
//## auto_generated
#include "PotiObserver.h"
//## auto_generated
#include "PotiSubject.h"
//## package Default


//## classInstance itsPoti
Poti itsPoti;

//## classInstance itsLedBar
LedBar itsLedBar(&itsPoti);

//## classInstance itsDisplay
Display itsDisplay(&itsPoti);

void Default_initRelations() {
    {
        {
            itsPoti.setShouldDelete(false);
        }
        {
            itsLedBar.setShouldDelete(false);
        }
    }
}

bool Default_startBehavior() {
    bool done = true;
    done &= itsPoti.startBehavior();
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
