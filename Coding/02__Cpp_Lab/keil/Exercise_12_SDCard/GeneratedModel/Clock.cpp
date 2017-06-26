/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: Clock
//!	Generated Date	: Thu, 1, Jun 2017  
	File Path	: MCB1700\Debug\Clock.cpp
*********************************************************************/

//## auto_generated
#include "Clock.h"
//## package DefaultPkg

//## class Clock
Clock::Clock() {
    //#[ operation Clock()
    /* Enable CLOCK into RTC */
    LPC_SC->PCONP |= (1 << 9);
    
    /* Disable RTC clock, reset clock, Enable RTC calibration */
    LPC_RTC->CCR = ((1 << SBIT_CTCRST ) | (1 << SBIT_CCALEN));
    LPC_RTC->CALIBRATION = 0x00;
    LPC_RTC->CCR = (1 << SBIT_CLKEN);    /* Enable the clock for RTC */
    
    // Set Date and Time only once
    // Comment these lines after setting the time and date                                           
    // Set Date 29th May 2017 
    //LPC_RTC->DOM    = 29;   // Update date value 
    //LPC_RTC->MONTH  = 5;   // Update month value
    //LPC_RTC->YEAR   = 2017; // Update year value
    
    // Set Time 22:05:25 AM 
    //LPC_RTC->HOUR   = 22;   // Update hour value 
    //LPC_RTC->MIN    = 05;   // Update min value
    //LPC_RTC->SEC    = 25;   // Update sec value 
    WSTMonitor_sendInit( this, 108, (void*)NULL);
    
    //#]
}

Clock::~Clock() {
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

unsigned char Clock::getHour() {
    //#[ operation getHour()
    return LPC_RTC->HOUR;
    //#]
}

unsigned char Clock::getMin() {
    //#[ operation getMin()
    return LPC_RTC->MIN;
    //#]
}

unsigned char Clock::getSec() {
    //#[ operation getSec()
    return LPC_RTC->SEC; 
    //#]
}

/*********************************************************************
	File Path	: MCB1700\Debug\Clock.cpp
*********************************************************************/
