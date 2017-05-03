/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Interrupt
//!	Generated Date	: Fri, 7, Apr 2017  
	File Path	: MCB1700\Debug\Interrupt.h
*********************************************************************/

#ifndef Interrupt_H
#define Interrupt_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## link itsBoard
class Board;

//## package Default

//## class Interrupt
class Interrupt {
    ////    Constructors and destructors    ////
    
public :

    //## operation Interrupt()
    Interrupt();
    
    //## auto_generated
    virtual ~Interrupt();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Board* getItsBoard() const;
    
    //## auto_generated
    void setItsBoard(Board* p_Board);

protected :

    //## auto_generated
    void cleanUpRelations();
    
    ////    Relations and components    ////
    
    Board* itsBoard;		//## link itsBoard
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void __setItsBoard(Board* p_Board);
    
    //## auto_generated
    void _setItsBoard(Board* p_Board);
    
    //## auto_generated
    void _clearItsBoard();
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Interrupt.h
*********************************************************************/
