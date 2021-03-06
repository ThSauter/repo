/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: TestBuilder
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\TestBuilder.h
*********************************************************************/

#ifndef TestBuilder_H
#define TestBuilder_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "rl_fs.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "DefaultPkg.h"
//## classInstance itsClock
#include "Clock.h"
//## classInstance itsDisplay
#include "Display.h"
//## classInstance itsJoystick
#include "Joystick.h"
//## classInstance itsLed28
#include "Led.h"
//## classInstance itsLedBar
#include "LedBar.h"
//## classInstance itsRunningIndicatorLed
#include "RunningIndicatorLed.h"
//## classInstance itsSDCard
#include "SDCard.h"
//## package DefaultPkg

//## class TestBuilder
class TestBuilder : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    TestBuilder(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~TestBuilder();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Clock* getItsClock() const;
    
    //## auto_generated
    Display* getItsDisplay() const;
    
    //## auto_generated
    Joystick* getItsJoystick() const;
    
    //## auto_generated
    Led* getItsLed28() const;
    
    //## auto_generated
    Led* getItsLed29() const;
    
    //## auto_generated
    Led* getItsLed31() const;
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    RunningIndicatorLed* getItsRunningIndicatorLed() const;
    
    //## auto_generated
    SDCard* getItsSDCard() const;
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initRelations();

public :

    static uint16 ClassWSTMonitor_getTypeSize3();
    
    static uint16 ClassWSTMonitor_getTypeSize4();
    
    static uint16 ClassWSTMonitor_getTypeSize5();
    
    static uint16 ClassWSTMonitor_getTypeSize6();
    
    static uint16 ClassWSTMonitor_getTypeSize7();
    
    static uint16 ClassWSTMonitor_getTypeSize8();
    
    static uint16 ClassWSTMonitor_getTypeSize9();
    
    ////    Relations and components    ////

protected :

    Clock itsClock;		//## classInstance itsClock
    
    Display itsDisplay;		//## classInstance itsDisplay
    
    Joystick itsJoystick;		//## classInstance itsJoystick
    
    Led itsLed28;		//## classInstance itsLed28
    
    Led itsLed29;		//## classInstance itsLed29
    
    Led itsLed31;		//## classInstance itsLed31
    
    LedBar itsLedBar;		//## classInstance itsLedBar
    
    RunningIndicatorLed itsRunningIndicatorLed;		//## classInstance itsRunningIndicatorLed
    
    SDCard itsSDCard;		//## classInstance itsSDCard
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void setTask(WST_TSK* myTask, bool activeInstance);
    
    //## auto_generated
    virtual void destroy();
};

uint16 WSTMonitor_getTypeSize3();

uint16 WSTMonitor_getTypeSize4();

uint16 WSTMonitor_getTypeSize5();

uint16 WSTMonitor_getTypeSize6();

uint16 WSTMonitor_getTypeSize7();

uint16 WSTMonitor_getTypeSize8();

uint16 WSTMonitor_getTypeSize9();

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\TestBuilder.h
*********************************************************************/
