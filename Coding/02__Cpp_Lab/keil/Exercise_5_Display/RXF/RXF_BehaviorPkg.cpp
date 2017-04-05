/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: RXF_BehaviorPkg
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\RXF_BehaviorPkg.cpp
*********************************************************************/

//## auto_generated
#include "RXF_BehaviorPkg.h"
//## auto_generated
#include "WST_EVT.h"
//## auto_generated
#include "WST_FSM.h"
//## auto_generated
#include "WST_MSQ.h"
//## auto_generated
#include "WST_MTX.h"
//## auto_generated
#include "WST_TMM.h"
//## auto_generated
#include "WST_TMR.h"
//## auto_generated
#include "WST_TSK.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg


sint16 WST_RXF_Main(sint16 argc, char_t* argv[]);


//## operation main()
int main( void ) {
    //#[ operation main()
    #ifndef	WST_COMPILER_INIT_AS_EMPTY_MACRO
    
    /* Initialize Compiler usage (for example heap) */
    
    WSTCompiler_Init();
    
    #endif
    
    /* Initialize Target interface */
    WSTTarget_Init();
    
    
	WST_RXF::initialize();

	WST_RXF_Main(0, NULL);
	
    
    /* Should never be reached. */		
    return 1;
    //#]
}

/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\RXF_BehaviorPkg.cpp
*********************************************************************/
