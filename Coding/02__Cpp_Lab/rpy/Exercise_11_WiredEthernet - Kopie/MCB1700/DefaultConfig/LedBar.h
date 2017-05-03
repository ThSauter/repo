/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: DefaultConfig
	Model Element	: LedBar
//!	Generated Date	: Wed, 26, Apr 2017  
	File Path	: MCB1700\DefaultConfig\LedBar.h
*********************************************************************/

#ifndef LedBar_H
#define LedBar_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "Default.h"
//## link itsLeds
#include "Led.h"
//## package Default

//## class LedBar
class LedBar : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation LedBar()
    LedBar(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~LedBar();
    
    ////    Operations    ////
    
    //## operation offSingleLed(int)
    void offSingleLed(int ledNr);
    
    //## operation onAllLeds()
    void onAllLeds();
    
    //## operation onSingleLed(int)
    void onSingleLed(int ledNr);
    
    //## operation toggleSingleLed(int)
    void toggleSingleLed(int ledNr);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getItsLeds() const;
    
    //## auto_generated
    virtual bool startBehavior();
    
    ////    Relations and components    ////

protected :

    Led itsLeds[4];		//## link itsLeds
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void setTask(WST_TSK* myTask, bool activeInstance);
    
    //## auto_generated
    virtual void destroy();
};

#endif
/*********************************************************************
	File Path	: MCB1700\DefaultConfig\LedBar.h
*********************************************************************/
