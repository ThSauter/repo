/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: DefaultPkg
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\DefaultPkg.h
*********************************************************************/

#ifndef DefaultPkg_H
#define DefaultPkg_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "rl_fs.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
class Clock;

//## auto_generated
class Display;

//## auto_generated
class Joystick;

//## auto_generated
class Led;

//## auto_generated
class LedBar;

//## auto_generated
class RunningIndicatorLed;

//## auto_generated
class SDCard;

//## auto_generated
class TestBuilder;

//#[ ignore
#define evToggle_DefaultPkg_id 16401

#define evOn_DefaultPkg_id 16402

#define evOff_DefaultPkg_id 16403

#define evJoystickPos_DefaultPkg_id 16404

#define evBlink_DefaultPkg_id 16405

#define evSDLog_DefaultPkg_id 16406

#define evError_DefaultPkg_id 16407

#define evSDLog2_DefaultPkg_id 16408
//#]

//## package DefaultPkg


//## type DIRECTION
enum DIRECTION {
    Joystick_SELECT = 0x78,
    Joystick_LEFT = 0x39,
    Joystick_UP = 0x71,
    Joystick_RIGHT = 0x69,
    Joystick_DOWN = 0x59,
    Joystick_CENTER = 0x79
};

//## type LED
enum LED {
    LED2_3 = 3,
    LED2_4 = 4,
    LED2_5 = 5,
    LED2_6 = 6,
    enumerationliteral_4
};

//#[ ignore
#define Joystick_Mask 0x79
//#]

//## event evToggle()
class evToggle : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evToggle();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evOn()
class evOn : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evOn();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evOff()
class evOff : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evOff();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evJoystickPos(char)
class evJoystickPos : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evJoystickPos(char p_joystickPosition);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    char joystickPosition;		//## auto_generated
};

uint16 WSTMonitor_getTypeSize0();

//## event evBlink()
class evBlink : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evBlink();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evSDLog(char*)
class evSDLog : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evSDLog(char* p_message);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    char* message;		//## auto_generated
};

//## event evError()
class evError : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evError();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evSDLog2(OMString)
class evSDLog2 : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evSDLog2(OMString p_message);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    OMString message;		//## auto_generated
};

uint16 WSTMonitor_getTypeSize1();

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\DefaultPkg.h
*********************************************************************/
