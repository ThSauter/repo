/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       PINCONNECT.h
@brief      LPC17xx Hardware Abstraction Layer:
            Reservierung eines Portpins (aus P0.x bis P4.x) mit
            Funktionszuordnung fuer die mehrfachbelegten Pins des LPC17xx

@details    Schnittstelle des Pin Connect Block Hardware Abstraction Layers.
            Die moeglichen Konfigurationen stehen in  den Tabellen des 
            LPC17xx User Manuals, Kapitel Pin Connect Block.
            
@author     N. Normann                                             
@version    1.7
@date       28. Oktober 2013
*******************************************************************************/

#ifndef __PINCONNECT_H
#define __PINCONNECT_H

#ifdef __cplusplus              // falls in C++ inkludiert
      namespace std {
          #define __CLIBNS std::
          extern "C" {
    #else
      #define __CLIBNS
    #endif  /* __cplusplus */

// Import-Schnittstellen *******************************************************
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false

/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_PINCONNECT
 * @{
 */

// Export-Schnittstellen *******************************************************
// Deklaration von Datentypen
//! @brief Typ fuer den PIN-Status
typedef enum 
{
  PIN_OK=     0,
  PIN_ERR=   -1
} PINSTAT_T;

//! @brief Klasse fuer die individuelle Pin-Funktionsauswahl und Konfiguration
typedef struct 
{
  uint8_t port:3;  //!< Portnummer 0 .. 4
  uint8_t bitNo:5; //!< Bitnummer des Ports 0..31
  uint8_t funkt:2; //!< IO-Funktion des Portbits laut LPX17xx UserManual (0..3)
  uint8_t mode:2;  //!< Modus des Portbits laut LPX17xx UserManual (0..3)
  uint8_t openDrainMode:1; //!<Treibermodus laut LPX17xx UserManual (0..1)
} PINCONNECT;

// Deklaration der oeffentlichen Funktionen ************************************                                                     				

/*!
********************************************************************************
@brief      Konstruktor: Einen bestimmten Px-Pin reservieren und konfigurieren.
@param      me Pointer auf Objekt vom Typ PINCONNECT
@param      port Portnummer 0 .. 4
@param      bitNo Bitnummer des Ports 0..31
@param      funkt IO-Funktion des Portbits
@param      mode Modus des Portbits
@param      openDrainMode Treibermodus
@return     Status 
*******************************************************************************/
extern PINSTAT_T PINCONNECT_constr ( PINCONNECT* me, uint8_t port, 
           uint8_t bitNo, uint8_t funkt, uint8_t mode, uint8_t openDrainMode );

/*!
********************************************************************************
@brief      Destruktor: Einen bestimmten Px-Pin freigeben 
            und in Resetzustand setzen
@param      me Pointer auf Objekt vom Typ PINCONNECT
@return     Status 
*******************************************************************************/
extern PINSTAT_T PINCONNECT_destr ( PINCONNECT* me );


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
#endif  // __PINCONNECT_H 
