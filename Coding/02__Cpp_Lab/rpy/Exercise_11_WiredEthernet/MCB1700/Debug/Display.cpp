/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Wed, 17, May 2017  
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Display.h"
//## link itsEthernetReceiver
#include "EthernetReceiver.h"
//## package DefaultPkg

//## class Display
Display::Display(WST_TSK* myTask) {
    setTask( myTask, false );
    itsEthernetReceiver = NULL;
    initStatechart();
    //#[ operation Display()
    const char* hostIpAddress;
    const char* remoteIpAddress;
    char str[40];
    
    extern GLCD_FONT GLCD_Font_6x8;
    extern GLCD_FONT GLCD_Font_16x24;
    
    // Get the configured IP addresses 
    hostIpAddress = itsEthernetReceiver->getHostIpAddress();
    remoteIpAddress = itsEthernetReceiver->getRemoteIpAddress();
                     
    // Initialize the display
    GLCD_Initialize();
    
    if (strcmp(hostIpAddress,"192.168.0.100") == 0)
    {   
    	// Evaluate if this is the "green" board
    	GLCD_SetBackgroundColor(GLCD_COLOR_GREEN);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);			
    }
    else if (strcmp(hostIpAddress,"192.168.0.101") == 0)
    {    
    	// Evaluate if this is the "blue" board
    	GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);			
    }
    else
    {   
    	// In case any IP is configured
    	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
    	GLCD_SetForegroundColor(GLCD_COLOR_WHITE);					
    }
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();        
    
    // Title
    GLCD_DrawString(0, 1*24, "   Wired Ethernet   "); 
     
    // Host IP
    GLCD_SetFont(&GLCD_Font_6x8);
    sprintf(str, "  Host IP:   %s "    , hostIpAddress);
    GLCD_DrawString(0, 3*24 + 0*8, str);   
    
    // Target IP
    sprintf(str, "  Remote IP: %s "    , remoteIpAddress);
    GLCD_DrawString(0, 3*24 + 2*8, str); 
    
    	// Ensure that this text is shown
    GLCD_DrawString(0, 3*24 + 4*8, "  Last Rx Position:"); 
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 109, (void*)&itsEthernetReceiver);
    
    //#]
}

Display::~Display() {
    cleanUpRelations();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void Display::drawReceivedPosition(char data) {
    //#[ operation drawReceivedPosition(char)
    const char* position;
    char str[40];
    
    switch(data)
    {
    	case Joystick_LEFT: 
    		position = "LEFT"; 
    		break;
    	case Joystick_UP: 
    		position = "UP"; 
    		break;
    	case Joystick_RIGHT: 
    		position = "RIGHT"; 
    		break;
    	case Joystick_DOWN: 
    		position = "DOWN"; 
    		break;
    	case Joystick_CENTER: 
    		position = "CENTER"; 
    		break;
    	default:
    		position = ""; 
    		break; 
    }
    
    sprintf(str, "  Last Rx Position: %s    "    , position);
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
    done = WST_FSM::startBehavior();
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
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/
