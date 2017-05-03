/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SYSTIMER.c
@brief      LPC17xx Hardware Abstraction Layer:
            Implementierung des Programm-Moduls SYSTIMER fuer LPC17xx

@details    Implementierung eines konfigurierbaren Softwaretimers unter Nutzung
            des Cortex-M Systicktimers im Interruptbetrieb.
            Statische Einzelinstanz (Singleton)
            
            Bei Compilierung mit HWDEBUG wird waehrend der Ausfuehrung der
            SysTick-ISR der Port DEBPORT = '1'.            
            
@author     N. Normann                                             
@version    1.2
@date       09. Januar 2014
*******************************************************************************/

// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false

// LPC17xx Devices
#include <LPC17xx.H>          // LPC17xx Peripherals
// LPC17xx Hardware Abstraction Layer
#include "GPIOBIT.h"          // nur benutzt bei HWDEBUG

// Export-Schnittstelle ********************************************************
#include "SYSTIMER.h"          // eigene Schnittstelle


/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_SYSTEM
 * @{
 */

// Definition interner modulglobaler Variabler *********************************

//! @brief Singleton fuer Systicksoftwaretimer
typedef struct 
{
  uint64_t tickTime;     //!< laufende Zeit in Systick-Einheiten
  uint32_t tickQuantum;  //!< Zeitquantum in Mikrosekunden
  bool runFlag;          //!< Bitwert 0: false, 1: true
} SYSTIMER;

// statische Einzelinstanz des Softwaretimers
static SYSTIMER sysTimer={0,0,0}; //!< Softwaretimer ist gestoppt bei Reset  

#ifdef HWDEBUG
  static const uint32_t DEBPORT[2] = {0,21};  //!< Port0.21 fuer Debug
  static GPIOBIT debPort; // !< Bitausgang fuer Debug
#endif // HWDEBUG

// Interne Funktionsprototypen des Moduls **************************************
// keine

//******************************************************************************
// Oeffentliche Funktionen des Moduls ******************************************

// Konstruktor: Port und Bitzuweisung und Reservierung
extern SYSTIMERSTAT_T SYSTIMER_constr ( uint32_t tickQuantum )
{
  uint32_t returnCode;
  if ( sysTimer.runFlag!=0 ) return SYSTIMER_ERR; // Softwaretimer laeuft schon
  
  // Instanz des Softwaretimers initialisieren
  sysTimer.tickQuantum = tickQuantum;
  sysTimer.tickTime = 0;
  sysTimer.runFlag = true;
  
  // Timerhardware und NVIC konfigurieren
  // CMSIS Prozedur zum Konfiguration des Systick-Timers und des 
  // NVIC Interrupt jede tickQuantum Mikrosekunden
  SystemCoreClockUpdate ( );
  returnCode=SysTick_Config((SystemCoreClock/1000000)*tickQuantum); 
   if (returnCode != 0)
   {
     SYSTIMER_destr ( ); // Fehler bei Konfiguration
     return SYSTIMER_ERR;
   }

   #ifdef HWDEBUG
   // Port fuer Debugmessungen initialisieren
	 if (GPIOBIT_constr (&debPort, DEBPORT[0], DEBPORT[1], GPIO_OUT))
                                          {  return SYSTIMER_ERR; }
	 #endif // HWDEBUG
   
  return SYSTIMER_OK; 
}

// Destruktor: Port und Bitzuweisung aufheben, Reset Systicktimer
extern SYSTIMERSTAT_T SYSTIMER_destr ( void )
{
  // Disable SysTick-Interrupt
  SysTick->CTRL = 0; // Reset des SysTick-Timers
  sysTimer.tickQuantum=0;
  sysTimer.tickTime=0;
  sysTimer.runFlag = 0; // Softwaretimer ist gestoppt
  return SYSTIMER_OK; 
}

// laufenden Systicktimer auslesen
extern uint64_t SYSTIMER_get ( void )
{
  return sysTimer.tickTime; 
}  

//******************************************************************************
//!  Systicktimereinheiten warten 
void SYSTIMER_wait ( uint32_t waitTime) 
{
  uint64_t endTime = SYSTIMER_get()+ waitTime;
  while ( SYSTIMER_get() < endTime ) {} // warten
}

//******************************************************************************
// Private Funktionen des Moduls ***********************************************

/*----------------------------------------------------------------------------
  SysTick Interrupt Handler (Cortex-M Standardname SysTick_Handler)
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void)
{
  // SysTicktimer Interrupt Request Flag wird automatisch geloescht,
  // keine Aktion noetig
 
  #ifdef HWDEBUG
  // Port fuer Debugmessungen setzen
  GPIOBIT_setBit (&debPort);
  #endif // HWDEBUG
  
  sysTimer.tickTime++; // SofwareTimerzeit hochzaehlen

  #ifdef HWDEBUG
  // Port fuer Debugmessungen setzen
  GPIOBIT_clrBit (&debPort);
  #endif // HWDEBUG
  
}


/**
 * @}
 */
/**
 * @}
 */
