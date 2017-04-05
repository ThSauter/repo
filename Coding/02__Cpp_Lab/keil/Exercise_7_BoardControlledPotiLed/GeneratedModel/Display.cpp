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

void Display::drawString(unsigned int x, unsigned int y, char* string) {
    //#[ operation drawString(unsigned int,unsigned int,char*)
    GLCD_DrawString(2,3,string); //line,column, text as char-Array
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

/*********************************************************************
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/
