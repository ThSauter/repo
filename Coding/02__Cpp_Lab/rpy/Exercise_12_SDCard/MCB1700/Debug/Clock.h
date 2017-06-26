/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Clock
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\Clock.h
*********************************************************************/

#ifndef Clock_H
#define Clock_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "rl_fs.h"
//## auto_generated
#include <lpc17xx.h>
//## auto_generated
#include "DefaultPkg.h"
//## package DefaultPkg

//## class Clock
class Clock {
public :

//#[ ignore
    #define SBIT_CLKEN     0    /* RTC Clock Enable*/
    #define SBIT_CTCRST    1    /* RTC Clock Reset */
    #define SBIT_CCALEN    4    /* RTC Calibration counter enable */
//#]

    ////    Constructors and destructors    ////
    
    //## operation Clock()
    Clock();
    
    //## auto_generated
    virtual ~Clock();
    
    ////    Operations    ////
    
    //## operation getHour()
    unsigned char getHour();
    
    //## operation getMin()
    unsigned char getMin();
    
    //## operation getSec()
    unsigned char getSec();
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\Clock.h
*********************************************************************/
