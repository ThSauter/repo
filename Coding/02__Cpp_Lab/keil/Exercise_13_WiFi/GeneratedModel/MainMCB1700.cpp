/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Debug
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\MainMCB1700.cpp
*********************************************************************/

//## auto_generated
#include "MainMCB1700.h"
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
            //#[ configuration MCB1700::Debug 
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
	File Path	: MCB1700\Debug\MainMCB1700.cpp
*********************************************************************/
