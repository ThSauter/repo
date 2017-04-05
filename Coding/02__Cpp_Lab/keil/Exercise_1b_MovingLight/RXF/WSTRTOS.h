#ifndef WSTRTOS_H
#define WSTRTOS_H

/**
* RTOS dependent prototypes and defines.
* This file is used, if no RTOS is part of the product.
*
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTRTOS.h 33605 2016-01-28 09:35:30Z eroemer $
* $URL: https://svn.willert.de/V6/trunk/Component/RTOS/OORTX/Source/Common/WSTRTOS.h $
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

#define	WST_RTOS_ERR_NONE					0u

#define WST_RXF_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */


extern WST_TimeUnit_t			WSTRTOS_getRxfTicks( void );
extern void				WSTRTOS_incrementRxfTicks( void );

#define WST_RXF_RUNNING_END_SEC_CODE_FAST
/* @MISRA_19.1=OFF PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1=ON */




#endif /* WSTRTOS_H */

