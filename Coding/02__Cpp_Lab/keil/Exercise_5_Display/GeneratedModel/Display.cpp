/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Mon, 3, Apr 2017  
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/

//## auto_generated
#include "WSTModelHeadersTSK.h"
//## auto_generated
#include "Display.h"
//## link itsBoard
#include "Board.h"
//## package Default

//## class Display
Display::Display(WST_TSK* myTask) {
    setTask( myTask, false );
    itsBoard = NULL;
    initStatechart();
    //#[ operation Display()
    extern GLCD_FONT GLCD_Font_16x24; //in case you don’t want to
    // use the default string
    GLCD_Initialize();
    GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
    GLCD_SetForegroundColor(GLCD_COLOR_BLUE);
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();
    //#]
}

Display::~Display() {
    cleanUpRelations();
}

void Display::drawString(int ledNr) {
    //#[ operation drawString(int)
    char str[20];
    sprintf(str, "LED %i is on", ledNr);
    GLCD_DrawString(2,3,str);
    
    //#]
}

Board* Display::getItsBoard() const {
    return itsBoard;
}

void Display::setItsBoard(Board* p_Board) {
    _setItsBoard(p_Board);
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
    if(itsBoard != NULL)
        {
            itsBoard = NULL;
        }
}

void Display::__setItsBoard(Board* p_Board) {
    itsBoard = p_Board;
}

void Display::_setItsBoard(Board* p_Board) {
    __setItsBoard(p_Board);
}

void Display::_clearItsBoard() {
    itsBoard = NULL;
}

void Display::rootState_entDef() {
    {
        rootState_subState = Display_refresh;
        rootState_active = Display_refresh;
    }
}

IOxfReactive::TakeEventStatus Display::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Display_refresh
    if(rootState_active == Display_refresh)
        {
            if(IS_EVENT_TYPE_OF(evSwitchLed_Default_id))
                {
                    OMSETPARAMS(evSwitchLed);
                    //#[ transition 0 
                    drawString(params->ledNr);
                    //#]
                    rootState_subState = Display_refresh;
                    rootState_active = Display_refresh;
                    res = eventConsumed;
                }
            
        }
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/
