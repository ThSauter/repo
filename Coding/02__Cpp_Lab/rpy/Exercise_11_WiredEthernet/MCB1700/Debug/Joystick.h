/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Joystick
//!	Generated Date	: Wed, 17, May 2017  
	File Path	: MCB1700\Debug\Joystick.h
*********************************************************************/

#ifndef Joystick_H
#define Joystick_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## link itsEthernetTransmitter
class EthernetTransmitter;

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
    EthernetTransmitter* getItsEthernetTransmitter() const;
    
    //## auto_generated
    void setItsEthernetTransmitter(EthernetTransmitter* p_EthernetTransmitter);
    
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
    
    EthernetTransmitter* itsEthernetTransmitter;		//## link itsEthernetTransmitter
    
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
