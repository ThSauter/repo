/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm (Basis Keil uVision)
*******************************************************************************/

/*!
********************************************************************************
@file       retarget.c

@brief      Driver fuer Standard I/O Ein-/Ausgabe:
            Implementierung des Programm-Moduls retarget
            
@details    siehe Headerdatei
					
@author     N. Normann                                             
@version    3.3
@date       30. April 2013
*******************************************************************************/


// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false

#pragma import(__use_no_semihosting_swi)

// LPC17xx Devices
// kein Direktzugriff auf I/O-Devices

// LPC17xx Hardware Abstraction Layer
#include "SERIAL.H"           // UART Hardware Abstraction Layer

// Export-Schnittstelle ********************************************************
#include "retarget.h"         // eigene Schnittstelle

/** @addtogroup LPC17xx_Drivers
 * @{
 */
/** @addtogroup LPC17xx_RETARGET
 * @{
 */
 
// Definitionen globaler Variabler *********************************************
// fuer Standard Library- Funktionen laut Keil uVision
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

// Private Konstanten, Symbolische Konstanten und Makros ***********************
// keine

// Definition interner modulglobaler Variabler *********************************
//! ausgewaehltes UART fuer StdIO, Schutz gegen mehrfache Instanzierung
static STDIO_T stdioUsed = {NOSTDIO}; // frei bei Programmstart   

// Interne Funktionsprototypen des Moduls **************************************
static int sendchar (int ch);
static int getkey (void);

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

//! I/O-Port fuer StdIO reservieren und initialisieren
STDIOSTAT_T initStdIO (STDIO_T* pStdio)
{
  SERSTAT_T serStat;
  SERSEL_T serSel;

  // Fehler, wenn UART schon belegt  
  if ( stdioUsed.portSel != NOSTDIO ) return STDIO_ERR; 
  
  switch (pStdio->portSel)
  {  
    case PORT0:
      serSel = UART0;
      break;
    case PORT1:
      serSel = UART1;
      break;
    default:
      return STDIO_ERR;
  }
  serStat = initSerial (serSel); // geht nur gut, wenn UART frei ist
  if ( serStat == SER_OK )
  {
    stdioUsed = *pStdio;// stdioUsed markiert stdIO als belegt
    return STDIO_OK;
  }
  return STDIO_ERR;
} 

//! I/O-Port von StdIO freigeben
STDIOSTAT_T unInitStdIO (STDIO_T* pStdio)
{
  SERSTAT_T serStat;
  SERSEL_T serSel;
  if ( stdioUsed.portSel == NOSTDIO ) return STDIO_ERR; // Fehler, wenn frei

  switch (pStdio->portSel)
  {  
    case PORT0:
      serSel = UART0;
      break;
    case PORT1:
      serSel = UART1;
      break;
    default:
      return STDIO_ERR;
  }
  serStat = unInitSerial ( serSel); // geht nur gut, wenn UART belegt ist
  if ( serStat == SER_OK )
  {
    stdioUsed.portSel = NOSTDIO;//statische Variable stdioUart markiert stdIO als frei
    return STDIO_OK;
  }
  return STDIO_ERR;
} 


// Library- Funktionen laut Keil uVision
int fputc(int ch, FILE *f) {
  return (sendchar(ch));
}

int fgetc(FILE *f) {
  return (sendchar(getkey()));
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch) {
  sendchar (ch);
}

void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}

//******************************************************************************
// Private Funktionen des Moduls ***********************************************

//!* implementation of putchar (used by printf function to output data)
// Write character to Port
static int sendchar (int ch)  
{
  SERSEL_T serSel;
  switch (stdioUsed.portSel)
  {  
    case PORT0:
      serSel = UART0;
      break;
    case PORT1:
      serSel = UART1;
      break;
    default:
      return ch;       // Dummy-Ausgabe, falls kein UART zugeordnet
  }  
  return sendSerial ( serSel, ch ); // ch an UART durchreichen 
}

//! Read character from Port
static int getkey (void)  
{
  SERSEL_T serSel;
  switch (stdioUsed.portSel)
  {  
    case PORT0:
      serSel = UART0;
      break;
    case PORT1:
      serSel = UART1;
      break;
    default:
      return EOF;       // Zeichen EOF fuer Fehlerabbruch
  }  
  return getSerial ( serSel );    // Zeichen vom UART abholen
}

/**
 * @}
 */
/**
 * @}
 */
