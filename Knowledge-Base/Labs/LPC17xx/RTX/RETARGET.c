/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm (Basis Keil uVision)
*******************************************************************************/

/*!
********************************************************************************
@file       retarget.c

@brief      Driver fuer Standard I/O Ein-/Ausgabe:
            Umlenkung der Zeichenaus- und -eingaben der C-Library
            auf eine ausgewaehlte Hardware-Schnittstelle.
            Version fuer RTX-Betriebssystem 
            
@details    Implementiert fputc(), fgetc(), ferror() und _ttywrch()
            als stdio unter Nutzung des bei der Initialisierung gewuenschten
            I/O-Ports.
            Implementiert: PORT0: UART0, PORT1: UART1; PORT2: UART2,
                           PORT3: GLCD-Display
            Implementiert _sys_exit() bei Exeptions als Programmhaltepunkt.
					
@author     N. Normann                                             
@version    4.3
@date       30. Oktober 2013
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
#include "GLCD.h"             // Schnittstelle zum LCD-Display

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
FILE __stdout; // Typ FILE ist identisch __FILE (typedef in stdio.h)
FILE __stdin;

// Private Konstanten, Symbolische Konstanten und Makros ***********************
// keine

// Definition interner modulglobaler Variabler *********************************
//! ausgewaehltes UART fuer StdIO, Schutz gegen mehrfache Instanzierung
static RETARGET stdioUsed = {NONE,NONE}; // frei bei Programmstart   

// Interne Funktionsprototypen des Moduls **************************************
static int sendChar (int ch);
static int getKey (void);

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

//!Konstruktor: Eine IO-Umleitung konfigurieren
extern RETARGETSTAT_T RETARGET_constr 
                 ( RETARGET* me, RETARGETPORT_T portIn, RETARGETPORT_T portOut )
{
  switch (portIn)
  {  
    case PORT0:
    case PORT1:
    case PORT2:
    case PORT3:
    case NONE:
    break;
    default:
      return RETARGET_ERR;
  }
  switch (portOut)
  {  
    case PORT0:
    case PORT1:
    case PORT2:
    case PORT3:
    case NONE:
    break;
    default:
      return RETARGET_ERR;
  }
  if ( portIn == PORT3)
  { me->portIn = NONE; } // GLCD hat nur Ausgabe
  else
  { me->portIn = portIn; }
  me->portOut = portOut;
  return RETARGET_OK;  
}

//Destruktor: Eine IO-Umleitung abschalten
extern RETARGETSTAT_T RETARGET_destr ( RETARGET* me )
{
  me->portIn = NONE;
  me->portOut = NONE;
  return RETARGET_OK;   
}

//! Eine IO-Umleitung fuer StdIn oeffnen
RETARGETSTAT_T RETARGET_openIn ( RETARGET* me )
{
  SERIAL serial;
  
  if ( stdioUsed.portIn != NONE ) return RETARGET_ERR; // schon offen
  
  switch (me->portIn)
  {  
    case PORT0:
      serial.serialSel = UART0;
      if ( SERIAL_openIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portIn = PORT0;
      return RETARGET_OK;    
    case PORT1:
      serial.serialSel = UART1;
      if ( SERIAL_openIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portIn = PORT1;
      return RETARGET_OK;
    case PORT2:
      serial.serialSel = UART2;
      if ( SERIAL_openIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portIn = PORT2;
      return RETARGET_OK;
    case PORT3: // GLCD ist nur Ausgabe
    default:
      return RETARGET_ERR;
  } 
}

//! Eine IO-Umleitung fuer StdIn schliessen
RETARGETSTAT_T RETARGET_closeIn ( RETARGET* me )
{
  SERIAL serial;
  if ( me->portIn == NONE ) return RETARGET_ERR; // schon zu
  
  switch (me->portIn)
  {  
    case PORT0:
      serial.serialSel = UART0;
      if ( SERIAL_closeIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;
    case PORT1:
      serial.serialSel = UART1;
      if ( SERIAL_closeIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;
    case PORT2:
      serial.serialSel = UART2;
      if ( SERIAL_closeIn (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;
    case PORT3: // GLCD ist nur Ausgabe
    default:
      return RETARGET_ERR;
  }
  stdioUsed.portIn = NONE;
  return RETARGET_OK;  
}
//! Eine IO-Umleitung fuer StdOut oeffnen
RETARGETSTAT_T RETARGET_openOut ( RETARGET* me )
{
  SERIAL serial;
  
  if ( stdioUsed.portOut != NONE ) return RETARGET_ERR; // schon offen
  
  switch (me->portOut)
  {  
    case PORT0:
      serial.serialSel = UART0;
      if ( SERIAL_openOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portOut = PORT0;
      return RETARGET_OK;    
    case PORT1:
      serial.serialSel = UART1;
      if ( SERIAL_openOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portOut = PORT1;
      return RETARGET_OK;
    case PORT2:
      serial.serialSel = UART2;
      if ( SERIAL_openOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      stdioUsed.portOut = PORT2;
      return RETARGET_OK;    
    case PORT3:
      stdioUsed.portOut = PORT3;
    return RETARGET_OK;
    default:
      return RETARGET_ERR;
  } 
}

//! Eine IO-Umleitung fuer StdOut schliessen
RETARGETSTAT_T RETARGET_closeOut ( RETARGET* me )
{
  SERIAL serial;
  if ( me->portOut == NONE ) return RETARGET_ERR; // schon zu
  
  switch (me->portOut)
  {  
    case PORT0:
      serial.serialSel = UART0;
      if ( SERIAL_closeOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;
    case PORT1:
      serial.serialSel = UART1;
      if ( SERIAL_closeOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;
    case PORT2:
      serial.serialSel = UART2;
      if ( SERIAL_closeOut (&serial) != SERIAL_OK ) return RETARGET_ERR;
      break;    
    case PORT3:
      break;
    default:
      return RETARGET_ERR;
  }
  stdioUsed.portOut = NONE;
  return RETARGET_OK;  
}

// Library- Funktionen fuer char IO laut Keil uVision
int fputc(int ch, FILE *f) {
  return (sendChar(ch));
}

int fgetc(FILE *f) {
  return (sendChar(getKey())); // wirklich mit Echo lesen?
}

int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch) {
  sendChar (ch);
}

void _sys_exit(int return_code) {
  while (1);    /* endless loop */
}

//******************************************************************************
// Private Funktionen des Moduls ***********************************************

//!* implementation of putchar (used by fputc function to output data)
// Write character to Port
static int sendChar (int ch)  
{
  SERIAL serial;
  
  switch (stdioUsed.portOut)
  {  
    case PORT0:
      serial.serialSel = UART0;
      break;
    case PORT1:
      serial.serialSel = UART1;
      break;
    case PORT2:
      serial.serialSel = UART2;
      break;    
    case PORT3:
      GLCD_PrintChar ( ch);
      return ch; 
    default:
      return ch; 
  }
  SERIAL_sendOut ( &serial, ch ); // ch an UART durchreichen
  return ch;   
}

//! Read character from Port
static int getKey (void)  
{
  SERIAL serial;

  switch (stdioUsed.portIn)
  {  
    case PORT0:
      serial.serialSel = UART0;
      return SERIAL_getIn ( &serial );    // Zeichen vom UART abholen
    case PORT1:
      serial.serialSel = UART1;
      return SERIAL_getIn ( &serial );    // Zeichen vom UART abholen
    case PORT2:
      serial.serialSel = UART2;
      return SERIAL_getIn ( &serial );    // Zeichen vom UART abholen
    default:
      return EOF;       // Zeichen EOF fuer Fehlerabbruch
  }  
}

/**
 * @}
 */
/**
 * @}
 */
