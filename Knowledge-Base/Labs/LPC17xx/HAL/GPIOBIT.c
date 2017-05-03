/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       GPIOBIT.c
@brief      LPC17xx Hardware Abstraction Layer:
            Implementierung des Programm-Moduls GPIOBIT fuer LPC17xx

@details    Implementierung des GPIO Hardware Abstraction Layers
           	fuer die Digital I/Os GPIO0, GPIO1, GPIO2, GPIO3 und GPIO4
            
@author     N. Normann                                             
@version    2.9
@date       26. Oktober 2013
*******************************************************************************/

// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false
// LPC17xx Hardware Abstraction Layer
#include "PINCONNECT.H"       // Pin Connect Block Hardware Abstraction Layer
// LPC17xx Devices
#include <LPC17xx.H>          // LPC17xx Peripherals

// Export-Schnittstelle ********************************************************
#include "GPIOBIT.h"             // eigene Schnittstelle


/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_GPIOBIT
 * @{
 */

// Definition interner modulglobaler Variabler *********************************
// Basisadressen der GPIO-Ports
LPC_GPIO_TypeDef * pGPIO[5] = 
                   { LPC_GPIO0,LPC_GPIO1,LPC_GPIO2,LPC_GPIO3,LPC_GPIO4};

// Interne Funktionsprototypen des Moduls **************************************
// keine

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

// Konstruktor: Port und Bitzuweisung und Reservierung
extern GPIOSTAT_T GPIOBIT_constr
               ( GPIOBIT* me, uint8_t port, uint8_t bitNo, GPIODIR_T bitDir )
{
  PINCONNECT pinForGPIO;

  // pruefen der Parameter
  if ( (port>4) || (bitNo>31) || (bitDir>1) ) return GPIO_ERR;

  // Pin fuer GPIO Bit reservieren
  // GPIO, Pull-Up angeschaltet, Opendrain ausgeschaltet
  if ( PINCONNECT_constr ( &pinForGPIO, port,bitNo,0,0,0 ) ) return GPIO_ERR;

  // Port mit Bitnummer ist reserviert und konfiguriert   
  me->bitPort.port = port;
  me->bitPort.bitNo = bitNo;
  me->bitDir = bitDir;
  
  pGPIO[port]->FIOCLR = (1UL<<bitNo);
  me->bitVal = false;
    
  // 1-Bit in GPIO->IODIR an Bitposition bitNo aendern in bitDir
  if ( me->bitDir == 1 )
  { 
    pGPIO[port]->FIODIR = pGPIO[port]->FIODIR | (1UL << bitNo );
  }
  else
  {
    pGPIO[port]->FIODIR = pGPIO[port]->FIODIR & ~(1UL << bitNo );    
  }
  return GPIO_OK; 
}

// Destruktor: Port und Bitzuweisung aufheben, Resetwerte eintragen
extern GPIOSTAT_T GPIOBIT_destr ( GPIOBIT* me )
{
  PINCONNECT pinGPIO;
  
  // Pin fuer GPIO Bit freigeben
  pinGPIO.port = me->bitPort.port;
  pinGPIO.bitNo = me->bitPort.bitNo;
  pinGPIO.funkt = 0; // GPIO
  pinGPIO.mode = 0;  // Pull-Up angeschaltet
  pinGPIO.openDrainMode = 0;  // Pull-Up angeschaltet
  if ( PINCONNECT_destr ( & pinGPIO ) ) return GPIO_ERR; 

  // Port und Bitzuweisung aufgehoben, Resetwerte eintragen
  pGPIO[me->bitPort.port]->FIODIR = 
            pGPIO[me->bitPort.port]->FIODIR & ~(1UL << me->bitPort.bitNo );  
  pGPIO[me->bitPort.port]->FIOCLR = (1UL<<me->bitPort.bitNo);
  me->bitPort.port = 0,
  me->bitPort.bitNo = 0;
  me->bitDir = GPIO_IN;
  me->bitVal = false;
  return GPIO_OK; 
}

// Ein GPIO-Bit auf '1' setzen
extern GPIOSTAT_T GPIOBIT_setBit ( GPIOBIT* me )
{
  pGPIO[me->bitPort.port]->FIOSET = (1UL<<me->bitPort.bitNo);
  me->bitVal = true;
  return GPIO_OK;
}

// Ein GPIO-Bit auf '0' setzen
extern GPIOSTAT_T GPIOBIT_clrBit ( GPIOBIT* me )
{
  pGPIO[me->bitPort.port]->FIOCLR = (1UL<<me->bitPort.bitNo);
  me->bitVal = false;
  return GPIO_OK;
}

// Ein GPIO-Bit lesen
extern bool GPIOBIT_getBit ( GPIOBIT* me )
{
  me->bitVal = pGPIO[me->bitPort.port]->FIOPIN & (1UL<<me->bitPort.bitNo);
  return me->bitVal;
}

// Einem GPIO-Bit  einen Bitwert zuweisen
extern GPIOSTAT_T GPIOBIT_writeBit ( GPIOBIT* me, bool bitVal )
{
  // 1-Bit in GPIO->PIN aendern in bitVal
  if ( bitVal)
  { 
    pGPIO[me->bitPort.port]->FIOSET = (1UL<<me->bitPort.bitNo);
  }
  else
  { 
    pGPIO[me->bitPort.port]->FIOCLR = (1UL<<me->bitPort.bitNo); 
  }
  me->bitVal = bitVal;
  return GPIO_OK;
}

// Funktion erkennt eine Aenderung an einem GPIO-Inputbit im 
// Vergleich zum vorhergehenden Funktionsaufruf
bool GPIOBIT_testBitChange ( GPIOBIT* me, int slope )
{
  static bool firstCall=true;    // Merker fuer ersten Aufruf
  static uint32_t savedValue[5]; // Merker fuer vorhergehende GPIO-Zustaende
  uint32_t portValue;
  bool portBitValue;

  if ( firstCall )
  {
    // kompletten Port lesen
    savedValue[me->bitPort.port] = pGPIO[me->bitPort.port]->FIOPIN; 
    firstCall = false;
    return false;
  }
  
  // Test Aenderung 0->1 am Eingang inPortBit
  portValue =   pGPIO[me->bitPort.port]->FIOPIN;          // Port lesen
  portBitValue = portValue & ( 1UL<<me->bitPort.bitNo); 
  if ( portBitValue == (bool)(savedValue[me->bitPort.port] 
                                            & (1UL<<me->bitPort.bitNo)) ) 
  {
    return false;               // alter Zustand am Eingang inPortBit 
  }
  else
  {
    // Aenderung am Eingang inPortBit
    savedValue[me->bitPort.port] = portValue;
    if (portBitValue)
    {
      // Bitwechsel 0->1 am Eingang inPortBit
      if ( slope >=0 )return true;
      return false;      
    }
    else
    {
      // Bitwechsel 1->0  am Eingang inPortBit
      if ( slope <=0 )return true;
      return false;
    }
  }
}

//******************************************************************************
// Private Funktionen des Moduls ***********************************************
// keine

/**
 * @}
 */
/**
 * @}
 */
