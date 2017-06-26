/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

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
#include <oxf\omlist.h>
//## dependency Board_GLCD
//#[ ignore
extern "C"
{
//#]
#include <Board_GLCD.h>
}
//## dependency GLCD_Config
//#[ ignore
extern "C"
{
//#]
#include <GLCD_Config.h>
}
//## package DefaultPkg

//## class Display
class Display : public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation Display()
    Display(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~Display();
    
    ////    Operations    ////
    
    //## operation drawSDCardLogging2()
    void drawSDCardLogging2();
    
    //## operation drawSDCardStatus(char*)
    void drawSDCardStatus(const char* logMessage);
    
    ////    Additional operations    ////
    
    //## auto_generated
    OMIterator<OMString> getLoggedLines() const;
    
    //## auto_generated
    void setLoggedLines(OMString p_loggedLines);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();

public :

    static uint16 ClassWSTMonitor_getTypeSize10();
    
    ////    Attributes    ////

protected :

    OMList<OMString> loggedLines;		//## attribute loggedLines
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // remove_line:
    //## statechart_method
    inline bool remove_line_IN() const;
    
    // draw_line:
    //## statechart_method
    inline bool draw_line_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum Display_Enum {
        OMNonState = 0,
        remove_line = 1,
        draw_line = 2
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

uint16 WSTMonitor_getTypeSize10();

inline bool Display::rootState_IN() const {
    return true;
}

inline bool Display::remove_line_IN() const {
    return rootState_subState == remove_line;
}

inline bool Display::draw_line_IN() const {
    return rootState_subState == draw_line;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/
