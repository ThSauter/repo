/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: LedBar
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\LedBar.h
*********************************************************************/

#ifndef LedBar_H
#define LedBar_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "rl_fs.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "DefaultPkg.h"
//## link itsLeds
#include "Led.h"
//## package DefaultPkg

//## class LedBar
class LedBar : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation LedBar()
    LedBar(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~LedBar();
    
    ////    Operations    ////
    
    //## operation offSingleLed(int)
    void offSingleLed(int ledNr);
    
    //## operation onSingleLed(int)
    void onSingleLed(int ledNr);
    
    //## operation processJoystickPosition()
    void processJoystickPosition();
    
    //## operation toggleSingleLed(int)
    void toggleSingleLed(int ledNr);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getItsLeds() const;
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();

private :

    //## auto_generated
    char getJoystickPosition() const;
    
    //## auto_generated
    void setJoystickPosition(char p_joystickPosition);
    
    ////    Attributes    ////

protected :

    char joystickPosition;		//## attribute joystickPosition
    
    ////    Relations and components    ////
    
    Led itsLeds[4];		//## link itsLeds
    
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
    
    // ProcessLeds:
    //## statechart_method
    inline bool ProcessLeds_IN() const;
    
    // Idle:
    //## statechart_method
    inline bool Idle_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum LedBar_Enum {
        OMNonState = 0,
        ProcessLeds = 1,
        Idle = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool LedBar::rootState_IN() const {
    return true;
}

inline bool LedBar::ProcessLeds_IN() const {
    return rootState_subState == ProcessLeds;
}

inline bool LedBar::Idle_IN() const {
    return rootState_subState == Idle;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\LedBar.h
*********************************************************************/
