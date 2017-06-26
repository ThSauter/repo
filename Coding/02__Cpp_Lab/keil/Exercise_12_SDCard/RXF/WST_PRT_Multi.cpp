/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MSQ
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.cpp
*********************************************************************/

//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg


/* ------ Start WST_InBoundMulti ----- */

WST_InBoundMulti::WST_InBoundMulti(){
	destination = NULL;
	parent = NULL;
}

void WST_InBoundMulti::setPort(WST_PRT_MULTI *port){
	parent = port;
}


void WST_InBoundMulti::setItsDefaultProvidedInterface( WST_FSM * part){
	addItsDefaultProvidedInterface( part );
}
void WST_InBoundMulti::addItsDefaultProvidedInterface( WST_FSM* part ){
	destination = part;
}

WST_FSM* WST_InBoundMulti::getDestination(){
	return destination;
}

//## operation ~WST_InBoundMulti()
WST_InBoundMulti::~WST_InBoundMulti( void ){
	
}



/* ------ End WST_InBoundMulti ----- */




/* ------ Start WST_OutBoundMulti ----- */

WST_OutBoundMulti::WST_OutBoundMulti(){
	start = NULL;
}

WSTPortOutList* WST_OutBoundMulti::getStart(){
	return start;
}

void WST_OutBoundMulti::addItsDefaultProvidedInterface(WST_InBoundMulti *part){
	WSTPortOutList *tmp = start;
	
	
	/* First Copy InPort Data of extern Port */
	WSTPortOutList *newPort;
	if( start == NULL ){ /* If first part is added use static data (For single Ports)*/ 
		newPort = &firstStatic;
	}
	else
	{
		newPort = (WSTPortOutList*)WST_MEM::getMemory( sizeof( WSTPortOutList ) );
	}
	
	newPort->destination = part;
	newPort->next = NULL;

	/* Second add first New Port to OutBound List */
	if( start == NULL) 
	{
		start = newPort;
	}
	else
	{
		while( tmp->next != NULL ){
			tmp = tmp->next;
		}
		tmp->next = newPort;
	}
}

//## operation ~WST_InBoundMulti()
WST_OutBoundMulti::~WST_OutBoundMulti( void ){
	
}

/* ------ End WST_OutBoundMulti ----- */




/* ------ Start WST_PRT_MULTI ----- */

/* Setze ausgehende Ports */
void WST_PRT_MULTI::addItsDefaultRequiredInterface(WST_InBoundMulti *part){
	OutBound.addItsDefaultProvidedInterface( part );
}

/* Setze ausgehende Ports */
void WST_PRT_MULTI::setItsDefaultRequiredInterface(WST_InBoundMulti *part){
	OutBound.addItsDefaultProvidedInterface( part );
}

/* Setze ausgehende Ports */
WST_InBoundMulti* WST_PRT_MULTI::getItsDefaultProvidedInterface(){
	return &InBound;
}

void WST_PRT_MULTI::send(WST_EVT *event){
	if(OutBound.getStart() != NULL){
		#ifdef WST_LIVE_ANIMATION
			event->setSource( InBound.getDestination() );
		#endif
		
		OutBound.getStart()->destination->getDestination()->gen( event, false );
	}
}


WST_PRT_MULTI::~WST_PRT_MULTI( void ){
	
}

/* ------ End WST_PRT_MULTI ----- */




/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MSQ.cpp
*********************************************************************/
