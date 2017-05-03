/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       PINCONNECT.c
@brief      LPC17xx Hardware Abstraction Layer:
            Implementierung des Programm-Moduls PINCONNECT fuer LPC17xx           

@details    Implementierung des Pin Connect Block Hardware Abstraction Layers

            
@author     N. Normann                                             
@version    1.7
@date       28. Oktober 2013
*******************************************************************************/

// Import-Schnittstellen *******************************************************
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
// LPC17xx Hardware Abstraction Layer
// keine Nutzung
// LPC17xx Devices
#include <LPC17xx.H>          // Pin Connect Block des LPC17xx

// Export-Schnittstelle ********************************************************
#include "PINCONNECT.h"              // eigene Schnittstelle

/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_PINCONNECT
 * @{
 */

// Definitionen globaler Variabler *********************************************
// keine


// Definition interner modulglobaler Variabler *********************************
static uint32_t assignedPins[5]; // Bitmasken markieren belegte Px-Pins
// Pointer auf zugehoerige PINCON-Register
static volatile uint32_t *pPinsel[5]=
       {&LPC_PINCON->PINSEL0,&LPC_PINCON->PINSEL2,&LPC_PINCON->PINSEL4,
        &LPC_PINCON->PINSEL6,&LPC_PINCON->PINSEL8};
// Pointer auf PINMODE-Register
static volatile uint32_t *pMode[5]=
       {&LPC_PINCON->PINMODE0,&LPC_PINCON->PINMODE2,&LPC_PINCON->PINMODE4,
        &LPC_PINCON->PINMODE6,&LPC_PINCON->PINMODE8};
// Pointer auf PINMODE_OD-Register
static volatile uint32_t *pPinmode_OD[5]=
    {&LPC_PINCON->PINMODE_OD0,&LPC_PINCON->PINMODE_OD1,
    &LPC_PINCON->PINMODE_OD2,&LPC_PINCON->PINMODE_OD3,&LPC_PINCON->PINMODE_OD4};

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

// Konstruktor: Pinzuweisung und Reservierung
PINSTAT_T PINCONNECT_constr ( PINCONNECT* me, uint8_t port, 
           uint8_t bitNo, uint8_t funkt, uint8_t mode, uint8_t openDrainMode )
{
  volatile uint32_t *pPinselV;
  volatile uint32_t *pModeV;
  volatile uint32_t *pPinmode_ODV;
  
  // pruefen des Ports (P0 ... P4 erlaubt)
  if (port>4) return PIN_ERR;

  // pruefen der Bitnummer des Ports
  if (bitNo>31) return PIN_ERR;

  // pruefen von mode und openDrainMode
  if ((mode>3) || (me->openDrainMode>3)) return PIN_ERR;

  // Parameter o.k., Pin reservieren, aber nur falls unbenutzt 
  
  __disable_irq(); // kritischer Abschnitt fuer assignedPin
  if ( (assignedPins[port] & (1UL<<bitNo) ) )
  {
    __enable_irq();
    return PIN_ERR;
  }    
  assignedPins[port] |= (1UL<<bitNo);
  __enable_irq(); // Ende kritischer Abschnitt fuer assignedPin
  
  // Objekt initialisieren
  me->port = port;
  me->bitNo = bitNo;
  me->funkt = funkt;
  me->mode = mode;
  me->openDrainMode = openDrainMode;  
 
  // Ermittlung der zur Port- und Bitnummer gehoerenden Register 
  // PINSELx, PINMODEx und PINMODE_ODx
  pPinselV = pPinsel[me->port];
  pModeV = pMode[me->port];
  pPinmode_ODV = pPinmode_OD[me->port];

  if ( bitNo >= 16 )
  {
    bitNo = bitNo - 16;
    pPinselV++; // zweites Register nehmen, z.B. PINSEL1 statt PINSEL0
    pModeV++; // zweites Register nehmen, z.B. PINMODE1 statt PINMODE0
  }
 
  // Im passenden 32-Bit-Register die 2 Bits ab Bitposition me->bitNo
  // auf den Wert me->funkt setzen, alle anderen Bits unverandert
  // 32-Bitmaske mit 00 an Einfuegepos
  uint32_t bitMask = ~(3UL << (2*bitNo));
  uint32_t funktBits = me->funkt<<(2*bitNo);
  uint32_t modeBits = me->mode<<(2*bitNo);  
  *pPinselV = (*pPinselV & bitMask) | funktBits;
  *pModeV = (*pModeV & bitMask) | modeBits;    
  // Bit me->openDrainMode, an Bit me->bitNo einfuegen    
  if ( me->openDrainMode == 1 )
  { 
    *pPinmode_ODV = *pPinmode_ODV | (1UL << me->bitNo );
  }
  else
  {
    *pPinmode_ODV = *pPinmode_ODV & ~(1UL << me->bitNo );    
  }
 
  return PIN_OK; 
}

// Destruktor: Pinreset
PINSTAT_T PINCONNECT_destr (  PINCONNECT * me )
{
  volatile uint32_t *pPinselV;
  volatile uint32_t *pModeV;
  volatile uint32_t *pPinmode_ODV;
  
  // pruefen des Ports (P0 ... P4 erlaubt)
  if (me->port>4) return PIN_ERR;

  // pruefen der Bitnummer des Ports
  if (me->bitNo>31) return PIN_ERR;
 
  // Ermittlung der zur Port- und Bitnummer gehoerenden Register 
  // PINSELx, PINMODEx und PINMODE_ODx
  pPinselV = pPinsel[me->port];
  pModeV = pMode[me->port];
  pPinmode_ODV = pPinmode_OD[me->port];

  uint32_t bitNo = me->bitNo; 
  if ( bitNo >= 16 )
  {
    bitNo = bitNo - 16;
    pPinselV++; // zweites Register nehmen, z.B. PINSEL1 statt PINSEL0
    pModeV++; // zweites Register nehmen, z.B. PINMODE1 statt PINMODE0
  } 
  // Im passenden 32-Bit-Register die 2 Bits ab Bitposition me->bitNo
  // auf den Resetwert 00 setzen, alle anderen Bits unverandert
  // 32-Bitmaske mit 00 an Einfuegepos

  uint32_t bitMask = ~(3UL << (2*bitNo));
  *pPinselV = (*pPinselV & bitMask);
  *pModeV = (*pModeV & bitMask);
  *pPinmode_ODV = *pPinmode_ODV & ~(1UL << me->bitNo ); 
  
  // Resetwerte eintragen
  me->port = 0;
  me->bitNo = 0;
  me->funkt = 0;
  me->mode = 0;
  me->openDrainMode = 0;

  // Parameter o.k., Pin freigeben 
  __disable_irq(); // kritischer Abschnitt fuer assignedPin
  if ( !(assignedPins[me->port] & (1UL<<me->bitNo) ) )
  {
    __enable_irq();
    return PIN_ERR;
  }     
  assignedPins[me->port] &= ~(1UL<<me->bitNo);  
  __enable_irq(); // Ende kritischer Abschnitt fuer assignedPin
  
  return PIN_OK; 
} 

/**
 * @}
 */

/**
 * @}
 */
