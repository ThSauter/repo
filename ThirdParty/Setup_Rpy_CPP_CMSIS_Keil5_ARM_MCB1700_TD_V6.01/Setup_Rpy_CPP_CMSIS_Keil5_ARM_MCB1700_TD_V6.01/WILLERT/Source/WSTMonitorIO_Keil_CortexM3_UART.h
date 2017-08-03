#ifndef WSTMONITORIO_KEIL_CORTEXM3_UART_H 
#define WSTMONITORIO_KEIL_CORTEXM3_UART_H
#define WST_H
/**
 * Monitor interface header for ARM-Cortex devices of the NXP LPC family
 * and serial connunication.
 *
 * Willert Software Tools - RealTime eXecution Framework
 *
 * Email: support@willert.de
 *
 * $Id: WSTMonitorIO_Keil_CortexM3_UART.h 35586 2016-10-17 14:55:47Z eroemer $
 * $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO_Keil_CortexM3_UART.h $
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
