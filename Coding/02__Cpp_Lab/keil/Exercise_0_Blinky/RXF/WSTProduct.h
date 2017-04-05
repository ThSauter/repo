/**
 * \brief This file defines the components a product consists of.
 *
 * It was automatically generated on 2016-02-18, 14:02:00 for:
 *
 * == Product RXF-Eval_Rpy-Cpp-ARM ==
 * RXF ............... : Willert OORTX
 * IDE ............... : Keil uVision 5
 * Debugger .......... : Keil uVision
 * Modelling ......... : IBM Rational Rhapsody
 * Language .......... : C++
 * RTOS .............. : Willert OORTX
 * CompilerAndTarget . : Keil MDK-ARM for Cortex-M3
 * Board ............. : Keil MCB1700
 * Extension ......... : RXF Evaluation Software
 * Extension ......... : Embedded UML Target Debugger
 * 
 */

/* Component Willert OORTX of category RXF: */
#define WST_RXF_OORTX

/* Component Commonly Shared Files of category Shared: */
#define WST_SHARED

/* Component Keil uVision 5 of category IDE: */
#define WST_IDE_UVISION5

/* Component Keil uVision of category Debugger: */
#define WST_DEBUGGER_UVISION

/* Component IBM Rational Rhapsody of category Modelling: */
#define WST_MODELLING_RPY

/* Component C++ of category Language: */
#define WST_LANGUAGE_CPP

/* Component Willert OORTX of category RTOS: */
#define WST_RTOS_OORTX

/* Component Keil MDK-ARM for Cortex-M3 of category CompilerAndTarget: */
#define WST_COMPILERANDTARGET_KEIL5_ARM

/* Component Keil MCB1700 of category Board: */
#define WST_BOARD_MCB1700

/* Component RXF Evaluation Software of category Extension: */
#define WST_EXTENSION_EVAL

/* Component Embedded UML Target Debugger of category Extension: */
#define WST_EXTENSION_TD





/* -----------------------------------
 * Additional defines for this product
 * -----------------------------------
 */

/* Embedded UML Target Debugger Configuration
 *
 * $URL: https://svn.willert.de/V6/trunk/Component/Board/MCB1700/NotForRelease/AdditionalWSTProductDefines.h $
 * $Id: AdditionalWSTProductDefines.h 30489 2014-10-24 13:53:50Z mspieker $
 */

/* WST_MONITORIO_PACKETBASED or WST_MONITORIO_BYTEBASED,
 * for the LPC17xx board all available interface implementations are byte-based.
 */
#define WST_MONITORIO_BYTEBASED 

/* Available target interfaces:
 * WST_FDX_IO				Lauterbach Trace32 Debugger communication channel
 * WST_LPC17xx_SERIAL_IO	Serial (RS232) on-board COM1 communication channel 
 * WST_CORTEX_ITM			Keil uVision JTAG communication channel (DEFAULT)
 */
#define WST_CORTEX_ITM

/* Some target interface implementations require polling,
 * which means WST_MONITORIO_REQUIRES_POLLING has to be defined.
 * This is the case for WST_FDX_IO and WST_CORTEX_ITM.
 */
#define WST_MONITORIO_REQUIRES_POLLING


