/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SYSTIMER.c
@brief      LPC17xx Hardware Abstraction Layer:
            Schnittstellen des Programm-Moduls SYSTIMER fuer LPC17xx

@details    Schnittstellen eines konfigurierbaren Softwaretimers unter Nutzung
            des Cortex-M Systicktimers im Interruptbetrieb
            
@author     N. Normann                                             
@version    1.2
@date       09. Januar 2014
*******************************************************************************/

#ifndef __SYSTIMER_H
#define __SYSTIMER_H

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

/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_SYSTEM
 * @{
 */
            
// Export-Schnittstellen *******************************************************
// Deklaration von Datentypen und modulglobalen Konstanten
//! @brief Typ fuer den PIN-Status
typedef enum 
{
  SYSTIMER_OK=     0,
  SYSTIMER_ERR=   -1
} SYSTIMERSTAT_T;


// Deklaration der oeffentlichen Funktionen ************************************                                                     				

/*!
********************************************************************************
@brief      Konstruktor: Systicktimer fuer Interruptbetrieb konfigurieren 
            und starten 
@param      tickQuantum Zeitquantum in Mikrosekunden
@return     Status 
*******************************************************************************/
extern SYSTIMERSTAT_T SYSTIMER_constr ( uint32_t tickQuantum );

/*!
********************************************************************************
@brief      Destruktor: Systicktimer freigeben und in Resetzustand schalten 
@return     Status 
*******************************************************************************/
extern SYSTIMERSTAT_T SYSTIMER_destr ( void );

/*!
********************************************************************************
@brief      Systicktimer auslesen
@return     Timerwert in SysTick-Einheiten 
*******************************************************************************/
extern uint64_t SYSTIMER_get ( void );

/*!
********************************************************************************
@brief      Systicktimereinheiten warten
@param      tickCounts Wartezeit in SysTick-Einheiten
@return     - 
*******************************************************************************/
extern void SYSTIMER_wait ( uint32_t tickCounts );

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
#endif  // __SYSTIMER_H 
