/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       retarget.h
@brief      Driver fuer Standard I/O Ein-/Ausgabe:
            Umlenkung der Zeichenaus- und -eingaben der C-Library
            auf eine ausgewaehlte Hardware-Schnittstelle.
            Version fuer RTX-Betriebssystem 
            
@details    Implementiert fputc(), fgetc(), ferror() und _ttywrch()
            als stdio unter Nutzung des bei der Initialisierung gewuenschten
            I/O-Ports.
            Implementiert: PORT0: UART0, PORT1: UART1; PORT2: UART2,
                           PORT3: GLCD-Display
            Implementiert _sys_exit() bei Exeptions als Programmhaltepunkt.
					
@author     N. Normann                                             
@version    4.3
@date       30. Oktober 2013
*******************************************************************************/

#ifndef __RETARGET_H
#define __RETARGET_H

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
#include <stdio.h>            // C99 I/O Library

/** @addtogroup LPC17xx_Drivers
 * @{
 */
/** @addtogroup LPC17xx_RETARGET
 * @{
 */
            
// Export-Schnittstellen *******************************************************

//******************************************************************************
// Deklaration von Datentypen und modulglobalen Konstanten

//! @brief Typ fuer den StandardI/O-Status            
typedef enum
{
  RETARGET_OK = 0,
  RETARGET_ERR = -1
} RETARGETSTAT_T;

//! @brief Typ fuer vorhandene Hardware-Ports 
typedef enum
{
  PORT0 = 0, //!< implementiert fuer UART0
  PORT1 = 1, //!< implementiert fuer UART1
  PORT2 = 2, //!< implementiert fuer UART2
  PORT3 = 3, //!< implementiert fuer GLCD Display
  NONE = -1  //!< kein Port zugewiesen
} RETARGETPORT_T;

//! @brief Klasse fuer ein RETARGET-Objekt ( StdIO-Umleitung auf Hardwareports)            
typedef struct
{
  RETARGETPORT_T portIn;   //!< zugeordneter Hardware-Port fuer In
  RETARGETPORT_T portOut;  //!< zugeordneter Hardware-Port fuer Out
} RETARGET;


// Deklaration der oeffentlichen Funktionen                                                     				
/*!
********************************************************************************
@brief      Konstruktor: Eine IO-Umleitung konfigurieren
@param      me Pointer auf Objekt vom Typ RETARGET
@param      portIn  Eingabeport
@param      portOut Ausgabeport
@return     Status 
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_constr 
               ( RETARGET* me, RETARGETPORT_T portIn, RETARGETPORT_T portOut );

/*!
********************************************************************************
@brief      Destruktor: Eine IO-Umleitung abschalten
@param      me Pointer auf Objekt vom Typ RETARGET 
@return     Status 
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_destr ( RETARGET* me );

/*! ****************************************************************************
@brief      Eine vorhandene Portumleitung fuer StdIn oeffnen.
@param      me Pointer auf Objekt vom Typ RETARGET
@return     Status RETARGET_OK oder RETARGET_ERR
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_openIn ( RETARGET* me );

/*! ****************************************************************************
@brief      Eine vorhandene Portumleitung fuer StdIn schliessen.
@param      me Pointer auf Objekt vom Typ RETARGET
@return     Status RETARGET_OK oder RETARGET_ERR
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_closeIn ( RETARGET* me );

/*! ****************************************************************************
@brief      Eine vorhandene Portumleitung fuer StdOut oeffnen.
@param      me Pointer auf Objekt vom Typ RETARGET
@return     Status RETARGET_OK oder RETARGET_ERR
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_openOut ( RETARGET* me );

/*! ****************************************************************************
@brief      Eine vorhandene Portumleitung fuer StdOut schliessen.
@param      me Pointer auf Objekt vom Typ RETARGET
@return     Status RETARGET_OK oder RETARGET_ERR
*******************************************************************************/
extern RETARGETSTAT_T RETARGET_closeOut ( RETARGET* me );

// Funktionen der Standard C Library laut Keil uVision
extern int fputc(int ch, FILE *f);
extern int fgetc(FILE *f);
extern int ferror(FILE *f);
extern void _ttywrch(int ch);
extern void _sys_exit(int return_code);

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
      
#endif  // __RETARGET_H
