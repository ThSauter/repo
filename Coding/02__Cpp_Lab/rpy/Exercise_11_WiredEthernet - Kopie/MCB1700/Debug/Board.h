/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Mon, 24, Apr 2017  
	File Path	: MCB1700\Debug\Board.h
*********************************************************************/

#ifndef Board_H
#define Board_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "Default.h"
//## link itsJoystick
#include "Joystick.h"
//## link itsLedBar
#include "LedBar.h"
//## package Default

//## class Board
class Board : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    Board(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Board();
    
    ////    Operations    ////
    
    //## operation processJoystickData()
    void processJoystickData();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Joystick* getItsJoystick() const;
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initRelations();
    
    //## auto_generated
    void initStatechart();

private :

    //## auto_generated
    int getJoystickPosition() const;
    
    //## auto_generated
    void setJoystickPosition(int p_joystickPosition);
    
    ////    Attributes    ////

protected :

    int joystickPosition;		//## attribute joystickPosition
    
    ////    Relations and components    ////
    
    Joystick itsJoystick;		//## link itsJoystick
    
    LedBar itsLedBar;		//## link itsLedBar
    
    ////    Framework operations    ////

public :

    //## auto_generated
    void setTask(WST_TSK* myTask, bool activeInstance);
    
    //## auto_generated
    virtual void destroy();
    
    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // ProcessJoystickData:
    //## statechart_method
    inline bool ProcessJoystickData_IN() const;
    
    // Idle:
    //## statechart_method
    inline bool Idle_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Board_Enum {
        OMNonState = 0,
        ProcessJoystickData = 1,
        Idle = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool Board::rootState_IN() const {
    return true;
}

inline bool Board::ProcessJoystickData_IN() const {
    return rootState_subState == ProcessJoystickData;
}

inline bool Board::Idle_IN() const {
    return rootState_subState == Idle;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Board.h
*********************************************************************/
