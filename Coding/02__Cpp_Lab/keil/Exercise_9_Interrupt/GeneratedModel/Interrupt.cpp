/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Interrupt
//!	Generated Date	: Fri, 7, Apr 2017  
	File Path	: MCB1700\Debug\Interrupt.cpp
*********************************************************************/

//## auto_generated
#include "Interrupt.h"
//## link itsBoard
#include "Board.h"
//## package Default

//## class Interrupt
Interrupt::Interrupt() {
    itsBoard = NULL;
    //#[ operation Interrupt()
    // P2.10 is function EINT0 for 01 (page 110)
    LPC_PINCON->PINSEL4 |= (1<<20);   
    // Disbale IRQ interrupt for INT0 in NVIC to configure  
    // EXTMODE (page 25) and EXTPOLAR (page 26)
    NVIC_DisableIRQ(EINT0_IRQn);  
    // To ensure that EINT0 interrupt is cleared (page 24)
    LPC_SC->EXTINT |= (1<<0);      
    // EINT0 is edge-sensitive (page 25)
    LPC_SC->EXTMODE |= (1<<0);
    // EINT0 is falling edge sensitive (page 26)
    LPC_SC->EXTPOLAR &= ~(1<<0);
    // Enable IRQ interrupt for INT0 in NVIC
    NVIC_EnableIRQ(EINT0_IRQn);
    
    //#]
}

Interrupt::~Interrupt() {
    cleanUpRelations();
}

Board* Interrupt::getItsBoard() const {
    return itsBoard;
}

void Interrupt::setItsBoard(Board* p_Board) {
    _setItsBoard(p_Board);
}

void Interrupt::cleanUpRelations() {
    if(itsBoard != NULL)
        {
            itsBoard = NULL;
        }
}

void Interrupt::__setItsBoard(Board* p_Board) {
    itsBoard = p_Board;
}

void Interrupt::_setItsBoard(Board* p_Board) {
    __setItsBoard(p_Board);
}

void Interrupt::_clearItsBoard() {
    itsBoard = NULL;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Interrupt.cpp
*********************************************************************/
