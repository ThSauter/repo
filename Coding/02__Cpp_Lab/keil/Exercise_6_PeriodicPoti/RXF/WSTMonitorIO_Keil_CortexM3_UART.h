#ifndef WSTMONITORIO_KEIL_CORTEXM3_UART_H 
#define WSTMONITORIO_KEIL_CORTEXM3_UART_H
#define WST_H
/**
* Willert Software Tools - RealTime eXecution Framework
*
* Email: support@willert.de
*
* $Id: WSTMonitorIO_Keil_CortexM3_UART.h 31343 2015-02-14 10:10:49Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO_Keil_CortexM3_UART.h $
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
#include "wstproduct.h"
#include "WSTMonitorIO.h"
#include "WSTMonitor.h"

extern void UART1_IRQHandler( void );
#ifdef WST_LPC17xx_SERIAL_IO

#ifdef WST_MONITORIO_BYTEBASED

#define BUFFER_SIZE 50U
#define SEND_BUFFER_SIZE 150U

#endif	/* WST_MONITORIO_BYTEBASED */

#ifdef WST_MONITORIO_PACKETBASED
#error The selected WSTMonitorIO file does not support packet based communication. Please compile it with WST_MONITORIO_BYTEBASED defined.
#endif	/* WST_MONITORIO_PACKETBASED */

#endif	/* WST_LPC17xx_SERIAL_IO */

#endif /* WSTMONITORIO_KEIL_CORTEXM3_UART_H */
