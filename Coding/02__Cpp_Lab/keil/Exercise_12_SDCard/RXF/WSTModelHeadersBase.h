/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Modelling\Rpy\Source\CPP\WSTModelHeadersBase.h
*********************************************************************/

#ifndef WST_H
#define WST_H

#define WST_CORRECT_HEADER_ORDER

#include "WSTForwardDecl.h"
#include "RxfConstants.h"			/**< constants needed to compile files of the RealTime eXecution Framework. 				*/
#include "WSTProduct.h"
#include "WSTCompiler.h"			/**< Compiler dependent prototypes and defines.									 			*/
#include "WSTRTOS.h"


class WST_TSK;
class WST_FSM;
class WST_MSQ;


#include "WST_MEM.h"
#include "WST_EVT.h"

#include "WST_MTX.h"
#include "WST_TMR.h"

#ifdef WST_TARGET_DEBUGGING_ENABLED
#include <string.h>					/**< for strcmp, strlen															*/
#include "WSTMonitor.h"
#endif /* WST_TARGET_DEBUGGING_ENABLED */

#include "WST_FSM.h"

#include "omstring.h"
#include "WSTModelling.h"

#undef WST_CORRECT_HEADER_ORDER

#endif /* WST_H */
/*********************************************************************
	File Path	: C:\V6\Component\Modelling\Rpy\Source\CPP\WSTModelHeadersBase.h
*********************************************************************/
