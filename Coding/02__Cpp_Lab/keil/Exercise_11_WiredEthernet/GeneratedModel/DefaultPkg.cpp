/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: DefaultPkg
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\DefaultPkg.cpp
*********************************************************************/

//## auto_generated
#include "DefaultPkg.h"
//## auto_generated
#include "Display.h"
//## auto_generated
#include "EthernetController.h"
//## auto_generated
#include "EthernetReceiver.h"
//## auto_generated
#include "EthernetTransmitter.h"
//## auto_generated
#include "Joystick.h"
//## auto_generated
#include "Led.h"
//## auto_generated
#include "LedBar.h"
//## auto_generated
#include "RunningIndicatorLed.h"
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

//## event evReceivedData(char)
evReceivedData::evReceivedData(char p_data) : data(p_data) {
    setId(evReceivedData_DefaultPkg_id);
    this->size = sizeof( evReceivedData ) - sizeof( WST_EVT );
}

bool evReceivedData::isTypeOf(WST_EVT_ID_t id) const {
    return (evReceivedData_DefaultPkg_id==id);
}

uint16 WSTMonitor_getTypeSize0() {
    return sizeof( char );
}

//## event evNewJoystickPosition(char)
evNewJoystickPosition::evNewJoystickPosition(char p_joystickPosition) : joystickPosition(p_joystickPosition) {
    setId(evNewJoystickPosition_DefaultPkg_id);
    this->size = sizeof( evNewJoystickPosition ) - sizeof( WST_EVT );
}

bool evNewJoystickPosition::isTypeOf(WST_EVT_ID_t id) const {
    return (evNewJoystickPosition_DefaultPkg_id==id);
}

//## event evBlink()
evBlink::evBlink() {
    setId(evBlink_DefaultPkg_id);
    this->size = sizeof( evBlink ) - sizeof( WST_EVT );
}

bool evBlink::isTypeOf(WST_EVT_ID_t id) const {
    return (evBlink_DefaultPkg_id==id);
}

/*********************************************************************
	File Path	: MCB1700\Debug\DefaultPkg.cpp
*********************************************************************/
