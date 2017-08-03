/********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Tue, 1, Aug 2017  
	File Path	: MCB1700/Debug/Display.cpp
*********************************************************************/

//## auto_generated
#include <oxf/omthread.h>
//## auto_generated
#include "Display.h"
//## link itsEthernetReceiver
#include "EthernetReceiver.h"
//## package DefaultPkg

//## class Display
Display::Display(IOxfActive* theActiveContext) {
    setActiveContext(theActiveContext, false);
    itsEthernetReceiver = NULL;
    initStatechart();
    //#[ operation Display()
    const char* hostIpAddr;
    const char* remoteIpAddr;
    char str[40];
    
    extern GLCD_FONT GLCD_Font_6x8;
    extern GLCD_FONT GLCD_Font_16x24;
    
    hostIpAddr = itsEthernetReceiver->getHostIpAddress();
    remoteIpAddr = itsEthernetReceiver->getRemoteIpAddress();
    
    GLCD_Initialize();
    
    if (strcmp(hostIpAddr,"192.168.0.100") == 0)
    {
    	GLCD_SetBackgroundColor(GLCD_COLOR_GREEN);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);			
    }
    else if (strcmp(hostIpAddr,"192.168.0.101") == 0)
    {
    	GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);			
    }
    else
    {
    	GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);					
    }
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();
    GLCD_DrawString(0, 1*24, "   Wired Ethernet   "); 
    GLCD_SetFont(&GLCD_Font_6x8);		
    sprintf(str, "  Host IP:   %s "    , hostIpAddr);
    GLCD_DrawString(0, 3*24 + 0*8, str); 
    sprintf(str, "  Remote IP: %s "    , remoteIpAddr);
    GLCD_DrawString(0, 3*24 + 2*8, str);   
    
    // Show initially last Rx Position
    GLCD_DrawString(0, 3*24 + 4*8, "  Last Rx Position:         ");
    
    //#]
}

Display::~Display() {
    cleanUpRelations();
}

void Display::drawReceivedPosition(char data) {
    //#[ operation drawReceivedPosition(char)
    char str[40];
    const char* direction;
    
    switch(data)
    {
    	case Joystick_LEFT: 
    		direction = "LEFT"; 
    		break;
    	case Joystick_UP: 
    		direction = "UP"; 
    		break;
    	case Joystick_RIGHT: 
    		direction = "RIGHT";
    		break;
    	case Joystick_DOWN: 
    		direction = "DOWN";
    		break;
    	case Joystick_CENTER: 
    		//TODO
    		break;
    	default:
    		break;
    }
    
    sprintf(str, "  Last Rx Position: %s      ", direction);
    GLCD_DrawString(0, 3*24 + 4*8, str);
    //#]
}

EthernetReceiver* Display::getItsEthernetReceiver() const {
    return itsEthernetReceiver;
}

void Display::setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver) {
    if(p_EthernetReceiver != NULL)
        {
            p_EthernetReceiver->_setItsDisplay(this);
        }
    _setItsEthernetReceiver(p_EthernetReceiver);
}

bool Display::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    return done;
}

void Display::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void Display::cleanUpRelations() {
    if(itsEthernetReceiver != NULL)
        {
            Display* p_Display = itsEthernetReceiver->getItsDisplay();
            if(p_Display != NULL)
                {
                    itsEthernetReceiver->__setItsDisplay(NULL);
                }
            itsEthernetReceiver = NULL;
        }
}

void Display::__setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver) {
    itsEthernetReceiver = p_EthernetReceiver;
}

void Display::_setItsEthernetReceiver(EthernetReceiver* p_EthernetReceiver) {
    if(itsEthernetReceiver != NULL)
        {
            itsEthernetReceiver->__setItsDisplay(NULL);
        }
    __setItsEthernetReceiver(p_EthernetReceiver);
}

void Display::_clearItsEthernetReceiver() {
    itsEthernetReceiver = NULL;
}

void Display::rootState_entDef() {
    {
        rootState_subState = Refresh;
        rootState_active = Refresh;
    }
}

IOxfReactive::TakeEventStatus Display::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Refresh
    if(rootState_active == Refresh)
        {
            if(IS_EVENT_TYPE_OF(evReceivedData_DefaultPkg_id))
                {
                    OMSETPARAMS(evReceivedData);
                    //#[ transition 0 
                    drawReceivedPosition(params->data);
                    //#]
                    rootState_subState = Refresh;
                    rootState_active = Refresh;
                    res = eventConsumed;
                }
            
        }
    return res;
}

/*********************************************************************
	File Path	: MCB1700/Debug/Display.cpp
*********************************************************************/
