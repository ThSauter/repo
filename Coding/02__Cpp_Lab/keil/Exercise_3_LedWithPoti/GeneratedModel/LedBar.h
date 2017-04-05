/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: LedBar
//!	Generated Date	: Wed, 29, Mar 2017  
	File Path	: MCB1700\Debug\LedBar.h
*********************************************************************/

#ifndef LedBar_H
#define LedBar_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "Default.h"
//## link itsBoard
class Board;

//## package Default

//## class LedBar
class LedBar : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation LedBar(int,int)
    LedBar(int aBitNr, int aDelay, WST_TSK* myTask = 0);
    
    //## auto_generated
    LedBar(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~LedBar();
    
    ////    Operations    ////
    
    //## operation off()
    void off();
    
    //## operation on()
    void on();
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getBitNr() const;
    
    //## auto_generated
    void setBitNr(int p_bitNr);
    
    //## auto_generated
    int getDelay() const;
    
    //## auto_generated
    void setDelay(int p_delay);
    
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
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);
    
    ////    Attributes    ////
    
    int bitNr;		//## attribute bitNr
    
    int delay;		//## attribute delay
    
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
    
    // State_on:
    //## statechart_method
    inline bool State_on_IN() const;
    
    // State_off:
    //## statechart_method
    inline bool State_off_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum LedBar_Enum {
        OMNonState = 0,
        State_on = 1,
        State_off = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool LedBar::rootState_IN() const {
    return true;
}

inline bool LedBar::State_on_IN() const {
    return rootState_subState == State_on;
}

inline bool LedBar::State_off_IN() const {
    return rootState_subState == State_off;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\LedBar.h
*********************************************************************/
