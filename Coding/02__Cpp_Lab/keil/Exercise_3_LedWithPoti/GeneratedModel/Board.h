/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Wed, 29, Mar 2017  
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
//## link itsLedBar
#include "LedBar.h"
//## package Default

//## class Board
class Board : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Board(int,int)
    Board(int aDelay, int aLedNr, WST_TSK* myTask = 0);
    
    //## auto_generated
    Board(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Board();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getDelay() const;
    
    //## auto_generated
    void setDelay(int p_delay);
    
    //## auto_generated
    int getLedNr() const;
    
    //## auto_generated
    void setLedNr(int p_ledNr);
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initRelations();
    
    //## auto_generated
    void initStatechart();
    
    ////    Attributes    ////
    
    int delay;		//## attribute delay
    
    int ledNr;		//## attribute ledNr
    
    ////    Relations and components    ////
    
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
    
    // runLedBar:
    //## statechart_method
    inline bool runLedBar_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Board_Enum {
        OMNonState = 0,
        runLedBar = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool Board::rootState_IN() const {
    return true;
}

inline bool Board::runLedBar_IN() const {
    return rootState_subState == runLedBar;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Board.h
*********************************************************************/
