/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: TestBuilder
//!	Generated Date	: Tue, 23, May 2017  
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
            itsEthernetReceiver.setShouldDelete(false);
        }
        {
            itsLed31.setShouldDelete(false);
        }
        {
            itsLed28.setShouldDelete(false);
        }
        {
            itsEthernetTransmitter.setShouldDelete(false);
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
    }
    initRelations();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 105, (void*)&itsDisplay);
    
}

TestBuilder::~TestBuilder() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

Display* TestBuilder::getItsDisplay() const {
    return (Display*) &itsDisplay;
}

EthernetReceiver* TestBuilder::getItsEthernetReceiver() const {
    return (EthernetReceiver*) &itsEthernetReceiver;
}

EthernetTransmitter* TestBuilder::getItsEthernetTransmitter() const {
    return (EthernetTransmitter*) &itsEthernetTransmitter;
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

bool TestBuilder::startBehavior() {
    bool done = true;
    done &= itsDisplay.startBehavior();
    done &= itsEthernetReceiver.startBehavior();
    done &= itsEthernetTransmitter.startBehavior();
    done &= itsJoystick.startBehavior();
    done &= itsLed28.startBehavior();
    done &= itsLed29.startBehavior();
    done &= itsLed31.startBehavior();
    done &= itsLedBar.startBehavior();
    done &= itsRunningIndicatorLed.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void TestBuilder::initRelations() {
    itsRunningIndicatorLed.setItsLed(&itsLed31);
    itsEthernetReceiver.setItsLed(&itsLed29);
    itsEthernetTransmitter.setItsLed(&itsLed28);
    itsJoystick.setItsEthernetTransmitter(&itsEthernetTransmitter);
    itsEthernetReceiver.setItsLedBar(&itsLedBar);
    itsEthernetReceiver.setItsDisplay(&itsDisplay);
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize3() {
    return sizeof( Display );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize4() {
    return sizeof( EthernetReceiver );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize5() {
    return sizeof( EthernetTransmitter );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize6() {
    return sizeof( Joystick );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize7() {
    return sizeof( Led );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize8() {
    return sizeof( LedBar );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize9() {
    return sizeof( RunningIndicatorLed );
}

void TestBuilder::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLed31.setTask( myTask, false );
        itsLed28.setTask( myTask, false );
        itsLed29.setTask( myTask, false );
        itsLedBar.setTask( myTask, false );
        itsDisplay.setTask( myTask, false );
    }
}

void TestBuilder::destroy() {
    itsDisplay.destroy();
    itsEthernetReceiver.destroy();
    itsEthernetTransmitter.destroy();
    itsJoystick.destroy();
    itsLed28.destroy();
    itsLed29.destroy();
    itsLed31.destroy();
    itsLedBar.destroy();
    itsRunningIndicatorLed.destroy();
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
