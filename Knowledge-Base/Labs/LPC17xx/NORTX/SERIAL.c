/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SERIAL.c
@brief      LPC17xx Hardware Abstraction Layer:
            Implementierung der UART-Routinen
            
@details    siehe Headerdatei
            Hardwareabhaengige Implementierung fuer  feste Baudrate 19200Bd
            bei 25MHz UART Clock
            
@author     N. Normann                                             
@version    4.2
@date       8. Mai 2013
*******************************************************************************/

// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false
// LPC17xx Devices
#include <LPC17xx.h>

// LPC17xx Hardware Abstraction Layer
#include "PINCONNECT.H"       // Pin Connect Block Hardware Abstraction Layer

/** @addtogroup LPC17xx_HAL
 * @{
 */
/** @addtogroup LPC17xx_SERIAL
 * @{
 */

// Export-Schnittstelle ********************************************************
#include "SERIAL.h"            // eigene Schnittstelle

// Private Konstanten, Symbolische Konstanten und Makros ***********************
// Bits der UART-Register (nicht vollstaendig) *********************************
// FIFO Control Reg FCR Bits
//static const uint8_t  RXTRIG =       (1U<<7); // Rx Trigger
//static const uint8_t  TXFIFORESET  = (1U<<2); // TX FIFO Reset
//static const uint8_t  RXFIFORESET  = (1U<<1); // RX FIFO Reset
static const uint8_t  FIFOENABLE   = (1U<<0); // FIFO Enable
static const uint8_t  FIFOTRIGLEV  = (3U<<6); // FIFO Trigger Level3 (14 Bytes)
// Line Control Reg LCR Bits
static const uint8_t  DLAB =         (1U<<7); // DLAB Bit
//static const uint8_t  SETBREAK =     (1U<<6); // Set Break Bit
//static const uint8_t  STICKPAR =     (1U<<5); // Stick Parity Bit
//static const uint8_t  EVENPAR =      (1U<<4); // Even Parity Select Bit
//tatic const uint8_t  PARENABLE =    (1U<<3); // Parity Enable Bit
//static const uint8_t  NUMSTOPBITS =  (1U<<2); // Number of Stop Bits
static const uint8_t  BITS8 =              3; // 8 Datenbits
//static const uint8_t  BITS7 =              2; // 7 Datenbits
//static const uint8_t  BITS6 =              1; // 6 Datenbits
//static const uint8_t  BITS5 =              0; // 5 Datenbits

// Line Status Register LSR Bits
//static const uint8_t  RXFIFOERR =    (1U<<7); // RXFIFO Error
//static const uint8_t  TEMPT =        (1U<<6); // Transmitter Empty
static const uint8_t  THRE =         (1U<<5); // Transmit Holding Reg Empty
//static const uint8_t  BI =           (1U<<4); // Break Interrupt
//static const uint8_t  FE =           (1U<<3); // Framing Error
//static const uint8_t  PE =           (1U<<2); // Parity Error
//static const uint8_t  OE =           (1U<<1); // Overrun Error
static const uint8_t  RDR =          (1U<<0); // Receiver Data Ready

// Baudrate
static const uint8_t  DLLSET = 81;       //!< fuer 19290 Bd bei 25MHz UART-Clock
static const uint8_t  DLMSET =  0;

static const unsigned char EOT = 0x04;   // End-Of-Transmission

// Definition interner modulglobaler Variabler *********************************
//! Pointer auf ausgewaehlte UARTs,, Schutz gegen mehrfache Instanziierung
static LPC_UART_TypeDef* pAssignedUart[4] = {0,0,0,0};

// UART initialisieren mit 8Bits, no Parity, 1 Stop, 19200 bd
SERSTAT_T initSerial ( SERSEL_T serSel)  
{
  PINCONNECT_T txdLine;
  PINCONNECT_T rxdLine;  
  LPC_UART_TypeDef* uart;

  if ( pAssignedUart[serSel] != 0 ) return SER_ERR; // schon anderes UART aktiv
  
  switch (serSel)
  {
    case UART0:
      txdLine.port = 0; // UART0 TxD an P0.2
      txdLine.pin = 2;
      txdLine.funkt = 1; // TxD
      rxdLine.port = 0; // UART0 RxD an P0.3
      rxdLine.pin = 3;
      rxdLine.funkt = 1; // RxD
      uart = LPC_UART0;
      break;    
    case UART1:
      txdLine.port = 0; // UART1 TxD an P0.15
      txdLine.pin = 15;
      txdLine.funkt = 1; // TxD
      rxdLine.port = 0; // UART1 RxD an P0.16
      rxdLine.pin = 16;
      rxdLine.funkt = 1; // RxD
      uart = (LPC_UART_TypeDef*) LPC_UART1;
      break;    
    case UART2:
      txdLine.port = 0; // UART2 TxD an P0.10
      txdLine.pin = 10;
      txdLine.funkt = 1; // TxD
      rxdLine.port = 0; // UART2 RxD an P0.11
      rxdLine.pin = 11;
      rxdLine.funkt = 1; // RxD
      uart = LPC_UART2;
      break;
    case UART3:
      txdLine.port = 0; // UART3 TxD an P0.0
      txdLine.pin =  0;
      txdLine.funkt = 2; // TxD
      rxdLine.port = 0; // UART3 RxD an P0.1
      rxdLine.pin =  1;
      rxdLine.funkt = 2; // RxD
      uart = LPC_UART3;
      break;
    default:
      return SER_ERR;
  }
  // Pins fuer UARTx reservieren
  txdLine.mode = 0;  // Pull-Up angeschaltet
  txdLine.openDrainMode = 0;  // Opendrain ausgeschaltet 
  rxdLine.mode = 0;           // Pull-Up angeschaltet
  rxdLine.openDrainMode = 0;  // Opendrain ausgeschaltet   
  if ( initPin ( &txdLine ) ) return SER_ERR;  
  if ( initPin ( &rxdLine ) ) return SER_ERR; 

  uart->LCR = DLAB | BITS8;      // DLAB=1, 8 bits, no Parity, 1 Stop bit
  uart->DLL = DLLSET;            // Baud Rate setzen
  uart->DLM = DLMSET; 
  uart->LCR = uart->LCR &~DLAB;  // DLAB = 0
  uart->FCR = FIFOENABLE | FIFOTRIGLEV; // FIFOs Enable und Reset
  pAssignedUart[serSel] = uart;  // Pointer auf ausgewaehlten UART merken
  return SER_OK;
}

// Ausschalten des UART, Freigabe der Leitungen
SERSTAT_T unInitSerial ( SERSEL_T serSel ) 
{
  PINCONNECT_T txdLine;
  PINCONNECT_T rxdLine;  
  LPC_UART_TypeDef* uart;
  
  switch (serSel)
  {
    case UART0:
      txdLine.port = 0;
      txdLine.pin = 2;
      rxdLine.port = 0;
      rxdLine.pin = 3;
      uart = LPC_UART0;
      break;    
    case UART1:
      txdLine.port = 0;
      txdLine.pin = 15;
      rxdLine.port = 0;
      rxdLine.pin = 16;
      uart = (LPC_UART_TypeDef*) LPC_UART1;
      break;
    case UART2:
      txdLine.port = 0;
      txdLine.pin = 10;
      rxdLine.port = 0;
      rxdLine.pin = 11;
      uart = LPC_UART2;
      break;
    case UART3:
      txdLine.port = 0;
      txdLine.pin =  0;
      rxdLine.port = 0;
      rxdLine.pin =  1;
      uart = LPC_UART3;    
    default:
      return SER_ERR;
  }
  // RxD und TxD-Leitungen abklemmen (Reset-Zustand, siehe LCP17xx Manual)
  txdLine.funkt = 0;          // Reset Pinfunktion
  txdLine.mode = 0;           // Pull-Up angeschaltet
  txdLine.openDrainMode = 0;  // Opendrain ausgeschaltet 
  rxdLine.funkt = 0;          // Reset Pinfunktion
  rxdLine.mode = 0;           // Pull-Up angeschaltet
  rxdLine.openDrainMode = 0;  // Opendrain ausgeschaltet
  if ( unInitPin ( &txdLine ) ) return SER_ERR;  
  if ( unInitPin ( &rxdLine ) ) return SER_ERR;
  // Reset UART  
  uart->LCR = 0;
  uart->FCR = 0; 
  pAssignedUart[serSel] = 0;        // UART abgeschaltet
  return SER_OK;
}

// Zeichen senden (blockierendes Warten auf freien Sendepuffer!)
int sendSerial ( SERSEL_T serSel, int ch )
{
  if ( pAssignedUart[serSel] == 0 ) return ch; // kein UART zugeteilt
  
  while (!(pAssignedUart[serSel]->LSR & THRE)); // warten auf Transmit Holding Reg Empty
  return (pAssignedUart[serSel]->THR = ch);
}

// Zeichen empfangen (blockierendes Warten!)
int getSerial ( SERSEL_T serSel)
{
  if ( pAssignedUart[serSel] == 0 ) return EOT; // kein UART zugeteilt, EOT zurueck
  
  while (!(pAssignedUart[serSel]->LSR & RDR)); // warten auf Receive Data Ready 
  return (pAssignedUart[serSel]->RBR);
}

/**
 * @}
 */

/**
 * @}
 */
