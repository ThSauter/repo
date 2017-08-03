/**
* $Id: WSTMonitorIO_Keil_CortexM3_UART.c 31343 2015-02-14 10:10:49Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO_Keil_CortexM3_UART.c $
*
* Willert Software Tools - Target Interface Specific Monitor I/O
*
* Email: support@willert.de
*
**/


/*****************************************************************************
 *
 * This file belongs to the Willert Software Tools RXF Product:  
 * Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00 (2016-04-22).
 * Copyright (c) 2013, Willert Software Tools GmbH.
 *
 * For detailed information about this product see release info file:
 * C:/Program Files/Willert/Rpy_CPP_KeilRTX_Keil5_ARM_MCB1700_TD_V6.00/ReleaseInfo.txt
 *
 *****************************************************************************/


#include "WST.H"

#ifdef WST_TARGET_DEBUGGING_ENABLED

#ifdef WST_LPC17xx_SERIAL_IO

#ifdef WST_RXF_RXF

/* #error The selected WSTMonitorIO file does not support RTOS based frameworks yet. */
#endif /* WST_RXF_RXF */

/*****************************************************************************
 *
 * Serial Communication Routines for Philips LPC2100.
 * 
 * Copyright 2004-2005 KEIL Software, Inc.
 *
 *****************************************************************************/

#include <LPC17xx.H>


#ifdef WST_MONITORIO_BYTEBASED

uint16 readbuffer;
uint16 writebuffer;
uint8 MonitorBuffer[BUFFER_SIZE];

uint8 SendBuffer[SEND_BUFFER_SIZE];
uint16 sendreadbuffer;
uint16 sendwritebuffer;
uint8 last;
uint8 temp;
static WSTBoolean	tx_restart = WSTTRUE;




/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/


/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_START_SEC_CODE_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 


void UART1_IRQHandler( void );


/**	function to initialise the serial interface (Com1) for the CORTEX M3*/ 
void WSTMonitor_IO_Init( void )
{
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 10.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001:  */
	LPC_UART1_TypeDef *pUart = LPC_UART1;
/*lint -restore */ 
	last = 0U;
	readbuffer = 0U;
	writebuffer = 0U;

	sendreadbuffer = 0U;
	sendwritebuffer = 0U;
	
  LPC_PINCON->PINSEL4 |= 2U;             /* Pin P2.0 used as TXD1 (Com1) */
  LPC_PINCON->PINSEL4 |= 2U << 2U;             /* Pin P2.1 used as RXD1 (Com1) */
	
	NVIC_EnableIRQ(UART1_IRQn ); 
	
	pUart->IER	= 0U;             /* disable UART RDA (Receive Date Available) interrupts */
	
	pUart->LCR    = 0x83U;                          /* 8 bits, no Parity, 1 Stop bit  */
	pUart->DLL    = 9U;                             /* 115200 Baud Rate @ 25.0 MHZ PCLK */
	pUart->FDR    = 0x21U;                          /* FR 1,507, DIVADDVAL = 1, MULVAL = 2 */
	pUart->DLM    = 0U;                             /* High divisor latch = 0         */
	pUart->LCR    = 0x03U;                          /* DLAB = 0                       */
	
	pUart->IER = 3U;       /* enable UART1 RDA (Receive Date Available) interrupts */
	
	NVIC_SetPriority ( UART1_IRQn, 1U);
}

/** UART1 Interupt routine (name must be exact UART1_IRQHandler)*/
void UART1_IRQHandler(void){

	volatile uint32 dummy;
	LPC_UART1_TypeDef *pUart;
	volatile uint32	 IIR;
	
	pUart = LPC_UART1;
	
	/*
	 * Repeat while there is at least one interrupt source.
	 */
			 
	while ( ( (IIR = pUart->IIR) & 0x01U ) == 0U )	  /* Interrupt Identification Register */
	{
		switch( IIR & 0x0EU )
		{
			case 0x06U:		/* Receive Line Status */
				dummy = pUart->LSR;  /* Just clear the interrupt source */
				break;
	
			case 0x04U:		/* Receive Data Available */
				monitorNbCmd = 1U;
				MonitorBuffer[ writebuffer ] = pUart->RBR;		/* write data into the ringbuffer */
				writebuffer = ( writebuffer + 1U ) % BUFFER_SIZE;	/* increment writeindex of the ringbuffer */
						 
			 	dummy = pUart->LSR;  /* Just clear the interrupt source */
				break;

			case 0x02U:		/* Transmitter holding register empty Interrupt */
				
			if ( sendreadbuffer != sendwritebuffer )
			{
				pUart->THR = SendBuffer[sendreadbuffer];
				sendreadbuffer = (sendreadbuffer+1U)%SEND_BUFFER_SIZE;
				tx_restart = WSTFALSE;
			}
			else
			{
				sendreadbuffer=0U;
				sendwritebuffer=0U;
				tx_restart = WSTFALSE;
			}

			break;
	
			default:
				break;
		}
	}
	
	dummy = LPC_UART0->ICR;                              /* clear interrupts */ 


}


/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/


/**	function to write data to the host over the com1 interface*/
void WSTMonitor_IO_PutByte (uint8 c)
{
	LPC_UART1_TypeDef *pUart = LPC_UART1;
	if ( tx_restart )
	{
		tx_restart  = WSTFALSE;
		pUart->THR = c;
	}
	else
	{
#ifndef WST_MONITORIO_WAIT
		if( ( c == 7U ) && ( last == 8U ) ) {
			SendBuffer[ sendwritebuffer ] = c;
			sendwritebuffer = ( sendwritebuffer + 1U ) % SEND_BUFFER_SIZE;
			temp = (uint8) ( ( sendwritebuffer + 8U ) % SEND_BUFFER_SIZE );
		}
		else if((temp != 0U) && (temp==sendwritebuffer)) {
			temp = 0U;
			SendBuffer[sendwritebuffer] = c;
			sendwritebuffer = (sendwritebuffer + 1U);
			while(sendwritebuffer)
			{
				;
			}

		}
		else if( ( sendwritebuffer + 1U ) == SEND_BUFFER_SIZE) 
		{
			sendwritebuffer = 0U;
			sendreadbuffer = 0U;
			SendBuffer[sendwritebuffer] = 1U;
			sendwritebuffer = ( sendwritebuffer + 1U );
			SendBuffer[sendwritebuffer] = 0x12U;
			sendwritebuffer = ( sendwritebuffer + 1U );
			SendBuffer[sendwritebuffer] = 0x22U;
			sendwritebuffer = ( sendwritebuffer + 1U );
			SendBuffer[sendwritebuffer] = c;
			sendwritebuffer = ( sendwritebuffer + 1U );
		}
#endif /* WST_MONITORIO_WAIT */	 
#ifdef WST_MONITORIO_WAIT
		if( ( sendwritebuffer + 1U ) == SEND_BUFFER_SIZE) {

			while(sendwritebuffer);
			SendBuffer[sendwritebuffer] = c;
			sendwritebuffer = ( sendwritebuffer + 1U ) % SEND_BUFFER_SIZE;
		}
#endif /* WST_MONITORIO_WAIT */	 
		else {
			SendBuffer[sendwritebuffer] = c;
			sendwritebuffer = ( sendwritebuffer + 1U ) % SEND_BUFFER_SIZE;
		}
	}
	last = c;

}




/*------------------------------------------------------------------------------
------------------------------------------------------------------------------*/




/**	function to read data from the ringbuffer*/
uint8 WSTMonitor_IO_GetByte( void )
{
	uint8 tmp;
	while(readbuffer == writebuffer) /* wait until the readindex is on the same position as the writeindex of the ringbuffer */
	{
		;	
	}
	tmp=MonitorBuffer[ readbuffer ];	/* read value from the actuall bufferposition */
	readbuffer = ( readbuffer + 1U ) % BUFFER_SIZE ;	/* increment readindex of the ringbuffer */
	return tmp;	
}

/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 19.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
#define WST_ANIM_RUNNING_STOP_SEC_CODE_FAST
#include "WSTMemoryTypes.h"
/*lint -restore */ 


#endif	/* WST_MONITORIO_BYTEBASED */


#endif	/* of WST_LPC17xx_SERIAL_IO */

#endif  /* WST_TARGET_DEBUGGING_ENABLED */

