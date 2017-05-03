/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: TestBuilder
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\TestBuilder.h
*********************************************************************/

#ifndef TestBuilder_H
#define TestBuilder_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
#include "ExamplePkg.h"
//## classInstance itsActiveController
#include "ActiveController.h"
//## classInstance itsEthernetController
#include "EthernetController.h"
//## classInstance itsLED1
#include "LED.h"
//## classInstance itsSequentialController
#include "SequentialController.h"
//## package ExamplePkg

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
    ActiveController* getItsActiveController() const;
    
    //## auto_generated
    EthernetController* getItsEthernetController() const;
    
    //## auto_generated
    LED* getItsLED1() const;
    
    //## auto_generated
    LED* getItsLED2() const;
    
    //## auto_generated
    LED* getItsLED3() const;
    
    //## auto_generated
    SequentialController* getItsSequentialController() const;
    
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
    
    ////    Relations and components    ////

protected :

    ActiveController itsActiveController;		//## classInstance itsActiveController
    
    EthernetController itsEthernetController;		//## classInstance itsEthernetController
    
    LED itsLED1;		//## classInstance itsLED1
    
    LED itsLED2;		//## classInstance itsLED2
    
    LED itsLED3;		//## classInstance itsLED3
    
    SequentialController itsSequentialController;		//## classInstance itsSequentialController
    
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

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\TestBuilder.h
*********************************************************************/
