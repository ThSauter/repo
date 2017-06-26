/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Joystick
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\Joystick.h
*********************************************************************/

#ifndef Joystick_H
#define Joystick_H

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
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## link itsLedBar
class LedBar;

//## link itsSDCard
class SDCard;

//## package DefaultPkg

//## class Joystick
class Joystick : public WST_TSK, public WST_FSM {
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
    int getLastPosition() const;
    
    //## auto_generated
    void setLastPosition(int p_lastPosition);
    
    //## auto_generated
    int getSampleTime() const;
    
    //## auto_generated
    void setSampleTime(int p_sampleTime);
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    void setItsLedBar(LedBar* p_LedBar);
    
    //## auto_generated
    SDCard* getItsSDCard() const;
    
    //## auto_generated
    void setItsSDCard(SDCard* p_SDCard);
    
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
    
    int lastPosition;		//## attribute lastPosition
    
    int sampleTime;		//## attribute sampleTime
    
    ////    Relations and components    ////
    
    LedBar* itsLedBar;		//## link itsLedBar
    
    SDCard* itsSDCard;		//## link itsSDCard
    
    ////    Framework operations    ////

public :

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
	File Path	: MCB1700\Debug\Joystick.h
*********************************************************************/
