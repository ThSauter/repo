/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TMR
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMR.cpp
*********************************************************************/

//## auto_generated
#include "WST_TMR.h"
//## auto_generated
#include "WST_FSM.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

#if WST_MAX_TIMEOUTS > 0

WST_TMR* itsFreeList;		//## link itsFreeList

WST_TMR itsWST_TMR[WST_MAX_TIMEOUTS];		//## link itsWST_TMR

#endif /* WST_MAX_TIMEOUTS > 0 */

//## class WST_TMR

void WST_TMR::operator delete(void * ptr)
{
#if WST_MAX_TIMEOUTS > 0
	WSTTarget_enterCriticalRegion();
	WST_TMR* tmp = (WST_TMR*)ptr;
	tmp->nextTm = itsFreeList;
	itsFreeList = tmp;
	WSTTarget_exitCriticalRegion();
#else
	WST_MEM::returnMemory( ptr );
#endif
}

void *WST_TMR::operator new(size_t size)
{
#if WST_MAX_TIMEOUTS > 0
	WST_TMR* tmp;
	WSTTarget_enterCriticalRegion();
	tmp = itsFreeList;
	if( itsFreeList == NULL )
	{
		WST_ERR::error( WST_ERR::WST_ERR_TIMEOUT_HEAP_FULL, 0u );
	}
	else
	{		
		itsFreeList = itsFreeList->nextTm;
	}
	WSTTarget_exitCriticalRegion();
	return tmp;
#else /* #if WST_MAX_TIMEOUTS > 0 */
	return WST_MEM::getMemory( sizeof( WST_TMR ) );
#endif /* #if WST_MAX_TIMEOUTS > 0 */
}

void WST_TMR::cancel(){
	WST_TMM::getInst()->stop( this );
}

#if WST_MAX_TIMEOUTS > 0
void WST_TMR::initTimeoutLists()
{
	itsFreeList = &itsWST_TMR[0];
	for( uint16 i = 0; i < WST_MAX_TIMEOUTS - 1; i++ )
	{
		itsWST_TMR[ i ].nextTm = &itsWST_TMR[ i + 1 ];
	}
	itsWST_TMR[ WST_MAX_TIMEOUTS -1 ].nextTm = NULL;
}
#endif /* #if WST_MAX_TIMEOUTS > 0 */



/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TMR.cpp
*********************************************************************/
