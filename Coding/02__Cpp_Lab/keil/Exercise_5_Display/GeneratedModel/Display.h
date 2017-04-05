/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## dependency Board_GLCD
//#[ ignore
extern "C"
{
//#]
#include <Board_GLCD.h>
}
//## dependency GLCD_config
//#[ ignore
extern "C"
{
//#]
#include <GLCD_config.h>
}
//## link itsBoard
class Board;

//## package Default

//## class Display
class Display : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Display()
    Display(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Display();
    
    ////    Operations    ////
    
    //## operation drawString(int)
    void drawString(int ledNr);
    
    ////    Additional operations    ////
    
    //## auto_generated
    Board* getItsBoard() const;
    
    //## auto_generated
    void setItsBoard(Board* p_Board);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
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
    
    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Display_refresh:
    //## statechart_method
    inline bool Display_refresh_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Display_Enum {
        OMNonState = 0,
        Display_refresh = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool Display::rootState_IN() const {
    return true;
}

inline bool Display::Display_refresh_IN() const {
    return rootState_subState == Display_refresh;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/
