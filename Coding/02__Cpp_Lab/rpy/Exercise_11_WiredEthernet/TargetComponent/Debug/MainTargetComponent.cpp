/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: Debug
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\MainTargetComponent.cpp
*********************************************************************/

//## auto_generated
#include "MainTargetComponent.h"
//## auto_generated
#include "TestBuilder.h"

//#[ ignore
// WST_RXF.h include needed only at this point 
#define WST_CORRECT_HEADER_ORDER
#include "WST_RXF.h"
//#]


sint16 WST_RXF_Main(sint16 argc, char_t* argv[]) {
    sint16 status = 0;
    if(WST_RXF::initialize())
        {
            TestBuilder * p_TestBuilder;
            p_TestBuilder = new TestBuilder;
            p_TestBuilder->startBehavior();
            //#[ configuration TargetComponent::Debug 
            //#]
            WST_RXF::start();
            delete p_TestBuilder;
            status = 0;
        }
    else
        {
            status = 1;
        }
    return status;
}

/*********************************************************************
	File Path	: TargetComponent\Debug\MainTargetComponent.cpp
*********************************************************************/
