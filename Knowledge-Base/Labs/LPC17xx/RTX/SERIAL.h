/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SERIAL.h
@brief      LPC17xx Hardware Abstraction Layer:
            Schnittstellen zu UART-Routinen.
            4 Instanzen (UART0 .. UART3) sind moeglich.
            Version fuer RTX-Betriebsystem.
            Initialisierung muss im Privileged Betrieb erfolgen, 
            da NVIC konfiguriert wird.
            
@details    Schnittstellen zu Methoden fuer bis zu 4 UARTs
            - Initialisierung und Abschaltung eines UART
            - Oeffnen und Schliessen einer Schnittstelle 
            - Senden eines Zeichens
            - Empfangen eines Zeichens

            Multitaskingfaehige Version fuer RTX-Kernel.
					
@author     N. Normann                                             
@version    5.7
@date       30. Oktober 2013
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
} SERIALSEL_T;

//! @brief Typ fuer den Serial-Status
typedef enum 
{
  SERIAL_OK=  0,
  SERIAL_ERR= -1
} SERIALSTAT_T;

//! @brief Klasse fuer serielle Schnittstellen
typedef struct 
{
  SERIALSEL_T serialSel;
  // hier kann bei Bedarf ergaenzt werden, z.B. Baudrate, Datenformat ...
} SERIAL;

// Deklaration der oeffentlichen Funktionen                                                     				
/*! ****************************************************************************
@brief      Konstruktor: Eine serielle Schnittstelle zuweisen und konfigurieren.
            UART initialisieren mit 8Bits, no Parity, 1 Stop, 19200 bd
            Muss im Privileged Mode laufen (NVIC wird konfiguriert)
@param      me Pointer auf Objekt vom Typ SERIAL
@param      uart zugeordneter UART
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_constr ( SERIAL* me, SERIALSEL_T uart );

/*! ****************************************************************************
@brief      Destruktor: eine serielle Schnittstelle abschalten.
            Ausschalten des UART, Freigabe der Leitungen
            Muss im Privileged Mode laufen (NVIC wird konfiguriert)
@param      me Pointer auf Objekt vom Typ SERIAL
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_destr ( SERIAL* me );

      				
/*! ****************************************************************************
@brief      Serial Out oeffnen, fuer laufenden Prozess reservieren
@param      me Pointer auf Objekt vom Typ SERIAL
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_openOut ( SERIAL* me );

/*! ****************************************************************************
@brief      Zeichen senden ( Warten auf freien Sendepuffer durch RTX)
@param      me Pointer auf Objekt vom Typ SERIAL
@param      ch zu sendendes Zeichen
@return     gesendetes Zeichen
*******************************************************************************/
extern int SERIAL_sendOut ( SERIAL* me, int ch );

/*! ****************************************************************************
@brief      Serial Out schliessen, Reservierung freigeben
@param      me Pointer auf Objekt vom Typ SERIAL
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_closeOut ( SERIAL* me );

      				
/*! ****************************************************************************
@brief      Serial In oeffnen, fuer laufenden Prozess reservieren
@param      me Pointer auf Objekt vom Typ SERIAL
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_openIn ( SERIAL* me );

/*! ****************************************************************************
@brief      Zeichen empfangen (Warten durch RTX)
@param      me Pointer auf Objekt vom Typ SERIAL
@return     empfangenes Zeichen
*******************************************************************************/
extern int SERIAL_getIn ( SERIAL* me);

/*! ****************************************************************************
@brief      Serial In schliessen, Reservierung freigeben
@param      me Pointer auf Objekt vom Typ SERIAL
@return     Status SER_OK oder SER_ERR
*******************************************************************************/
extern SERIALSTAT_T SERIAL_closeIn ( SERIAL* me );
 

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
