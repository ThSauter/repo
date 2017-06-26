/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: TestBuilder
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\TestBuilder.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "TestBuilder.h"
//## package DefaultPkg

//## class TestBuilder
TestBuilder::TestBuilder(WST_TSK* myTask) : itsLed31(2), itsLed28(0), itsLed29(1) {
    setTask( myTask, false );
    {
        {
            itsRunningIndicatorLed.setShouldDelete(false);
        }
        {
            itsLed31.setShouldDelete(false);
        }
        {
            itsLed28.setShouldDelete(false);
        }
        {
            itsLed29.setShouldDelete(false);
        }
        {
            itsJoystick.setShouldDelete(false);
        }
        {
            itsLedBar.setShouldDelete(false);
        }
        {
            itsDisplay.setShouldDelete(false);
        }
        {
            itsSDCard.setShouldDelete(false);
        }
    }
    initRelations();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 103, (void*)&itsClock);
    
}

TestBuilder::~TestBuilder() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

Clock* TestBuilder::getItsClock() const {
    return (Clock*) &itsClock;
}

Display* TestBuilder::getItsDisplay() const {
    return (Display*) &itsDisplay;
}

Joystick* TestBuilder::getItsJoystick() const {
    return (Joystick*) &itsJoystick;
}

Led* TestBuilder::getItsLed28() const {
    return (Led*) &itsLed28;
}

Led* TestBuilder::getItsLed29() const {
    return (Led*) &itsLed29;
}

Led* TestBuilder::getItsLed31() const {
    return (Led*) &itsLed31;
}

LedBar* TestBuilder::getItsLedBar() const {
    return (LedBar*) &itsLedBar;
}

RunningIndicatorLed* TestBuilder::getItsRunningIndicatorLed() const {
    return (RunningIndicatorLed*) &itsRunningIndicatorLed;
}

SDCard* TestBuilder::getItsSDCard() const {
    return (SDCard*) &itsSDCard;
}

bool TestBuilder::startBehavior() {
    bool done = true;
    done &= itsDisplay.startBehavior();
    done &= itsJoystick.startBehavior();
    done &= itsLed28.startBehavior();
    done &= itsLed29.startBehavior();
    done &= itsLed31.startBehavior();
    done &= itsLedBar.startBehavior();
    done &= itsRunningIndicatorLed.startBehavior();
    done &= itsSDCard.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void TestBuilder::initRelations() {
    itsRunningIndicatorLed.setItsLed(&itsLed31);
    itsJoystick.setItsLedBar(&itsLedBar);
    itsJoystick.setItsSDCard(&itsSDCard);
    itsSDCard.setItsDisplay(&itsDisplay);
    itsSDCard.setItsClock(&itsClock);
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize3() {
    return sizeof( Clock );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize4() {
    return sizeof( Display );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize5() {
    return sizeof( Joystick );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize6() {
    return sizeof( Led );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize7() {
    return sizeof( LedBar );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize8() {
    return sizeof( RunningIndicatorLed );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize9() {
    return sizeof( SDCard );
}

void TestBuilder::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLed31.setTask( myTask, false );
        itsLed28.setTask( myTask, false );
        itsLed29.setTask( myTask, false );
        itsLedBar.setTask( myTask, false );
        itsDisplay.setTask( myTask, false );
        itsSDCard.setTask( myTask, false );
    }
}

void TestBuilder::destroy() {
    itsDisplay.destroy();
    itsJoystick.destroy();
    itsLed28.destroy();
    itsLed29.destroy();
    itsLed31.destroy();
    itsLedBar.destroy();
    itsRunningIndicatorLed.destroy();
    itsSDCard.destroy();
    WST_FSM::destroy();
}

uint16 WSTMonitor_getTypeSize3() {
    return TestBuilder::ClassWSTMonitor_getTypeSize3( );
}

uint16 WSTMonitor_getTypeSize4() {
    return TestBuilder::ClassWSTMonitor_getTypeSize4( );
}

uint16 WSTMonitor_getTypeSize5() {
    return TestBuilder::ClassWSTMonitor_getTypeSize5( );
}

uint16 WSTMonitor_getTypeSize6() {
    return TestBuilder::ClassWSTMonitor_getTypeSize6( );
}

uint16 WSTMonitor_getTypeSize7() {
    return TestBuilder::ClassWSTMonitor_getTypeSize7( );
}

uint16 WSTMonitor_getTypeSize8() {
    return TestBuilder::ClassWSTMonitor_getTypeSize8( );
}

uint16 WSTMonitor_getTypeSize9() {
    return TestBuilder::ClassWSTMonitor_getTypeSize9( );
}

/*********************************************************************
	File Path	: MCB1700\Debug\TestBuilder.cpp
*********************************************************************/
