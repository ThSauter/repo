#ifdef __cplusplus
extern "C" {
#endif
#ifndef WSTMONITORIO_H
#define WSTMONITORIO_H


/**
* $Id: WSTMonitorIO.h 35670 2016-10-25 09:00:51Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO.h $
*
* Willert Software Tools - Monitor I/O
*
* Email: support@willert.de
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


#ifdef WST_MONITORIO_ADSP_BF53X_SERIAL
#include "WSTMonitorIO_ADSP_BF53x_SERIAL_IO.h"
#endif /* WST_MONITORIO_ADSP_BF53X_SERIAL */

#ifdef WST_SPARCv8_SERIAL_IO
#include "WSTMonitorIO_Gcc_SPARCv8.h"
#endif /* WST_SPARCv8_SERIAL_IO */

#ifdef WST_MONITORIO_KEIL_ARM7_RTA
#include "WSTMonitorIO_Keil_ARM7_RTA.h"
#endif /* WST_MONITORIO_KEIL_ARM7_RTA */

#ifdef WST_LPC21xx_SERIAL_IO
#include "WSTMonitorIO_Keil_ARM7_UART.h"
#endif /* WST_LPC21xx_SERIAL_IO */

#ifdef WST_MONITORIO_IAR_MSP430G2xx3_SERIAL_IO
#include "WSTMonitorIO_IAR_MSP430G_UART.h"
#endif /* WST_MONITORIO_IAR_MSP430G2xx3_SERIAL_IO */

#ifdef WST_MONITORIO_KEIL_ARM7_TRACE32
#include "WSTMonitorIO_Keil_ARM7_Trace32.h"
#endif /* WST_MONITORIO_KEIL_ARM7_TRACE32 */

#ifdef WST_CORTEX_ITM
#include "WSTMonitorIO_Keil_CortexM3_ITM.h"
#endif /* WST_CORTEX_ITM */

#ifdef WST_MONITORIO_CMSIS_UART
#include "WSTMonitorIO_CMSIS_UART.h"
#endif /* WST_MONITORIO_CMSIS_UART */

#ifdef WST_MONITORIO_KEIL_CORTEXM3_TRACE32
#include "WSTMonitorIO_Keil_CortexM3_Trace32.h"
#endif /* WST_MONITORIO_KEIL_CORTEXM3_TRACE32 */

#ifdef WST_LPC17xx_SERIAL_IO
#include "WSTMonitorIO_Keil_CortexM3_UART.h"
#endif /* WST_LPC17xx_SERIAL_IO */

#ifdef WST_WIN32_TCPIP_IO
#include "WSTMonitorIO_MS_PC_TCPIP.h"
#endif /* WST_WIN32_TCPIP_IO */

#ifdef WST_MONITORIO_PICOLO_UART
#include "WSTMonitorIO_Picolo_SCI.h"
#endif /* WST_MONITORIO_PICOLO_UART */

#ifdef WST_ISYSTEM_MEM
#include "WSTMonitorIO_iSystemMem.h"
#endif /* WST_ISYSTEM_MEM */

#ifdef WST_GHS_MEM
#include "WSTMonitorIO_GHS_Mem.h"
#endif /* WST_GHS_MEM */

#ifdef WST_LINUX_TCPIP
#include "WSTMonitorIO_LINUX_TCPIP.h"
#endif /* WST_LINUX_TCPIP */





#ifdef	WST_RXF


#define WST_ANIM_RUNNING_START_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


extern WST_MTX	monitorMutex;


#define WST_ANIM_RUNNING_STOP_SEC_DATA_NOINIT_UNSPECIFIED_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


#endif	/* WST_RXF */

#ifdef WST_MONITORIO_PACKETBASED


#define WST_ANIM_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


void	WSTMonitor_IO_Init( void );
uint8	WSTMonitor_IO_PutPacket( void *packet, uint16 length );
uint8	WSTMonitor_IO_GetByte(void);


	#define WST_ANIM_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


#endif	/* WST_MONITORIO_PACKETBASED */





#ifdef WST_MONITORIO_BYTEBASED


#define WST_ANIM_RUNNING_START_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */


void	 WSTMonitor_IO_Init( void );
void						WSTMonitor_IO_PutByte( uint8 c );
uint8			WSTMonitor_IO_GetByte( void );


#define WST_ANIM_RUNNING_STOP_SEC_CODE_FAST
/* @MISRA_19.1,19.15=OFF PD-0005: The design requires memory type macro inclusions to be located in multiple locations within files. */
#include "WSTMemoryTypes.h"
/* @MISRA_19.1,19.15=ON */

#endif	/* WST_MONITORIO_BYTEBASED */


#endif	/* WSTMONITORIO_H */

#ifdef __cplusplus
}
#endif






