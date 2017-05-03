/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SERIAL.h
@brief      LPC17xx Hardware Abstraction Layer:
            Schnittstellen zu UART-Routinen
            
@details    Schnittstellen zu Methoden fuer
            - Initialisierung und Abschaltung des UART,
            - Senden eines Zeichens
            - Empfangen eines Zeichens
					
@author     N. Normann                                             
@version    4.1
@date       30. April 2013
*******************************************************************************/

#ifndef __SERIAL_H
#define __SERIAL_H

#ifdef __cplusplus              // falls in C++ inkludiert
      namespace std {
          #define __CLIBNS std::
          extern "C" {
    #else
      #define __CLIBNS
    #endif  /* __cplusplus */

// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false


/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_SERIAL
 * @{
 */

// Export-Schnittstellen *******************************************************

//******************************************************************************
// Deklaration von Datentypen und modulglobalen Konstanten
            
//! @brief Typ fuer den UART-Auswahl
typedef enum 
{
  UART0 = 0,
  UART1 = 1,
  UART2 = 2,
  UART3 = 3,  
  NOUART = -1
} SERSEL_T;

//! @brief Typ fuer den Serial-Status
typedef enum 
{
  SER_OK=     0,
  SER_ERR=   -1
} SERSTAT_T;

// Deklaration der oeffentlichen Funktionen                                                     				
/*! ****************************************************************************
@brief      UART initialisieren mit 8Bits, no Parity, 1 Stop, 19200 bd
            ( Non-reentrant, muss bei Multitasking geschuetzt werden )
@param      serSel ausgewaehler UART
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERSTAT_T initSerial ( SERSEL_T serSel );

/*! ****************************************************************************
@brief      Zeichen senden (blockierendes Warten auf freien Sendepuffer!)
@param      serSel ausgewaehler UART
@param      ch zu sendendes Zeichen
@return     gesendetes Zeichen
*******************************************************************************/
extern int sendSerial ( SERSEL_T serSel, int ch );


/*! ****************************************************************************
@brief      Zeichen empfangen (blockierendes Warten!)
@param      serSel ausgewaehler UART
@return     empfangenes Zeichen
*******************************************************************************/
extern int getSerial ( SERSEL_T serSel);


/*! ****************************************************************************
@brief      Ausschalten des UART, Freigabe der Leitungen
            ( Non-reentrant, muss bei Multitasking geschuetzt werden )
@param      serSel ausgewaehler UART
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERSTAT_T unInitSerial ( SERSEL_T serSel ); 

#ifdef __cplusplus              // falls in C++ inkludiert
         }  /* extern "C" */
      }  /* namespace std */
#endif /* __cplusplus */

/**
 * @}
 */

/**
 * @}
 */

#endif  // __SERIAL_H
