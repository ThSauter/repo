/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       BINOUT.c
@brief      Driver fuer Binaer-Ausgabe
            Implementierung des Programm-Moduls BINOUT

@details    siehe Headerdatei
            
@author     N. Normann                                             
@version    2.7
@date       07. November 2013
*******************************************************************************/

// Export-Schnittstelle ********************************************************
#include "BINOUT.h"          // Headerdatei des eigenen Moduls

// Import-Schnittstellen *******************************************************
//C99
#include <inttypes.h>        // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>         // C99 Keywords bool, true, false

// LPC17xx Devices
// kein Direktzugriff auf Devices

/** @addtogroup LPC17xx_Drivers
 * @{
 */
/** @addtogroup LPC17xx_BINOUT
 * @{
 */

// Definitionen globaler Variabler *********************************************
// keine 
// Private Konstanten, Symbolische Konstanten und Makros ***********************
// keine
// Definition interner modulglobaler Variabler *********************************
// keine
// Interne Funktionsprototypen des Moduls **************************************
static bool clockOn (BINOUT* me);
static void clockOff (BINOUT* me);

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

//! Initialisierung und Reservierung einer Bitgruppe
//  Zuordnung der Bits einer Gruppe zu beliebigen GPIO0-Bits und HW-Pins 
extern BITSSTAT_T BINOUT_constr (BINOUT* me, uint8_t numBits, 
          const uint8_t * pPorts, const uint8_t * pPins, bool clockPinActive )
{
  // Bitanzahl pruefen
  if ( numBits > 32 ) return BITS_ERR;
  
  // Klasse initialisieren
  me->numBits = numBits;
  me->clockEnable = clockPinActive;
  
  // jedem Bit der Bitgruppe seinen GPIO-Port und seinen GPIO-Pin zuweisen
  for (int i=0; i<me->numBits; i++)
  {
    me->ioBits[i].bitPort.port = *(pPorts+i); // i-ter Port
    me->ioBits[i].bitPort.bitNo = *(pPins+i); // i-ter Pin
    if ( !(GPIOBIT_constr ( &me->ioBits[i], me->ioBits[i].bitPort.port, 
         me->ioBits[i].bitPort.bitNo, GPIO_OUT ))== GPIO_OK ) return BITS_ERR;
  }
  return BINOUT_bitsOut (me, 0); // Ports auf 0
}

//! Freigabe einer Bitgruppe, GPIO-Bits und HW-Pins freigeben 
extern BITSSTAT_T BINOUT_destr (BINOUT* me)
{
  if ( me->numBits > 32 ) return BITS_ERR;
  
  for (int i=0; i<me->numBits; i++)
  {
    if ( !(GPIOBIT_destr(&me->ioBits[i])==GPIO_OK)) return BITS_ERR;
    me->ioBits[i].bitPort.port = 0;
    me->ioBits[i].bitPort.bitNo = 0;
  }

  me->numBits=0;
  return BITS_OK;
}

//! Einschalten eines bestimmten Bits in einer Bitgruppe 
extern BITSSTAT_T BINOUT_bitOn (BINOUT* me, unsigned int bitNum)
{
  // Bitnummer pruefen
  if ( bitNum > 32 ) return BITS_ERR;
  
  // Bit Nummer bitNum an
  me->ioBits[bitNum].bitVal = true;  
  if ( !(GPIOBIT_setBit(&me->ioBits[bitNum])==GPIO_OK) ) return BITS_ERR;  
  me->binVal = me->binVal | (1UL<<bitNum);
  return BITS_OK;
}

//! Ausschalten eines bestimmten Bits in einer Bitgruppe 
extern BITSSTAT_T BINOUT_bitOff (BINOUT* me, unsigned int bitNum)
{
  // Bitnummer pruefen
  if ( bitNum > 32 ) return BITS_ERR;
  
  // Bit Nummer bitNum aus
  me->ioBits[bitNum].bitVal = true;   
  if ( !(GPIOBIT_clrBit(&me->ioBits[bitNum])==GPIO_OK) ) return BITS_ERR;  
  me->binVal = me->binVal & ~(1UL<<bitNum);
  return BITS_OK;
}

//! Bitinhalt einer Bitgruppe ausgeben, zu grosse Werte werden abgeschnitten 
extern BITSSTAT_T BINOUT_bitsOut (BINOUT* me, uint32_t bitVal)
{
  bool clockStat;
  uint8_t numBits = me->numBits;
  
  // Bits der Gruppe ausgeben
  clockStat = clockOn ( me);  // Clock auf '1', wenn konfiguriert
  if ( clockStat ) numBits--; // hoechstwertiges Bit ist durch Clock belegt

  // Bits der Gruppe schnell nacheinander einzeln schalten
  // gleichzeitig geht nicht, da verschiedene Ports beteiligt sein koennen  
  for (int i=0; i<numBits; i++)
  {
    bool bitBool = bitVal & (1UL<<i); // Einzelbit
    if ( !(GPIOBIT_writeBit(&me->ioBits[i],bitBool)==GPIO_OK) ) return BITS_ERR;
  }
  clockOff (me);
  me->binVal= bitVal; // Wert der Bitgruppe merken
  return BITS_OK;
}


//******************************************************************************
// Private Funktionen des Moduls ***********************************************
// Taktausgabe auf hoechstwertigem Bit einschalten, wenn me->clockEnable == TRUE 
static bool clockOn (BINOUT* me)
{
  if ( me->clockEnable)
  {
    // hoechstwertiges Bit '1', Bitgruppe wird veraendert
    BINOUT_bitOn ( me, (me->numBits)-1);
    return true;    
  }
  return false;  
}

// Taktausgabe auf hoechstwertigem Bit ausschalten, wenn me->clockEnable == TRUE 
static void clockOff (BINOUT* me)
{
  if ( me->clockEnable)
  {
    // hoechstwertiges Bit '0', Bitgruppe stabil
    BINOUT_bitOff ( me, (me->numBits)-1); 
  }    
}

/**
 * @}
 */
/**
 * @}
 */

