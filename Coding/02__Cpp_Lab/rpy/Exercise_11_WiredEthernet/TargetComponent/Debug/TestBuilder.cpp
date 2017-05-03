/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: TestBuilder
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\TestBuilder.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "TestBuilder.h"
//## package ExamplePkg

//## class TestBuilder
TestBuilder::TestBuilder(WST_TSK* myTask) : itsLED2(1), itsLED1(0), itsLED3(2) {
    setTask( myTask, false );
    {
        {
            itsSequentialController.setShouldDelete(false);
        }
        {
            itsActiveController.setShouldDelete(false);
        }
        {
            itsLED2.setShouldDelete(false);
        }
        {
            itsLED1.setShouldDelete(false);
        }
        {
            itsEthernetController.setShouldDelete(false);
        }
        {
            itsLED3.setShouldDelete(false);
        }
    }
    initRelations();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 104, (void*)&itsActiveController);
    
}

TestBuilder::~TestBuilder() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

ActiveController* TestBuilder::getItsActiveController() const {
    return (ActiveController*) &itsActiveController;
}

EthernetController* TestBuilder::getItsEthernetController() const {
    return (EthernetController*) &itsEthernetController;
}

LED* TestBuilder::getItsLED1() const {
    return (LED*) &itsLED1;
}

LED* TestBuilder::getItsLED2() const {
    return (LED*) &itsLED2;
}

LED* TestBuilder::getItsLED3() const {
    return (LED*) &itsLED3;
}

SequentialController* TestBuilder::getItsSequentialController() const {
    return (SequentialController*) &itsSequentialController;
}

bool TestBuilder::startBehavior() {
    bool done = true;
    done &= itsActiveController.startBehavior();
    done &= itsEthernetController.startBehavior();
    done &= itsLED1.startBehavior();
    done &= itsLED2.startBehavior();
    done &= itsLED3.startBehavior();
    done &= itsSequentialController.startBehavior();
    done &= WST_FSM::startBehavior();
    return done;
}

void TestBuilder::initRelations() {
    itsActiveController.setItsLED(&itsLED1);
    itsSequentialController.setItsLED(&itsLED2);
    itsEthernetController.setItsLED(&itsLED3);
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize3() {
    return sizeof( ActiveController );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize4() {
    return sizeof( EthernetController );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize5() {
    return sizeof( LED );
}

uint16 TestBuilder::ClassWSTMonitor_getTypeSize6() {
    return sizeof( SequentialController );
}

void TestBuilder::setTask(WST_TSK* myTask, bool activeInstance) {
    WST_FSM::setTask( myTask, activeInstance );
    {
        itsLED2.setTask( myTask, false );
        itsLED1.setTask( myTask, false );
        itsLED3.setTask( myTask, false );
    }
}

void TestBuilder::destroy() {
    itsActiveController.destroy();
    itsEthernetController.destroy();
    itsLED1.destroy();
    itsLED2.destroy();
    itsLED3.destroy();
    itsSequentialController.destroy();
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

/*********************************************************************
	File Path	: TargetComponent\Debug\TestBuilder.cpp
*********************************************************************/
