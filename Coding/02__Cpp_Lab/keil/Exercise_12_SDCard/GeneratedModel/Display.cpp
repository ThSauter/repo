/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Thu, 1, Jun 2017  
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
    GLCD_SetBackgroundColor(GLCD_COLOR_YELLOW);
    GLCD_SetForegroundColor(GLCD_COLOR_BLACK);  
    
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();
    GLCD_DrawString(0, 1*24, "      SD Card      "); 
    GLCD_SetFont(&GLCD_Font_6x8);	
    
    // Initial logging and horizontal line
    GLCD_DrawString(0, 3*24 + 0*8, "  Logging  "); 
    GLCD_DrawHLine(5, 3*24 + 1*8, 310);
    this->setOwner( this );
    WSTMonitor_sendInit( this, 106, (void*)&loggedLines);
    
    //#]
}

Display::~Display() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void Display::drawSDCardLogging2() {
    //#[ operation drawSDCardLogging2()
    int i = 0;
    OMIterator<OMString> iter(loggedLines);
    
    while (*iter){	
    	
    	// Check if the string ends with '\n'.  	
    	if ((*iter).GetAt((*iter).GetLength()-1) == '\n')
    	{   
    		// Replace '\n' by ' '
    		(*iter).SetAt((*iter).GetLength()-1,' ');
    	}
    	
    	GLCD_DrawString(0, 3*24 + (2+i)*8, "  " + (*iter) + "    ");
    	iter++; 
    	i++;
    }
    //#]
}

void Display::drawSDCardStatus(const char* logMessage) {
    //#[ operation drawSDCardStatus(char*)
    char str[55];
    
    // Override an old status
    sprintf(str, "  Status:                                    ");
    GLCD_DrawString(0, 3*24 + 0*8, str); 
    
    // Draw the new status
    sprintf(str, "  Status: %s  ", logMessage);
    GLCD_DrawString(0, 3*24 + 0*8, str);
    //#]
}

OMIterator<OMString> Display::getLoggedLines() const {
    OMIterator<OMString> iter(loggedLines);
    return iter;
}

void Display::setLoggedLines(OMString p_loggedLines) {
    loggedLines.add(p_loggedLines);
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

uint16 Display::ClassWSTMonitor_getTypeSize10() {
    return sizeof( OMList<OMString> );
}

void Display::rootState_entDef() {
    {
        rootState_subState = draw_line;
        rootState_active = draw_line;
        //#[ state draw_line.(Entry) 
        drawSDCardLogging2();
        //#]
    }
}

IOxfReactive::TakeEventStatus Display::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    switch (rootState_active) {
        // State draw_line
        case draw_line:
        {
            if(IS_EVENT_TYPE_OF(evSDLog2_DefaultPkg_id))
                {
                    OMSETPARAMS(evSDLog2);
                    //## transition 2 
                    if(loggedLines.getCount() > 7)
                        {
                            //#[ transition 0 
                            loggedLines.add(params->message);
                            //#]
                            pushNullTransition();
                            rootState_subState = remove_line;
                            rootState_active = remove_line;
                            //#[ state remove_line.(Entry) 
                            loggedLines.removeFirst();
                            //#]
                            res = eventConsumed;
                        }
                    else
                        {
                            //#[ transition 0 
                            loggedLines.add(params->message);
                            //#]
                            rootState_subState = draw_line;
                            rootState_active = draw_line;
                            //#[ state draw_line.(Entry) 
                            drawSDCardLogging2();
                            //#]
                            res = eventConsumed;
                        }
                }
            
        }
        break;
        // State remove_line
        case remove_line:
        {
            if(IS_EVENT_TYPE_OF(WST_EVT_null_id ))
                {
                    popNullTransition();
                    rootState_subState = draw_line;
                    rootState_active = draw_line;
                    //#[ state draw_line.(Entry) 
                    drawSDCardLogging2();
                    //#]
                    res = eventConsumed;
                }
            
        }
        break;
        default:
            break;
    }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

uint16 WSTMonitor_getTypeSize10() {
    return Display::ClassWSTMonitor_getTypeSize10( );
}

/*********************************************************************
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/
