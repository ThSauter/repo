/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       BINOUT.h
@brief      Driver fuer Binaer-Ausgabe
            Schnittstellen des Programm-Moduls BINOUT

@details    Schnittstelle des Programm-Moduls BINOUT
            Stellt Funktionen zur Ausgabe von Bitgruppen zur
            Verfuegung. 
            Die Gruppen koennen aus 1..32 Bits bestehen.
            Zur Taktung von angeschlossener Hardware kann das hoechstwertige
            Bit als Taktleitung konfiguriert werden, die waehrend eines neuen 
            Schreibvorgangs '1' und danach '0' wird. 
            Eine Instanz einer Bitgruppe existiert als Struktur
            vom Typ BINOUT_T, z.B. mit Namen myBits.
            Das Mapping auf GPIO-Hardwareports erfolgt durch Initialisierung
            der Struktur myBits (siehe unten) und
            anschliessenden Aufruf von initBINOUT ( BINOUT_T &myBITS ).
            Bei versuchter Doppelbelegung von Px-Portbits liefert initBINOUT
            den Fehler BITS_ERR, sonst BITS_OK.            
                        
             
@author     N. Normann                                             
@version    2.7
@date       07. November 2013
*******************************************************************************/

#ifndef __BINOUT_H
#define __BINOUT_H

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

//
#include "GPIOBIT.H"
            
/** @addtogroup LPC17xx_Drivers
 * @{
 */
/** @addtogroup LPC17xx_BINOUT
 * @{
 */

// Export-Schnittstellen *******************************************************
// Deklaration von Datentypen und modulglobalen Konstanten

//! @brief Typ fuer den Bit-Status
typedef enum 
{
  BITS_OK=     0,
  BITS_ERR=   -1
} BITSSTAT_T;

//! @brief Klasse fuer eine Bitgruppe von 1 bis 32 Bits
//         Bei Instantiierung Portleitungen pro Bit zuweisen
//         GPIO Portnummern 0 .. 4 
//         Bitnummer der einzelnen Ports 0..31
//         Beliebige Mischungen moeglich, 
//         Doppelbelegungen werden als Fehler erkannt
typedef struct
{
  uint8_t numBits;      //!< Anzahl von Bits ( 1 .. 32 )
  GPIOBIT ioBits[32];   //!< Zuordnung der Bits zu Portbits
  uint32_t binVal;      //!< Wert der Bitgruppe als vorzeichenlose Ganzzahl
  bool clockEnable;     //!< Taktausgabe auf hoechstwertigem Bit einschalten 
} BINOUT;                          
                                                   				
// Deklaration der oeffentlichen Funktionen                                                     				

/*!
********************************************************************************
@brief      Konstruktor: Initialisierung und Reservierung einer Bitgruppe,
            Zuordnung der Bits der Bitgruppe zu beliebigen 
            Ports und Pins des LPC17xx 
@param      me Pointer auf Objekt vom Typ BINOUT 
@param      numBits Anzahl der Bits der Bitgruppe
@param      pPorts Zeiger auf Array mit festen Portzuweisungen pro Bit
@param      pPins Zeiger auf Array mit festen Pinzuweisungen pro Bit
@param      clockPinActive Taktausgabe Ein/Aus
@return     Status
*******************************************************************************/
extern BITSSTAT_T BINOUT_constr (BINOUT* me, uint8_t numBits, 
          const uint8_t * pPorts, const uint8_t * pPins, bool clockPinActive );

/*!
********************************************************************************
@brief      Freigabe einer Bitgruppe, GPIO-Bits und HW-Pins freigeben 
@param      me Pointer auf Objekt vom Typ BINOUT
@return     Status
*******************************************************************************/
extern BITSSTAT_T BINOUT_destr (BINOUT* me);

/*!
********************************************************************************
@brief      Bitinhalt einer Bitgruppe ausgeben 
@param      me Pointer auf Objekt vom Typ BINOUT
@param      bitVal Binaerwert der Bitgruppe
@return     Status
*******************************************************************************/
extern BITSSTAT_T BINOUT_bitsOut (BINOUT* me, uint32_t bitVal);

/*!
********************************************************************************
@brief      Einschalten eines bestimmten Bits in einer Bitgruppe 
@param      me Pointer auf Objekt vom Typ BINOUT
@param      bitNum Bitnummer
@return     Status
*******************************************************************************/
extern BITSSTAT_T BINOUT_bitOn (BINOUT* me, unsigned int bitNum);

/*!
********************************************************************************
@brief      Ausschalten eines bestimmten Bits in einer Bitgruppe 
@param      me Pointer auf Objekt vom Typ BINOUT
@param      bitNum Bitnummer
@return     Status
*******************************************************************************/
extern BITSSTAT_T BINOUT_bitOff (BINOUT* me, unsigned int bitNum);


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
#endif  // __BINOUT_H
