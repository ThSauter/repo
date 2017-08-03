/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_PRT
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_PRT.h
*********************************************************************/

#ifndef WST_PRT_H
#define WST_PRT_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_PRT
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_PRT represents an event / asynchronous message in the RXF.
// 
// $Id: WST_PRT_Multi.h 32759 2015-07-25 11:27:59Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_PRT_Multi.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.

class WST_PRT;
class WST_PRT_MULTI;
class WST_InBoundMulti;

struct WSTPortOutList{
	WST_InBoundMulti *destination;
	WSTPortOutList *next;
};

class WST_OutBoundMulti {
    ////    Constructors and destructors    ////
	
private:
	WSTPortOutList* start;
	WSTPortOutList firstStatic;
    
public:
    
    //## operation ~WST_InBoundMulti()
    virtual ~WST_OutBoundMulti( void );

	//## operation WST_InBoundMulti()
    WST_OutBoundMulti( void );

    //## operation setItsDefaultProvidedInterface()
    void setItsDefaultProvidedInterface( WST_FSM* part );

	void setPort( WST_PRT_MULTI *part);

	void addItsDefaultProvidedInterface( WST_InBoundMulti *part );

	WSTPortOutList* getStart();

};


class WST_InBoundMulti {
    ////    Constructors and destructors    ////
	
private:
	WST_PRT_MULTI *parent;
	WST_FSM* destination;
    
public:
    
    //## operation ~WST_InBoundMulti()
    virtual ~WST_InBoundMulti( void );

	//## operation WST_InBoundMulti()
    WST_InBoundMulti( void );

	void addItsDefaultProvidedInterface( WST_FSM * part);

	void setItsDefaultProvidedInterface( WST_FSM * part);

	void setPort(WST_PRT_MULTI *port);

	WST_FSM* getDestination();

};


class WST_PRT_MULTI {
    ////    Constructors and destructors    ////
    
public:

    
    //## operation ~WST_PRT()
    virtual ~WST_PRT_MULTI( void );

	void send(WST_EVT *event);

	void addItsDefaultRequiredInterface(WST_InBoundMulti *part);

	void setItsDefaultRequiredInterface(WST_InBoundMulti *part);

	WST_InBoundMulti* getItsDefaultProvidedInterface(void);

	WST_OutBoundMulti OutBound;

	WST_InBoundMulti InBound;


};


#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_PRT.h
*********************************************************************/
