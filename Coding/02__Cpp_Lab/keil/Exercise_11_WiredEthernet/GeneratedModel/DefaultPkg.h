/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: DefaultPkg
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\DefaultPkg.h
*********************************************************************/

#ifndef DefaultPkg_H
#define DefaultPkg_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
class Display;

//## auto_generated
class EthernetController;

//## auto_generated
class EthernetReceiver;

//## auto_generated
class EthernetTransmitter;

//## auto_generated
class Joystick;

//## auto_generated
class Led;

//## auto_generated
class LedBar;

//## auto_generated
class RunningIndicatorLed;

//## auto_generated
class TestBuilder;

//#[ ignore
#define evToggle_DefaultPkg_id 16401

#define evOn_DefaultPkg_id 16402

#define evOff_DefaultPkg_id 16403

#define evReceivedData_DefaultPkg_id 16404

#define evNewJoystickPosition_DefaultPkg_id 16405

#define evBlink_DefaultPkg_id 16406
//#]

//## package DefaultPkg


//## type DIRECTION
enum DIRECTION {
    Joystick_SELECT = 0x0,
    Joystick_LEFT = 0x7,
    Joystick_UP = 0xE,
    Joystick_RIGHT = 0xD,
    Joystick_DOWN = 0xB,
    Joystick_CENTER = 0xF
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

//## event evReceivedData(char)
class evReceivedData : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evReceivedData(char p_data);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    char data;		//## auto_generated
};

uint16 WSTMonitor_getTypeSize0();

//## event evNewJoystickPosition(char)
class evNewJoystickPosition : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evNewJoystickPosition(char p_joystickPosition);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    char joystickPosition;		//## auto_generated
};

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

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\DefaultPkg.h
*********************************************************************/
