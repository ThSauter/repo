/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Display
//!	Generated Date	: Fri, 14, Apr 2017  
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/

#ifndef Display_H
#define Display_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "Default.h"
//## dependency Board_GLCD
//#[ ignore
extern "C" {

//#]
#include <Board_GLCD.h>
}
//## dependency GLCD_config
#include <GLCD_config.h>
//## class Display
#include "PotiObserver.h"
//## operation Display(Poti)
class Poti;

//## auto_generated
class PotiSubject;

//## package Default

//## class Display
class Display : public PotiObserver {
    ////    Constructors and destructors    ////
    
public :

    //## operation Display(Poti)
    Display(Poti* poti);
    
    //## auto_generated
    Display();
    
    //## auto_generated
    virtual ~Display();
    
    ////    Operations    ////
    
    //## operation drawString()
    void drawString();
    
    //## operation update(PotiSubject)
    virtual void update(PotiSubject* potiSubject);
    
    ////    Additional operations    ////

private :

    //## auto_generated
    Poti* get_poti() const;
    
    //## auto_generated
    void set_poti(Poti* p__poti);
    
    //## auto_generated
    int get_potiVal() const;
    
    //## auto_generated
    void set_potiVal(int p__potiVal);
    
    ////    Attributes    ////

protected :

    Poti* _poti;		//## attribute _poti
    
    int _potiVal;		//## attribute _potiVal
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Display.h
*********************************************************************/
