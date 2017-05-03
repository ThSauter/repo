/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: DefaultConfig
	Model Element	: Joystick
//!	Generated Date	: Wed, 26, Apr 2017  
	File Path	: MCB1700\DefaultConfig\Joystick.h
*********************************************************************/

#ifndef Joystick_H
#define Joystick_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "Default.h"
//## link itsBoard
class Board;

//## package Default

//## class Joystick
class Joystick : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Joystick()
    Joystick(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Joystick();
    
    ////    Operations    ////
    
    //## operation sample()
    void sample();
    
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
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);

private :

    //## auto_generated
    int getLastPosition() const;
    
    //## auto_generated
    void setLastPosition(int p_lastPosition);
    
    //## auto_generated
    int getSampleTime() const;
    
    //## auto_generated
    void setSampleTime(int p_sampleTime);
    
    ////    Attributes    ////

protected :

    int lastPosition;		//## attribute lastPosition
    
    int sampleTime;		//## attribute sampleTime
    
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
    
    // Sample:
    //## statechart_method
    inline bool Sample_IN() const;
    
    // Hold:
    //## statechart_method
    inline bool Hold_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Joystick_Enum {
        OMNonState = 0,
        Sample = 1,
        Hold = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool Joystick::rootState_IN() const {
    return true;
}

inline bool Joystick::Sample_IN() const {
    return rootState_subState == Sample;
}

inline bool Joystick::Hold_IN() const {
    return rootState_subState == Hold;
}

#endif
/*********************************************************************
	File Path	: MCB1700\DefaultConfig\Joystick.h
*********************************************************************/
