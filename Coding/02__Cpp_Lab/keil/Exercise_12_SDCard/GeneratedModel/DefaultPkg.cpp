/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: DefaultPkg
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\DefaultPkg.cpp
*********************************************************************/

//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "Clock.h"
//## auto_generated
#include "Display.h"
//## auto_generated
#include "Joystick.h"
//## auto_generated
#include "Led.h"
//## auto_generated
#include "LedBar.h"
//## auto_generated
#include "RunningIndicatorLed.h"
//## auto_generated
#include "SDCard.h"
//## auto_generated
#include "TestBuilder.h"
//## package DefaultPkg



//## event evToggle()
evToggle::evToggle() {
    setId(evToggle_DefaultPkg_id);
    this->size = sizeof( evToggle ) - sizeof( WST_EVT );
}

bool evToggle::isTypeOf(WST_EVT_ID_t id) const {
    return (evToggle_DefaultPkg_id==id);
}

//## event evOn()
evOn::evOn() {
    setId(evOn_DefaultPkg_id);
    this->size = sizeof( evOn ) - sizeof( WST_EVT );
}

bool evOn::isTypeOf(WST_EVT_ID_t id) const {
    return (evOn_DefaultPkg_id==id);
}

//## event evOff()
evOff::evOff() {
    setId(evOff_DefaultPkg_id);
    this->size = sizeof( evOff ) - sizeof( WST_EVT );
}

bool evOff::isTypeOf(WST_EVT_ID_t id) const {
    return (evOff_DefaultPkg_id==id);
}

//## event evJoystickPos(char)
evJoystickPos::evJoystickPos(char p_joystickPosition) : joystickPosition(p_joystickPosition) {
    setId(evJoystickPos_DefaultPkg_id);
    this->size = sizeof( evJoystickPos ) - sizeof( WST_EVT );
}

bool evJoystickPos::isTypeOf(WST_EVT_ID_t id) const {
    return (evJoystickPos_DefaultPkg_id==id);
}

uint16 WSTMonitor_getTypeSize0() {
    return sizeof( char );
}

//## event evBlink()
evBlink::evBlink() {
    setId(evBlink_DefaultPkg_id);
    this->size = sizeof( evBlink ) - sizeof( WST_EVT );
}

bool evBlink::isTypeOf(WST_EVT_ID_t id) const {
    return (evBlink_DefaultPkg_id==id);
}

//## event evSDLog(char*)
evSDLog::evSDLog(char* p_message) : message(p_message) {
    setId(evSDLog_DefaultPkg_id);
    this->size = sizeof( evSDLog ) - sizeof( WST_EVT );
}

bool evSDLog::isTypeOf(WST_EVT_ID_t id) const {
    return (evSDLog_DefaultPkg_id==id);
}

//## event evError()
evError::evError() {
    setId(evError_DefaultPkg_id);
    this->size = sizeof( evError ) - sizeof( WST_EVT );
}

bool evError::isTypeOf(WST_EVT_ID_t id) const {
    return (evError_DefaultPkg_id==id);
}

//## event evSDLog2(OMString)
evSDLog2::evSDLog2(OMString p_message) : message(p_message) {
    setId(evSDLog2_DefaultPkg_id);
    this->size = sizeof( evSDLog2 ) - sizeof( WST_EVT );
}

bool evSDLog2::isTypeOf(WST_EVT_ID_t id) const {
    return (evSDLog2_DefaultPkg_id==id);
}

uint16 WSTMonitor_getTypeSize1() {
    return sizeof( OMString );
}

/*********************************************************************
	File Path	: MCB1700\Debug\DefaultPkg.cpp
*********************************************************************/
