/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       GPIOBIT.h
@brief      LPC17xx Hardware Abstraction Layer:
            Schnittstellen fuer Zugriff auf ausgewaehlte GPIO-Bits

@details    Schnittstelle des GPIO Hardware Abstraction Layers
            fuer Einzelbit Digital I/O auf GPIO0, GPIO1, GPIO2, GPIO3 und GPIO4
            
@author     N. Normann                                             
@version    2.9
@date       26. Oktober 2013
*******************************************************************************/

#ifndef __GPIOBIT_H
#define __GPIOBIT_H

#ifdef __cplusplus             // falls in C++ inkludiert
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
            
// IO-Pins des LPC17xx
#include "PINCONNECT.H"

/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_GPIOBIT
 * @{
 */
            
// Export-Schnittstellen *******************************************************
// Deklaration von Datentypen und modulglobalen Konstanten
//! @brief Typ fuer den PIN-Status
typedef enum 
{
  GPIO_OK=     0,
  GPIO_ERR=   -1
} GPIOSTAT_T;

//! @brief Typ fuer die PIN-Richtung
typedef enum 
{
  GPIO_IN= 0,
  GPIO_OUT= 1
} GPIODIR_T;

//! @brief Klasse fuer ein GPIO-Bit
typedef struct 
{
  PINCONNECT bitPort;     //!< Zuordnung eines Portpins (aus P0.x bis P4.x)
  GPIODIR_T bitDir;       //!< GPIO_IN: Eingang, GPIO_OUT: Ausgang
  bool bitVal;            //!< Bitwert 0: false, 1: true
} GPIOBIT;

// Deklaration der oeffentlichen Funktionen ************************************                                                     				

/*!
********************************************************************************
@brief      Konstruktor: Ein GPIO-Portbit reservieren und konfigurieren
@param      me Pointer auf Objekt vom Typ GPIOBIT
@param      port GPIO Portnummer 0 .. 4
@param      bitNo Bitnummer des Ports 0..31
@param      bitDir GPIO_IN: Eingang, GPIO_OUT: Ausgang
@return     Status 
*******************************************************************************/
extern GPIOSTAT_T GPIOBIT_constr 
              ( GPIOBIT* me, uint8_t port, uint8_t bitNo, GPIODIR_T bitDir );

/*!
********************************************************************************
@brief      Destruktor: Ein GPIO-Portbit freigeben und in Resetzustand schalten
@param      me Pointer auf Objekt vom Typ GPIOBIT 
@return     Status 
*******************************************************************************/
extern GPIOSTAT_T GPIOBIT_destr ( GPIOBIT* me );

/*!
********************************************************************************
@brief      Ein einzelnes GPIO-Portbit auf '1' setzen
@param      me Pointer auf Objekt vom Typ GPIOBIT
@return     Status 
*******************************************************************************/
extern GPIOSTAT_T GPIOBIT_setBit ( GPIOBIT* me );

/*!
********************************************************************************
@brief      Ein einzelnes GPIO-Portbit auf '0' setzen
@param      me Pointer auf Objekt vom Typ GPIOBIT
@return     Status 
*******************************************************************************/
extern GPIOSTAT_T GPIOBIT_clrBit ( GPIOBIT* me );

/*!
********************************************************************************
@brief      Ein einzelnes GPIO-Portbit lesen
@param      me Pointer auf Objekt vom Typ GPIOBIT
@return     Bitwert (1 = true, 0 = false ) 
*******************************************************************************/
extern bool GPIOBIT_getBit ( GPIOBIT* me );

/*!
********************************************************************************
@brief      Einem einzelnen GPIO-Bit einen Bitwert zuweisen
@param      me Pointer auf Objekt vom Typ GPIOBIT
@param      bitVal (1 = true, 0 = false )  
@return     Status 
*******************************************************************************/
extern GPIOSTAT_T GPIOBIT_writeBit ( GPIOBIT* me , bool bitVal );

/*!
********************************************************************************
@brief      Funktion erkennt eine Aenderung an einem Inputbit im 
            Vergleich zum vorhergehenden Aufruf
@param      me Pointer auf Objekt vom Typ GPIOBIT
@param      slope Flankenerkennung -1: neg., +1: pos., 0: beide Flanken
@return     false - keine Aenderung
            true - Aenderung
*******************************************************************************/
extern bool GPIOBIT_testBitChange ( GPIOBIT* me, int slope );

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
#endif  // __GPIOBIT_H 
