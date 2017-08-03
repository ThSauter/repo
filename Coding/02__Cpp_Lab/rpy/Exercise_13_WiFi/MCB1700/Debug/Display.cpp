/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Display.h"
//## package DefaultPkg

//## class Display
Display::Display(WST_TSK* myTask) {
    setTask( myTask, false );
    initStatechart();
    //#[ operation Display()
    extern GLCD_FONT GLCD_Font_6x8;
    extern GLCD_FONT GLCD_Font_16x24;
    
    
    GLCD_Initialize();
    GLCD_SetBackgroundColor(GLCD_COLOR_LIGHT_GREY);
    GLCD_SetForegroundColor(GLCD_COLOR_BLACK);					
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();
    GLCD_DrawString(0, 1*24, "        WiFi        "); 
    GLCD_SetFont(&GLCD_Font_6x8);		  
    
    // Show initially last Rx Position
    GLCD_DrawString(0, 3*24 + 4*8, "  Last Rx Position:         ");
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 106, (void*)&rootState_subState);
    
    //#]
}

Display::~Display() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
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

bool Display::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    return done;
}

void Display::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
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
