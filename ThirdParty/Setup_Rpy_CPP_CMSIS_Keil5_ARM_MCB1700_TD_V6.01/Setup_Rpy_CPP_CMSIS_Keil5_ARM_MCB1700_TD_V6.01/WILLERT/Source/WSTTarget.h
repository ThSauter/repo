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
* $Id: WSTTarget.h 34418 2016-05-12 15:36:02Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/CompilerAndTarget/Keil5_ARM/Source/Common/WSTTarget.h $
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
 * Copyright (c) 2011, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01/ReleaseInfo.txt
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


/**
 * \brief  This define is set for Targets who can detect if the running context is an interrupt context.
 * \req{RXF-1622}
 */
#define WST_MSQ_PUT_WITH_ISR_DETECTION
	
#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


void 					WSTTarget_Init( void );
void 					WSTTarget_Cleanup( void );



#define WST_RXF_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

/* For Keil RTX the interrupts need to be disabled the target specific way,
 * as RTX does not provide these functions.
 */
void					WSTTarget_enterCriticalRegion( void );
void					WSTTarget_exitCriticalRegion( void );
WSTBoolean				WSTTarget_isInISR( void );



#ifdef __cplusplus
}
#endif

#endif  /* of WSTTARGET_H */
