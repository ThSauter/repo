/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Board
//!	Generated Date	: Fri, 7, Apr 2017  
	File Path	: MCB1700\Debug\Board.h
*********************************************************************/

#ifndef Board_H
#define Board_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## link itsDisplay
#include "Display.h"
//## link itsInterrupt
#include "Interrupt.h"
//## link itsLedBar
#include "LedBar.h"
//## link itsPoti
#include "Poti.h"
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
    
    ////    Operations    ////
    
    //## operation drawPotiValue(int)
    void drawPotiValue(int potiValue);
    
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
    int getPotiValue() const;
    
    //## auto_generated
    void setPotiValue(int p_potiValue);
    
    //## auto_generated
    Display* getItsDisplay() const;
    
    //## auto_generated
    Interrupt* getItsInterrupt() const;
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    Poti* getItsPoti() const;
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initRelations();
    
    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    int delay;		//## attribute delay
    
    int ledNr;		//## attribute ledNr
    
    int potiValue;		//## attribute potiValue
    
    ////    Relations and components    ////
    
    Display itsDisplay;		//## link itsDisplay
    
    Interrupt itsInterrupt;		//## link itsInterrupt
    
    LedBar itsLedBar;		//## link itsLedBar
    
    Poti itsPoti;		//## link itsPoti
    
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
    
    // controlling:
    //## statechart_method
    inline bool controlling_IN() const;
    
    //## statechart_method
    void controlling_entDef();
    
    //## statechart_method
    void controlling_exit();
    
    //## statechart_method
    IOxfReactive::TakeEventStatus controlling_processEvent();
    
    // state_4:
    //## statechart_method
    inline bool state_4_IN() const;
    
    //## statechart_method
    void state_4_entDef();
    
    //## statechart_method
    IOxfReactive::TakeEventStatus state_4_processEvent();
    
    // updateDisplay:
    //## statechart_method
    inline bool updateDisplay_IN() const;
    
    // state_3:
    //## statechart_method
    inline bool state_3_IN() const;
    
    //## statechart_method
    void state_3_entDef();
    
    //## statechart_method
    IOxfReactive::TakeEventStatus state_3_processEvent();
    
    // runLedBar:
    //## statechart_method
    inline bool runLedBar_IN() const;
    
    //## statechart_method
    void runLedBar_entDef();
    
    //## statechart_method
    void runLedBar_exit();
    
    //## statechart_method
    IOxfReactive::TakeEventStatus runLedBar_handleEvent();
    
    // notifyLedBar:
    //## statechart_method
    inline bool notifyLedBar_IN() const;
    
    //## statechart_method
    IOxfReactive::TakeEventStatus notifyLedBar_handleEvent();
    
    // pause:
    //## statechart_method
    inline bool pause_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Board_Enum {
        OMNonState = 0,
        controlling = 1,
        state_4 = 2,
        updateDisplay = 3,
        state_3 = 4,
        runLedBar = 5,
        notifyLedBar = 6,
        pause = 7
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    int state_4_subState;
    
    int state_4_active;
    
    int state_3_subState;
    
    int state_3_active;
    
    int runLedBar_subState;
    
    IOxfTimeout* runLedBar_timeout;
//#]
};

inline bool Board::rootState_IN() const {
    return true;
}

inline bool Board::controlling_IN() const {
    return rootState_subState == controlling;
}

inline bool Board::state_4_IN() const {
    return controlling_IN();
}

inline bool Board::updateDisplay_IN() const {
    return state_4_subState == updateDisplay;
}

inline bool Board::state_3_IN() const {
    return controlling_IN();
}

inline bool Board::runLedBar_IN() const {
    return state_3_subState == runLedBar;
}

inline bool Board::notifyLedBar_IN() const {
    return runLedBar_subState == notifyLedBar;
}

inline bool Board::pause_IN() const {
    return state_3_subState == pause;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Board.h
*********************************************************************/
