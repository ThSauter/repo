#ifdef __cplusplus
extern "C" {
#endif
#ifndef WSTMONITORIO_KEIL_CORTEXM3_ITM_H 
#define WSTMONITORIO_KEIL_CORTEXM3_ITM_H

/**
 * Monitor interface header for ARM-Cortex devices with the ITM interface.
 * The file name contains "CortexM3", but the ITM interface is also available
 * on other ARM Cortex devices, e.g. Cortex-M4. 
 *
 * Willert Software Tools - RealTime eXecution Framework
 *
 * Email: support@willert.de
 *
 * $Id: WSTMonitorIO_Keil_CortexM3_ITM.h 35586 2016-10-17 14:55:47Z eroemer $
 * $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO_Keil_CortexM3_ITM.h $
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

#include "WSTProduct.h"
#include "WSTMonitorIO.h"
#ifdef WST_CORTEX_ITM


#define ITM_Port8    (*((volatile uint8  *)( 0xE0000000U ) ) )
#define ITM_Port32   (*((volatile uint32 *)( 0xE0000000U ) ) )

#define DEMCR1           (*((volatile uint32 *)(0xE000EDFCU)))
#define TRCENA1          0x01000000U


void WSTMonitorIO_receiveIncomingData( void );

#ifdef WST_MONITORIO_PACKETBASED
#error The selected WSTMonitorIO file does not support packet based communication. Please compile it with WST_MONITORIO_BYTEBASED defined.
#endif	/* WST_MONITORIO_PACKETBASED */

#endif	/* WST_CORTEX_ITM */

#endif /* WSTMONITORIO_KEIL_CORTEXM3_ITM_H */
#ifdef __cplusplus
}
#endif
