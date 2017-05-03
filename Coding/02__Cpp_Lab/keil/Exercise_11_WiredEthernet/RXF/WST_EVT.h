#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_EVT
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_EVT.h
*********************************************************************/

#ifndef WST_EVT_H
#define WST_EVT_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]

//## package RXF::RXF_BehaviorPkg

//## class WST_EVT
// Willert Software Tools - C++ Realtime eXecution Framework (RXF)
// 
// WST_EVT represents an event / asynchronous message in the RXF.
// 
// $Id: WST_EVT.h 35767 2016-10-28 13:31:14Z mspieker $
// $URL: https://svn.willert.de/V6/trunk/Component/Shared/Source/CPP/WST_EVT.h $
// 
// This file belongs to the Willert Software Tools RXF Product:  
// Rpy_CPP_CMSIS_Keil5_ARM_MCB1700_TD_V6.01 (2017-02-27).
// 
// Email: support(at)willert.de
// 
// Copyright (c) 2012, Willert Software Tools GmbH.

//## WSTStartBehavior_id
#define WSTStartBehavior_id -5

//## WST_EVT_delete_id
#define WST_TMR_delete_id -4

//## WST_EVT_null_id
#define WST_EVT_null_id -1

//## WST_TMR_id
#define WST_TMR_id -2

class WST_EVT {
	////    Constructors and destructors    ////
	
public :

	//## operation ~WST_EVT()
	WST_EVT( void ) : isStatic(WSTFALSE) {}
		
	//## operation ~WST_EVT()
	virtual ~WST_EVT( void ){}
	
	////    Operations    ////
	
	//## operation isTypeOf(WST_EVT_ID_t)
	WST_INLINE_OP WSTBoolean isTypeOf(const WST_EVT_ID_t eventId) { return eventId == id; }
	
	//## operation operator setPort(WST_FSM *)
	WST_INLINE_OP void setPort(void* p_port) { port = p_port; }
	
	//## operation operator getPort()
	WST_INLINE_OP void* getPort() { return port; }

	//## operation toBeCancelled(WST_FSM,WST_EVT_ID_t)
	WSTBoolean toBeCancelled(const WST_FSM* destination, const WST_EVT_ID_t id);
	
	////    Additional operations    ////
	
	//## operation operator delete(void *)
	WST_INLINE_OP void operator delete(void * ptr)
	{
		WST_MEM::returnMemory( ptr );
	}
	
	//## operation operator new(size_t)
	WST_INLINE_OP void * operator new(size_t size)
	{
		return WST_MEM::getMemory( size );
	}
	
	//## auto_generated
	WST_INLINE_OP WST_EVT_ID_t getId( void ) { return id; }
	
	//## auto_generated
	WST_INLINE_OP void setId(WST_EVT_ID_t p_id) { id = p_id; }
	
	//## auto_generated
	WST_INLINE_OP WSTBoolean getIsStatic( void ) { return isStatic; }
	
	//## auto_generated
	WST_INLINE_OP void setIsStatic(bool p_isStatic) { isStatic = p_isStatic; }
	
	//## auto_generated
	WST_INLINE_OP void setDeleteAfterConsume(bool p_isStatic) { isStatic = !p_isStatic; }



#ifdef WST_LIVE_ANIMATION     
	//## auto_generated
	WST_INLINE_OP void* getSource( void ) { return source; }
	
	//## auto_generated
	WST_INLINE_OP void setSource(void* p_source) { source = p_source; }
	
		//## auto_generated
	WST_INLINE_OP uint8 getSize( void ) { return size; }
	
	//## auto_generated
	WST_INLINE_OP void setEventID( uint32 p_eventID ) { eventID = p_eventID; }
	
		//## auto_generated
	WST_INLINE_OP uint32 getEventID( void ) { return eventID; }
	
	//## auto_generated
	WST_INLINE_OP void setSize(uint8 p_size) { size = p_size; }
#endif /* WST_LIVE_ANIMATION */
    
	//## auto_generated
	WST_INLINE_OP WST_FSM* getDestination( void ) { return destination; }
	
	//## auto_generated
	WST_INLINE_OP void setDestination(WST_FSM* p_destination) { destination = p_destination; }
	
private :
	
	//## auto_generated
	void cleanUpRelations( void );
	
	////    Attributes    ////
	
	void * port;		//## attribute port
	


protected :
	
	WST_FSM* destination;		//## link destination

	
#ifdef WST_LIVE_ANIMATION 	    
	void* source;		//## attribute source
#endif /* WST_LIVE_ANIMATION */

	
	WST_EVT_ID_t id;		//## attribute id


	
	
#ifdef WST_LIVE_ANIMATION 
	uint32 eventID;	  //## attribute eventID
	   
	uint8 size;		//## attribute size
#endif /* WST_LIVE_ANIMATION */


private :
	
	
	WSTBoolean isStatic;		//## attribute isStatic
	 
	

};


#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_EVT.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
