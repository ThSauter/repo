/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: SDCard
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\SDCard.h
*********************************************************************/

#ifndef SDCard_H
#define SDCard_H

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
//## link itsClock
class Clock;

//## link itsDisplay
class Display;

//## package DefaultPkg

//## class SDCard
class SDCard : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    SDCard(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~SDCard();
    
    ////    Operations    ////
    
    //## operation append(char)
    void append(char position);
    
    //## operation deleteFile()
    void deleteFile();
    
    //## operation initAndMount()
    void initAndMount();
    
    //## operation read()
    void read();
    
    ////    Additional operations    ////
    
    //## auto_generated
    static int getCounter();
    
    //## auto_generated
    static void setCounter(int p_counter);
    
    //## auto_generated
    char getJoystickPos() const;
    
    //## auto_generated
    void setJoystickPos(char p_joystickPos);
    
    //## auto_generated
    Clock* getItsClock() const;
    
    //## auto_generated
    void setItsClock(Clock* p_Clock);
    
    //## auto_generated
    Display* getItsDisplay() const;
    
    //## auto_generated
    void setItsDisplay(Display* p_Display);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();

private :

    //## auto_generated
    static const char* getFileName();
    
    ////    Attributes    ////

protected :

    static int counter;		//## attribute counter
    
    static const char* fileName;		//## attribute fileName
    
    char joystickPos;		//## attribute joystickPos
    
    ////    Relations and components    ////
    
    Clock* itsClock;		//## link itsClock
    
    Display* itsDisplay;		//## link itsDisplay
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Read:
    //## statechart_method
    inline bool Read_IN() const;
    
    // Log:
    //## statechart_method
    inline bool Log_IN() const;
    
    // Initialize:
    //## statechart_method
    inline bool Initialize_IN() const;
    
    // Delete_File:
    //## statechart_method
    inline bool Delete_File_IN() const;
    
    // Confirm_Delete:
    //## statechart_method
    inline bool Confirm_Delete_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum SDCard_Enum {
        OMNonState = 0,
        Read = 1,
        Log = 2,
        Initialize = 3,
        Delete_File = 4,
        Confirm_Delete = 5
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool SDCard::rootState_IN() const {
    return true;
}

inline bool SDCard::Read_IN() const {
    return rootState_subState == Read;
}

inline bool SDCard::Log_IN() const {
    return rootState_subState == Log;
}

inline bool SDCard::Initialize_IN() const {
    return rootState_subState == Initialize;
}

inline bool SDCard::Delete_File_IN() const {
    return rootState_subState == Delete_File;
}

inline bool SDCard::Confirm_Delete_IN() const {
    return rootState_subState == Confirm_Delete;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\SDCard.h
*********************************************************************/
