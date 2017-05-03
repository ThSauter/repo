/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/

//## auto_generated
#include "Display.h"
//## operation Display(Poti)
#include "Poti.h"
//## auto_generated
#include "PotiSubject.h"
//## package Default

//## class Display
Display::Display(Poti* poti) {
    //#[ operation Display(Poti)
    _poti = poti;
    _poti->subscribe(this);
    
    extern GLCD_FONT GLCD_Font_16x24; //in case you don’t want to
    // use the default string
    GLCD_Initialize();
    GLCD_SetBackgroundColor(GLCD_COLOR_WHITE);
    GLCD_SetForegroundColor(GLCD_COLOR_BLUE);
    GLCD_SetFont(&GLCD_Font_16x24);
    GLCD_ClearScreen();
    //#]
}

Display::Display() {
}

Display::~Display() {
}

void Display::drawString() {
    //#[ operation drawString()
    char str[20];
    sprintf(str, "Poti value: %i", _potiVal);
    GLCD_DrawString(2,3,str);
    //#]
}

void Display::update(PotiSubject* potiSubject) {
    //#[ operation update(PotiSubject)
    if (potiSubject == _poti)  
    {
        _potiVal = _poti->getPotiVal();  
        drawString();
    }
    //#]
}

Poti* Display::get_poti() const {
    return _poti;
}

void Display::set_poti(Poti* p__poti) {
    _poti = p__poti;
}

int Display::get_potiVal() const {
    return _potiVal;
}

void Display::set_potiVal(int p__potiVal) {
    _potiVal = p__potiVal;
}

/*********************************************************************
	File Path	: MCB1700\Debug\Display.cpp
*********************************************************************/
