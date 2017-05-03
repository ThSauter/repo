/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: LedBar
//!	Generated Date	: Tue, 25, Apr 2017  
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "LedBar.h"
//## package Default

//## class LedBar
LedBar::LedBar(WST_TSK* myTask) {
    setTask( myTask, false );
    {
        for (int i = 0; i < 4; i++) 
            {
                itsLeds[i].setShouldDelete(false);
            }
        
    }
    //#[ operation LedBar()
    int i;                 
    
    // Assign the bit numbers to the leds
    for (i = 0; i < 4; i++)
    {
    	itsLeds[i].setBitNr(i + 2);
    }
    //#]
}

LedBar::~LedBar() {
}

void LedBar::offSingleLed(int ledNr) {
    //#[ operation offSingleLed(int)
    itsLeds[ledNr].off();
    //#]
}

void LedBar::onAllLeds() {
    //#[ operation onAllLeds()
    int i;
    
    for (i = 0; i < 4; i++)
    {
    	itsLeds[i].on();
    }
    //#]
}

void LedBar::onSingleLed(int ledNr) {
    //#[ operation onSingleLed(int)
    itsLeds[ledNr].on();
    //#]
}

void LedBar::toggleSingleLed(int ledNr) {
    //#[ operation toggleSingleLed(int)
    CGEN( &itsLeds[ledNr], evToggleLed());
    //#]
}

int LedBar::getItsLeds() const {
    int iter = 0;
    return iter;
}

bool LedBar::startBehavior() {
    bool done = true;
    {
        int iter = 0;
        while (iter < 4){
            done &= (((Led*)&itsLeds[iter]))->startBehavior();
            iter++;
        }
    }
    done &= WST_FSM::startBehavior();
    return done;
}

void LedBar::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        for (int i = 0; i < 4; i++) 
            {
                itsLeds[i].setTask( myTask, false );
            }
        
    }
}

void LedBar::destroy() {
    {
        int iter = 0;
        while (iter < 4){
            (((Led*)&itsLeds[iter]))->destroy();
            iter++;
        }
    }
    WST_FSM::destroy();
}

/*********************************************************************
	File Path	: MCB1700\Debug\LedBar.cpp
*********************************************************************/
