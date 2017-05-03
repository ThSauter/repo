/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Default
//!	Generated Date	: Tue, 25, Apr 2017  
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/

#ifndef Default_H
#define Default_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## classInstance itsBoard
class Board;

//## auto_generated
class Joystick;

//## auto_generated
class Led;

//## auto_generated
class LedBar;

//#[ ignore
#define evNewJoystickPosition_Default_id 18601

#define evToggleLed_Default_id 18602
//#]

//## package Default


//## type DIRECTION
enum DIRECTION {
    Joystick_SELECT = 0x0,
    Joystick_LEFT = 0x7,
    Joystick_UP = 0xE,
    Joystick_RIGHT = 0xD,
    Joystick_DOWN = 0xB,
    Joystick_CENTER = 0xF
};

//#[ ignore
#define Joystick_Mask 0x79
//#]

//## type LED
enum LED {
    LED2_3 = 0,
    LED2_4 = 1,
    LED2_5 = 2,
    LED2_6 = 3
};

//## classInstance itsBoard
extern Board itsBoard;

//## auto_generated
void Default_initRelations();

//## auto_generated
bool Default_startBehavior();

//#[ ignore
class Default_OMInitializer {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    Default_OMInitializer();
    
    //## auto_generated
    virtual ~Default_OMInitializer();
};
//#]

//## event evNewJoystickPosition(int)
class evNewJoystickPosition : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evNewJoystickPosition(int p_joystickPosition);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
    
    ////    Framework    ////
    
    int joystickPosition;		//## auto_generated
};

//## event evToggleLed()
class evToggleLed : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evToggleLed();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Default.h
*********************************************************************/
