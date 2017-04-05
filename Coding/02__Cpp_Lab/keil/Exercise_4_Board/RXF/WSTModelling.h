#ifndef WSTMODELLING_H 
#define WSTMODELLING_H 


#define eventNotConsumed		WST_EVT_handleEventNotConsumed
#define eventError			    WST_EVT_handleEventError
#define eventConsumed			WST_EVT_handleEventConsumed
#define eventCompleted			WST_EVT_handleEventCompleted
#define eventInCleanup			WST_EVT_handleEventInCleanup
#define eventReachTerminate		WST_EVT_handleEventReachTerminate

#define IOxfTimeout				WST_TMR
#define IOxfEvent	WST_EVT
#define IOxfReactive WST_FSM
#define OMReactive WST_FSM
#define IOxfEventGenerationParams void*
#define IOxfActive WST_TSK
typedef OMString RhpString;

#define RhpBoolean bool


#define OMDECLARE_GUARDED public:\
	WST_MTX mutex;
#define GUARD_OPERATION WST_MTX_inUse tmpMutex(&mutex);



#ifndef NULL
#define NULL 0
#endif /* NULL */

#define OXF WST_RXF


#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define IS_IN(state) state##_IN()
#else
#define IS_IN(state) state->in()
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION

// Test if the current event is of the type of the given id.
// A macro is used to support both flat and reusable statechart implementation.
//#[ type IS_EVENT_TYPE_OF
#ifndef OM_REUSABLE_STATECHART_IMPLEMENTATION
#define IS_EVENT_TYPE_OF(id) ((getCurrentEvent() != 0) ? getCurrentEvent()->isTypeOf((id)) : false)
#else
#define IS_EVENT_TYPE_OF(id) (((concept != 0) && ((concept->getCurrentEvent()) != 0)) ? (concept->getCurrentEvent())->isTypeOf((id)) : false)
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]

#define GEN(EVENT)  send( new EVENT ) 

#ifdef WST_LIVE_ANIMATION

#define FIRE_PORT(PORT,EVENT)               			\
{														\
	WST_EVT* event = new EVENT;							\
	event->setSource( this );							\
	(PORT).getOutBound()->send( event );									\
}

#define FIRE_PORT_MULTI(PORT,EVENT)									\
if(PORT.OutBound.getStart() != NULL ){								\
	WSTPortOutList* first = (PORT).OutBound.getStart();				\
	WST_EVT *event;													\
	while( first != NULL ){											\
		event = new EVENT;											\
		event->setSource( this );									\
		first->destination->getDestination()->gen( event, WSTFALSE );	\
		first = first->next;										\
	}																\
}

#define FIRE(DESTINATION,EVENT)												\
{																			\
	if ((DESTINATION) != NULL) {											\
		WST_EVT*  event = new EVENT;										\
		event->setSource( this );											\
		(DESTINATION)->gen(event, WSTFALSE);									\
	}																		\
}

#define FIRE_ISR(DESTINATION,EVENT)											\
{																			\
	if ((DESTINATION) != NULL) {											\
		EVENT->setSource( this );											\
		(DESTINATION)->gen(EVENT, WSTTRUE);									\
	}																		\
}

#define FIRE_ISR_ARRAY( DESTINATION, EVENT_ARRAY, INDEX_ATTR, SIZE ) {			\
	if( (INDEX_ATTR) >= (SIZE) )												\
	{																			\
	  INDEX_ATTR = 0;															\
	}																			\
	if ( (DESTINATION) != NULL)													\
	{																			\
		(EVENT_ARRAY[INDEX_ATTR]).setSource( this );							\
		(DESTINATION)->gen( &(EVENT_ARRAY[INDEX_ATTR]), WSTTRUE);				\
	}																			\
	INDEX_ATTR++;																\
}


#else /* WST_LIVE_ANIMATION */

#define FIRE_PORT(PORT,EVENT)               			\
{														\
	WST_EVT* event = new EVENT;							\
	(PORT).getOutBound()->send( event );								\
}

#define FIRE_PORT_MULTI(PORT,EVENT)									\
if(PORT.OutBound.getStart() != NULL ){								\
	WSTPortOutList* first = (PORT).OutBound.getStart();				\
	WST_EVT *event;													\
	while( first != NULL ){											\
		event = new EVENT;											\
		first->destination->getDestination()->gen( event, WSTFALSE );	\
		first = first->next;										\
	}																\
}


#define FIRE(DESTINATION,EVENT) 											\
{																			\
	if ((DESTINATION) != NULL) {											\
		WST_EVT*  event = new EVENT;										\
		(DESTINATION)->gen(event, WSTFALSE);									\
	}																		\
}
#define FIRE_ISR(DESTINATION,EVENT) 										\
{																			\
	if ((DESTINATION) != NULL) {											\
		(DESTINATION)->gen(EVENT, WSTTRUE);									\
	}																		\
}

#define FIRE_ISR_ARRAY( DESTINATION, EVENT_ARRAY, INDEX_ATTR, SIZE ) {			\
	if( (INDEX_ATTR) >= (SIZE) )												\
	{																			\
	  INDEX_ATTR = 0;															\
	}																			\
	if ( (DESTINATION) != NULL)													\
	{																			\
		(DESTINATION)->gen( &(EVENT_ARRAY[INDEX_ATTR]), WSTTRUE);				\
	}																			\
	INDEX_ATTR++;																\
}


#endif /* of WST_LIVE_ANIMATION */



#define WST_EVT_initStaticEventArray( EVENT_ARRAY, SIZE ) {	\
	int index;																	\
	for( index = 0; index < (SIZE); index++ )									\
	{																			\
		(EVENT_ARRAY[index]).setIsStatic(WSTTRUE);								\
	}																			\
}	

#define CGEN				FIRE								/** < \req{RXF-999} */
#define CGEN_ISR			FIRE_ISR							/** < \req{RXF-1000} */

#define RiCGEN				FIRE								/** < \req{RXF-1001} */
#define RiCGEN_ISR			FIRE_ISR							/** < \req{RXF-1002} */


#define MULTICAST_GEN		FIRE_PORT_MULTI

	



// Set a triggered operation return value.
// A macro is used to support both flat and reusable statechart implementation.
#define OMREPLY(retVal)		(params->om_reply = retVal)

// Set a local variable  called params of the specific event type to enable access to the current event data.
// A macro is used to support both flat and reusable statechart implementation.
#define OMSETPARAMS(type) type* params = static_cast<type*>(getCurrentEvent())
#define IS_COMPLETED(state) state##_isCompleted()

// Shorted name for OMREPLY
#define reply(retVal)	OMREPLY(retVal)

// Shorted name for OMSETPARAMS
#define SETPARAMS(type) OMSETPARAMS(type)


#endif /* WSTMODELLING_H */ 
