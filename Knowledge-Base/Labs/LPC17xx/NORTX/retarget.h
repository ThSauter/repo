/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       retarget.h
@brief      Driver fuer Standard I/O Ein-/Ausgabe::
            Lenkt Zeichenaus- und -eingaben der C-Library
            auf eine serielle Schnittstelle. 
            
@details    Implementiert fputc(), fgetc(), ferror() und _ttywrch()
            als stdio unter Nutzung der bei der Initialisierung gewueschten
            seriellen Schnittstelle.
            Implementiert _sys_exit() bei Exeptions als Programmhaltepunkt.
					
@author     N. Normann                                             
@version    3.3
@date       30. April 2013
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
  STDIO_OK = 0,
  STDIO_ERR = -1
} STDIOSTAT_T;

//! @brief Typ fuer den StandardI/O Hardware-Port 
typedef enum
{
  PORT0 = 0,
  PORT1 = 1,
  NOSTDIO = -1
} STDIOPORT_T;

//! @brief Typ fuer StdIO-Objekt, nur eine Instanz moeglich            
typedef struct
{
  STDIOPORT_T portSel;          // zugeordneter Hardware-Port
  // hier Platz fuer weitere Eigenschaften, z.B. Baudrate.....
} STDIO_T;


// Deklaration der oeffentlichen Funktionen                                                     				
/*! ****************************************************************************
@brief      I/O-Port fuer StdIO reservieren und initialisieren.
            ( Non-reentrant, muss bei Multitasking geschuetzt werden )
@param      pStdio Pointer auf StdIO-Objekt (aktuell nur UART-Auswahl)
@return     Status STDIO_OK oder STDIO_ERR
*******************************************************************************/
extern STDIOSTAT_T initStdIO ( STDIO_T* pStdio );

/*! ****************************************************************************
@brief      I/O-Port von StdIO freigeben.
            ( Non-reentrant, muss bei Multitasking geschuetzt werden )
@param      pStdio Pointer auf StdIO-Objekt (aktuell nur UART-Auswahl)
@return     Status STDIO_OK oder STDIO_ERR
*******************************************************************************/
extern STDIOSTAT_T unInitStdIO ( STDIO_T* pStdio ); 

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
