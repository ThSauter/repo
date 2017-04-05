#ifndef WSTTARGET_H
#define WSTTARGET_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* Target specific functionality is encapsulated in this module.
* 
* \ingroup Adaptation
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTTarget.h 33605 2016-01-28 09:35:30Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/CompilerAndTarget/Keil5_ARM/Source/Common/WSTTarget.h $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * RXF-Eval_Rpy-Cpp-ARM_V6.01 (2016-02-18).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/RXF-Eval_Rpy-Cpp-ARM_V6.01/ReleaseInfo.txt
 *
 *****************************************************************************/



/**
 * \brief A user defined hook which is called before event consumption.
 * \req{RXF-1619}
 */
#define WST_PRE_EVENT_CONSUMPTION_HOOK

/**
 * \brief A user defined hook which is called after event consumption.
 * \req{RXF-1620}
 */
#define WST_POST_EVENT_CONSUMPTION_HOOK


	
#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */


void 					WSTTarget_Init( void );
void 					WSTTarget_Cleanup( void );
extern void				SysTick_Handler( void );


#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */

/* For Keil RTX the interrupts need to be disabled the target specific way,
 * as RTX does not provide these functions.
 */
void					WSTTarget_enterCriticalRegion( void );
void					WSTTarget_exitCriticalRegion( void );
 

#define WST_RXF_RUNNING_START_SEC_CODE_SLOW
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */

void 					WSTTarget_sleep( WST_TimeUnit_t aTime );

#define WST_RXF_RUNNING_STOP_SEC_CODE_SLOW
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */

#ifdef __cplusplus
}
#endif

#endif  /* of WSTTARGET_H */
