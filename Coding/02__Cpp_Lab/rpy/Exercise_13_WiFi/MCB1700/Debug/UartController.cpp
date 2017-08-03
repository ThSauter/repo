/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartController
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartController.cpp
*********************************************************************/

//## auto_generated
#include "UartController.h"
//## auto_generated
#include <lpc17xx.h>
//## package DefaultPkg

//## class UartController
bool UartController::isInitialized = 0;

UartController::UartController() {
    //#[ operation UartController()
        if (isInitialized == false)
        {
        uint32_t var_UartPclk_u32,var_Pclk_u32,var_RegValue_u32;
    
        LPC_PINCON->PINSEL0 &= ~0x000000F0;
        LPC_PINCON->PINSEL0 |= 0x00000050;            // Enable TxD0 P0.2 and p0.3 
    
        LPC_UART0->FCR = (1<<0x00) | (1<<0x01) | (1<<0x02); // Enable FIFO and reset Rx/Tx FIFO buffers    
        LPC_UART0->LCR = (0x03<<0x00) | (1<<0x07);             // 8bit data, 1Stop bit, No parity
    
    
        /** Baud Rate Calculation :
           PCLKSELx registers contains the PCLK info for all the clock dependent peripherals.
           Bit6,Bit7 contains the Uart Clock(ie.UART_PCLK) information.
           The UART_PCLK and the actual Peripheral Clock(PCLK) is calculated as below.
           (Refer data sheet for more info)
           UART_PCLK    PCLK
             0x00       SystemFreq/4        
             0x01       SystemFreq
             0x02       SystemFreq/2
             0x03       SystemFreq/8   
         **/
    
        var_UartPclk_u32 = (LPC_SC->PCLKSEL0 >> 6) & 0x03;
    
        switch( var_UartPclk_u32 )
        {
        case 0x00:
            var_Pclk_u32 = SystemCoreClock/4;
            break;
        case 0x01:
            var_Pclk_u32 = SystemCoreClock;
            break; 
        case 0x02:
            var_Pclk_u32 = SystemCoreClock/2;
            break; 
        case 0x03:
            var_Pclk_u32 = SystemCoreClock/8;
            break;
        }
    
    
        var_RegValue_u32 = ( var_Pclk_u32 / (16 * 115200 )); 
        LPC_UART0->DLL =  var_RegValue_u32 & 0xFF;
        LPC_UART0->DLM = (var_RegValue_u32 >> 0x08) & 0xFF;
    
        util_BitClear(LPC_UART0->LCR,(0x07));  // Clear DLAB after setting DLL,DLM  
        }
    WSTMonitor_sendInit( this, 107, (void*)&dbuf);
    
    //#]
}

UartController::~UartController() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

char UartController::rxChar() {
    //#[ operation rxChar()
    char ch; 
    while(util_IsBitCleared(LPC_UART0->LSR,0x00u))
    {
    	osDelay(10);  
    }
    ch = LPC_UART0->RBR;                                // Read received data    
    return ch;
    //#]
}

void UartController::txChar(char ch) {
    //#[ operation txChar(char)
        while(util_IsBitCleared(LPC_UART0->LSR,0x05u)); // Wait for Previous transmission
        LPC_UART0->THR=ch;                                  // Load the data to be transmitted
    //#]
}

int UartController::getDbuf() const {
    return dbuf;
}

void UartController::setDbuf(int p_dbuf) {
    dbuf = p_dbuf;
}

bool UartController::getIsInitialized() {
    return isInitialized;
}

void UartController::setIsInitialized(bool p_isInitialized) {
    isInitialized = p_isInitialized;
}

/*********************************************************************
	File Path	: MCB1700\Debug\UartController.cpp
*********************************************************************/
