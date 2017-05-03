/*******************************************************************************
Produkt:    Labore MCOM
Kunde:      HS Ulm

Copyright (C): Hochschule Ulm
*******************************************************************************/

/*!
********************************************************************************
@file       SERIAL.c
@brief      LPC17xx Hardware Abstraction Layer:
            Implementierung zu UART-Routinen.
            4 Instanzen (UART0 .. UART3) sind moeglich.
            Version fuer RTX-Betriebsystem.
            Initialisierung muss im Privileged Betrieb erfolgen, 
            da NVIC konfiguriert wird.
            
@details    siehe Headerdatei
            Hardwareabhaengige Implementierung fuer  feste Baudrate 19200Bd
            bei 25MHz UART Clock

            Multitaskingfaehige Version fuer RTX-Kernel.
            Mutexes zum Reservieren der Eingabe oder Ausgabe.
            Eventmechanismus fuer Transmit-Interrupts.
            RTX-Mailbox als Empfangspuffer bei Receive-Interrupts.
            
@author     N. Normann                                             
@version    5.7
@date       30. Oktober 2013
*******************************************************************************/

// Import-Schnittstellen *******************************************************
// C99
#include <inttypes.h>         // MISRA-C:2004 Standard Integer Types
#include <stdbool.h>          // C99 Keywords bool, true, false
// LPC17xx Devices
#include <LPC17xx.h>
// EmbeddedOS
#include "system_lpc17xx.h"   // LPC17xx System
#include <RTL.h>              // Schnittstelle zum RTX-Betriebssystem

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

// Applikationsparameter
// Divisor Latch Registers DLL und DLM
static const uint8_t  DLLSET = 81;    //!< fuer 19290 Bd bei 25MHz UART-Clock
static const uint8_t  DLMSET =  0;

// Bits der UART-Register (nicht vollstaendig)
// FIFO Control Reg FCR Bits
static const uint8_t  RXTRIG =       (3U<<6); // Rx Trigger Level3 (14 Bytes)
static const uint8_t  TXFIFORESET  = (1U<<2); // TX FIFO Reset
static const uint8_t  RXFIFORESET  = (1U<<1); // RX FIFO Reset
static const uint8_t  FIFOENABLE   = (1U<<0); // FIFO Enable

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
//static const uint8_t  THRE =         (1U<<5); // Transmit Holding Reg Empty
//static const uint8_t  BI =           (1U<<4); // Break Interrupt
//static const uint8_t  FE =           (1U<<3); // Framing Error
//static const uint8_t  PE =           (1U<<2); // Parity Error
//static const uint8_t  OE =           (1U<<1); // Overrun Error
static const uint8_t  RDR =          (1U<<0); // Receiver Data Ready

// Interrupt Enable Register IER Bits
static const uint8_t RBRIntEn = 1U;
static const uint8_t THREIntEn = (1U<<1);

// Interrupt Information Register IIR Bits
static const uint8_t THREInt = (1U<<1);  // TransmitHoldingReg Empty Interrupt 
static const uint8_t RDAInt = (1U<<2);   // ReceiveDataAvailable Interrupt


// RTX Konstanten
static const uint16_t EVT_TBR = 0x0001; //!< Event: UART1 kann Zeichen senden
static const uint32_t FOREVER = 0xFFFF; //!< unendliche Wartezeit
static const uint32_t CHARMAX = 16; //!< Mailboxgroesse fuer empfangene Zeichen

//! @brief private Klasse fuer UARTs
typedef struct
{
  SERIALSEL_T name;        //!< UART Name
  LPC_UART_TypeDef* pUart; //!< Pointer auf UART-Register
  IRQn_Type uartInt;       //!< UART Interrupt Vector
  PINCONNECT txdLine;      //!< TxD Hardwareport
  PINCONNECT rxdLine;      //!< RxD Hardwareport
  OS_TID tidTransmitTask;  //!< Task, die die Ausgabe reserviert hat
  OS_MUT mutSerOut;        //!< Mutex zur Reservierung der Ausgabe
  OS_MUT mutSerIn;         //!< Mutex zur Reservierung der Eingabe
  os_mbx_declare (rxdBuff,CHARMAX); //!< Puffer fuer CHARMAX Empfangszeichen
} UART;

// Definition interner modulglobaler Variabler *********************************
//! private statische Instanzen fuer 4 serielle Schnittstellen UART0 .. UART3
static UART uart[4]; //!< SERIAL_constr( ) initialisiert die Array-Elemente

// Interne Funktionsprototypen des Moduls **************************************
static SERIALSTAT_T selectLines( UART* me );
static void interruptSerial ( SERIALSEL_T serSel );
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);

// Oeffentliche Methoden des Moduls   ******************************************

// Eine serielle Schnittstelle zuweisen und konfigurieren
SERIALSTAT_T SERIAL_constr ( SERIAL* me, SERIALSEL_T name)  
{

  // UART schon in Benutzung?
  if ( uart[name].pUart != 0 ) return SERIAL_ERR;

  // UART zuweisen
  // zugehoerige RxD und TxD-Leitungen auswaehlen
  uart[name].name = name;  
  if ( selectLines ( &uart[name] ) !=SERIAL_OK ) return SERIAL_ERR; 
  // Pins fuer UARTx verbinden
  if ( PINCONNECT_constr ( &(uart[name].rxdLine), 
       uart[name].rxdLine.port, uart[name].rxdLine.bitNo, 
       uart[name].rxdLine.funkt, uart[name].rxdLine.mode, 
       uart[name].rxdLine.openDrainMode ) )  return SERIAL_ERR;

  if ( PINCONNECT_constr ( &(uart[name].txdLine), 
       uart[name].txdLine.port, uart[name].txdLine.bitNo, 
       uart[name].txdLine.funkt, uart[name].txdLine.mode, 
       uart[name].txdLine.openDrainMode ) )  return SERIAL_ERR;
  
  // UART zuweisen und konfigurieren
  me->serialSel = name;

  // Register des zugeordneten UARTs konfigurieren  
  // Zugriff auf LCR mit DLAB=1, 8 bits, no Parity, 1 Stop bit
  uart[me->serialSel].pUart->LCR = DLAB | BITS8;
  // Baud Rate setzen
  uart[me->serialSel].pUart->DLL = DLLSET;            
  uart[me->serialSel].pUart->DLM = DLMSET; 
  // Zugriff auf LCR mit DLAB = 0  
  uart[me->serialSel].pUart->LCR = uart[me->serialSel].pUart->LCR &~DLAB;
  // FIFOs Enable und Reset
  uart[me->serialSel].pUart->FCR = FIFOENABLE | RXTRIG;
  // Enable Interrupt Requests
  uart[me->serialSel].pUart->IER = RBRIntEn | THREIntEn;
  
  // Mutexe des UART initialisieren vor erster Verwendung
  os_mut_init ( &(uart[me->serialSel].mutSerOut) );
  os_mut_init ( &(uart[me->serialSel].mutSerIn) );
  
  // Enable Interrupt des zugeordneten UARTs   
  NVIC_EnableIRQ(uart[me->serialSel].uartInt);
  return SERIAL_OK;
}

// Ausschalten des UART, Freigabe der Leitungen
SERIALSTAT_T SERIAL_destr ( SERIAL* me ) 
{
  
  if ( uart[me->serialSel].pUart == 0 ) return SERIAL_ERR; // UART schon frei
  
  NVIC_DisableIRQ(uart[me->serialSel].uartInt); // disable UART Interrupt

  // RxD und TxD-Leitungen auswaehlen   
  if ( selectLines ( &uart[me->serialSel] ) ) return SERIAL_ERR;  
  // RxD und TxD-Leitungen abklemmen (Reset-Zustand, siehe LCP17xx Manual)
  uart[me->serialSel].txdLine.funkt = 0;          // Reset Pinfunktion
  uart[me->serialSel].txdLine.mode = 0;           // Pull-Up angeschaltet
  uart[me->serialSel].txdLine.openDrainMode = 0;  // Opendrain ausgeschaltet 
  uart[me->serialSel].rxdLine.funkt = 0;          // Reset Pinfunktion
  uart[me->serialSel].rxdLine.mode = 0;           // Pull-Up angeschaltet
  uart[me->serialSel].rxdLine.openDrainMode = 0;  // Opendrain ausgeschaltet

  if ( PINCONNECT_destr (&(uart[me->serialSel].rxdLine)) ) return SERIAL_ERR;  
  if ( PINCONNECT_destr (&(uart[me->serialSel].txdLine)) ) return SERIAL_ERR;
  // Reset UART  
  uart[me->serialSel].pUart->LCR = 0;
  uart[me->serialSel].pUart->FCR = TXFIFORESET | RXFIFORESET;
  uart[me->serialSel].pUart->FCR = 0; 
  uart[me->serialSel].pUart = 0;        // UART abgeschaltet

  return SERIAL_OK;
}

// SerialOut oeffnen, fuer laufenden Prozess reservieren
extern SERIALSTAT_T SERIAL_openOut ( SERIAL* me )
{
  OS_RESULT result;
  
  // UART muss konfiguriert sein, sonst Fehler
  if ( uart[me->serialSel].pUart == 0 ) return SERIAL_ERR;
  
  // Sofortigen Besitz der seriellen Ausgabe erbitten
  result = os_mut_wait(&(uart[me->serialSel].mutSerOut), 0);
  if ( (result == OS_R_OK) || (result == OS_R_MUT))
  {
    // Bitte erfolgreich, laufende Task hat Mutex mutSerOut
    // erhalten und lenkt die
    // von interruptSerial erzeugten Transmit-Events auf sich. 
    uart[me->serialSel].tidTransmitTask = os_tsk_self();
    // Sendebereitschaft fuer 1. Zeichen signalisieren
    os_evt_set(EVT_TBR, uart[me->serialSel].tidTransmitTask);
    return (SERIAL_OK);
  }
  else
  {
    // Bitte abgelehnt.
    // mutSerOut gehoert schon einer anderen Task
    return (SERIAL_ERR);
  }
}

// Zeichen senden ( Warten auf freien Sendepuffer durch RTX)
// Datentyp int, da C-Standard Library diesen Datentyp verwendet
int SERIAL_sendOut ( SERIAL* me, int ch )
{
  // Sofortigen Besitz der seriellen Ausgabe erbitten
  if ( (os_mut_wait(&(uart[me->serialSel].mutSerOut), 0) == OS_R_OK))
  {
    // StdOut ist von der laufenden Task reserviert, Zeichen ausgeben
    os_evt_wait_or(EVT_TBR, FOREVER);  // Task Waiting, bis UART sendebereit
    os_evt_clr(EVT_TBR, uart[me->serialSel].tidTransmitTask); 
    uart[me->serialSel].pUart->THR = (char)ch; // Byte an UART uebergeben zum Senden
    // aktuelle Mutexanforderung aufheben
    os_mut_release(&(uart[me->serialSel].mutSerOut)); 
    return ch;
  }
  else
  {
    os_tsk_delete_self(); // illegaler Aufruf von sendSerial, Abbruch
    return (-1);          // Dummy
  }
}

// SerialOut schliessen und freigeben
extern SERIALSTAT_T SERIAL_closeOut ( SERIAL* me )
{
  // UART konfiguriert?
  if ( uart[me->serialSel].pUart == 0 ) return SERIAL_ERR;
  
  if ( (os_mut_wait(uart[me->serialSel].mutSerOut, 0) == OS_R_OK))
  {  // nur der aktuelle Besitzer von mutStdOut kann freigeben
    // warten, bis Transmitpuffer leer
    os_evt_wait_or(EVT_TBR, FOREVER);  // Task Waiting, bis UART fertig    
    uart[me->serialSel].tidTransmitTask = 0;
    // obige Mutexanforderung zuruecknehmen
    os_mut_release(&(uart[me->serialSel].mutSerOut));
    // Mutexreservierung durch SERIAL_openOut freigeben
    os_mut_release(&(uart[me->serialSel].mutSerOut));
    return (SERIAL_OK);
  }
  else
  {
    // mutSerOut gehoert schon einer anderen Task
    return (SERIAL_ERR);
  }
}

// SerialIn oeffnen, fuer laufenden Prozess reservieren
extern SERIALSTAT_T SERIAL_openIn ( SERIAL* me )
{
  OS_RESULT result;

  // UART konfiguriert?  
  if ( uart[me->serialSel].pUart == 0 ) return SERIAL_ERR;

  // Sofortigen Besitz der seriellen Eingabe erbitten  
  result = os_mut_wait(&(uart[me->serialSel].mutSerIn), 0);
  if ( (result == OS_R_OK) || (result == OS_R_MUT))
  {
    // Bitte erfolgreich, laufende Task hat Mutex mutSerIn
    // erhalten, Mailbox rxdBuff zum Beginn leeren
    os_mbx_init (&(uart[me->serialSel].rxdBuff), 
                              sizeof(uart[me->serialSel].rxdBuff)); 
    return (SERIAL_OK);
  }
  else
  {
    // mutSerIn gehoert schon einer anderen Task
    return (SERIAL_ERR);
  }
}

// Zeichen empfangen (Warten durch RTX)
// Datentyp int, da C-Standard Library diesen Datentyp verwendet
int SERIAL_getIn ( SERIAL* me)
{
  void ** ppMessage=0; // Pointer auf den aktuellen Messagepointer

  // Sofortigen Besitz der seriellen Einggabe erbitten
  if ( (os_mut_wait(&(uart[me->serialSel].mutSerIn), 0) == OS_R_OK))
  {
    // Bitte erfolgreich, laufende Task hat Mutex mutSerIn.
    // Zeichen aus Mailbox rxdBuff abholen, wenn vorhanden, 
    // sonst beliebig lange warten.
    // Weil die RTX-Mailbox nur untypisierte Messagepointer verschickt, wird
    // ppMessage entsprechend in int umgewandelt 
    os_mbx_wait ( &(uart[me->serialSel].rxdBuff), ppMessage, FOREVER);
    // aktuelle Mutexanforderung aufheben    
    os_mut_release(&(uart[me->serialSel].mutSerIn));

    // Messagepointer lesen und in int-Zeichen wandeln
    return ( (int) *ppMessage );    
  }
  else
  {
    os_tsk_delete_self(); // illegaler Aufruf von getSerial, Abbruch
    return (-1);          // Dummy
  }
}

// Serial In schliessen und freigeben
extern SERIALSTAT_T SERIAL_closeIn ( SERIAL* me )
{

  if ( uart[me->serialSel].pUart == 0 ) return SERIAL_ERR; // UART nicht initialisiert
  
  if ( (os_mut_wait(&(uart[me->serialSel].mutSerIn), 0) == OS_R_OK))
  {  // nur der aktuelle Besitzer von mutStdOut kann freigeben 
    uart[me->serialSel].tidTransmitTask = 0;
    // obige Mutexanforderung zuruecknehmen
    os_mut_release(&(uart[me->serialSel].mutSerIn));
        // Mutexreservierung durch SERIAL_openIn freigeben
    os_mut_release(&(uart[me->serialSel].mutSerIn));
    return (SERIAL_OK);
  }
  else
  {
    // mutSerIn gehoert schon einer anderen Task
    return (SERIAL_ERR);
  }
}

// Private Methoden des Moduls   ******************************************
//! Auswahl der Hardwareports TxD und RxD des UARTs
SERIALSTAT_T selectLines ( UART* me )
{
  switch ( me->name)
  {
    case UART0:
      me->txdLine.port = 0;
      me->txdLine.bitNo = 2;
      me->txdLine.funkt = 1;
      me->rxdLine.port = 0;
      me->rxdLine.bitNo = 3;
      me->rxdLine.funkt = 1;
      me->pUart = LPC_UART0;
      me->uartInt = UART0_IRQn;
      return SERIAL_OK;
    case UART1:
      me->txdLine.port = 0;
      me->txdLine.bitNo = 15;
      me->txdLine.funkt = 1;
      me->rxdLine.port = 0;
      me->rxdLine.bitNo = 16;
      me->rxdLine.funkt = 1;
      me->pUart = (LPC_UART_TypeDef*) LPC_UART1;
      me->uartInt = UART1_IRQn;
      return SERIAL_OK;
    case UART2:
      me->txdLine.port = 0;
      me->txdLine.bitNo = 10;
      me->txdLine.funkt = 1;
      me->rxdLine.port = 0;
      me->rxdLine.bitNo = 11;
      me->rxdLine.funkt = 1;
      me->pUart = LPC_UART2;
      me->uartInt = UART2_IRQn;
      return SERIAL_OK;
    case UART3:
      me->txdLine.port = 0;
      me->txdLine.bitNo =  0;
      me->txdLine.funkt = 2;
      me->rxdLine.port = 0;
      me->rxdLine.bitNo =  1;
      me->rxdLine.funkt = 2;
      me->pUart = LPC_UART3;
      me->uartInt = UART3_IRQn;    
      return SERIAL_OK;
    default:
      return SERIAL_ERR;
  }
  
}

// ISRs fuer UARTs
void UART0_IRQHandler(void)
{
  interruptSerial ( UART0 );
}
void UART1_IRQHandler(void)
{
  interruptSerial ( UART1 );
}
void UART2_IRQHandler(void)
{
  interruptSerial ( UART2 );
}
void UART3_IRQHandler(void)
{
  interruptSerial ( UART3 );
}

//! Interrupt Service Routine fuer alle UARTs (Receive und Transmit)
/*!
  - Schreibt bei Receive-Interrupt die empfangenen Zeichen einzeln in 
    die Mailbox rxdBuff des UARTS, leert das Receive-FIFO. 
  - Sendet EVT_TBR an tidTransmitTask bei TransmitBufferEmpty-Interrupt.   
*/
static void interruptSerial ( SERIALSEL_T serSel )  
{
  uint32_t intInfo;
  int recChar; // Datentyp int, da C-Standard Library diesen Datentyp verwendet
  
  intInfo = uart[serSel].pUart->IIR; // lesen von IIR loescht TransmitIntFlg

  if (intInfo & RDAInt) 
  {
    // Receive interrupt RDA, Receive FIFO leeren
    while ( uart[serSel].pUart->LSR & RDR )
    {      
      recChar = uart[serSel].pUart->RBR; // loescht auch ReceiveIntFlg
      // Zeichen direkt in der Mailbox ablegen, wenn noch Platz frei.
      // Weil die RTX-Mailbox nur untypisierte Pointer verschickt, wird
      // recChar entsprechend in pMessage umgewandelt
      void * pMessage = (void*) recChar;      
      if (isr_mbx_check (&(uart[serSel].rxdBuff)) != 0) 
      { 
        isr_mbx_send (&(uart[serSel].rxdBuff), pMessage);     
      }
    }
  }
  if ((intInfo & THREInt) && (uart[serSel].tidTransmitTask>0)) 
  {
    // Transmit Register Empty Interrupt THRE
    // Event EVT_TBR: UART1 akzeptiert Zeichen zum Senden
    isr_evt_set(EVT_TBR, uart[serSel].tidTransmitTask); 
  }
}

/**
 * @}
 */

/**
 * @}
 */
