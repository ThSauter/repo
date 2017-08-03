/**
* $Id: WSTMonitorIO_Keil_CortexM3_ITM.c 30489 2014-10-24 13:53:50Z mspieker $
* $URL: https://svn.willert.de/V6/trunk/Component/Extension/TD/Source/Common/WSTMonitorIO_Keil_CortexM3_ITM.c $
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

#ifdef WST_CORTEX_ITM

#ifdef WST_MONITORIO_BYTEBASED


volatile sint32 ITM_RxBuffer;        // 0x5AA55AA5 is handshake value

/**	init the ITM viewer */
void WSTMonitor_IO_Init( void )
{
	uint32 i;
	for(i=0U;i<100000U;i++)
	{
		;
	}
	ITM_RxBuffer = 0x5AA55AA5;	/* this value must be exactly 0x5AA55AA5 that the monitor recocnize that no data have received */
}



/**	function to send one byte over the ITM viewer to the host
	this function can be used withe uVision 4.** running on the host side */
void WSTMonitor_IO_PutByte (uint8 c)
{
/*lint -save -e* */ 	/* Should suppress MISRA Warnings for rule 11.1, but the macro replacement tool currently only supports temporarily disabling all checks. Reason: PD-0001: The design requires memory type macro inclusions to be located in multiple locations within files */
	if (DEMCR1 & TRCENA1) {
		while (ITM_Port32 == 0U ) /* while ITM FIFO is full */
		{ 
			; 
		}	
		ITM_Port8 = c;	/* send data to the host */
/*lint -restore */ 
	}
}

/**	function to receive one byte over the ITM viewer from the host
	this function can be used withe uVision 4.** running on the host side */
uint8 WSTMonitor_IO_GetByte( void )
{
	uint8 recChar;   

    while ( ITM_RxBuffer == 0x5AA55AA5 ){	/* wait until data has received from the host (!!blocking!!) */
			;
		}
    recChar = ((uint8)ITM_RxBuffer) & (uint8)0xffU;
    ITM_RxBuffer = 0x5AA55AA5;	/* reset public variable to default value */

    return( recChar );
}

/**	function to check if data is availebale from the DCC chanel sended from the host.
	This function is called from the Willert framework*/
void WSTMonitorIO_receiveIncomingData( void ){
	if(ITM_RxBuffer != 0x5AA55AA5){	//if the default value has changed new data is availeble from the ITM-Viewer...
		monitorNbCmd=1U;	/* set a flag that the monitore is able to recive a command */
	}
}




#endif	/* WST_MONITORIO_BYTEBASED */

#endif	/* of WST_CORTEX_ITM */

#endif  /* WST_TARGET_DEBUGGING_ENABLED */
