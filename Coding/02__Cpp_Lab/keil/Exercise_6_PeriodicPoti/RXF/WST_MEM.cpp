/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MEM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM.cpp
*********************************************************************/

//## auto_generated
#include "WST_MEM.h"
//## auto_generated
#include "WST.h"
//## auto_generated
#include <string.h>
//## package RXF::RXF_MemPkg
#include <stdlib.h>

//## class WST_MEM
//#[ ignore

WST_MEM *myInstance;

#if WST_INITIAL_TINY_BUFFERS > 0
	sint16 startTiny;
	WST_MEM_TINY_POOL_DEFINITION
	
#ifdef WST_MEM_USE_TAIL
	sint16 tailTiny;		
#endif /* WST_MEM_USE_TAIL */

 
	uint16 tinyCounter;
 

#endif /* WST_INITIAL_TINY_BUFFERS > 0 */



#if WST_INITIAL_SMALL_BUFFERS > 0
	sint16 startSmall;
	WST_MEM_SMALL_POOL_DEFINITION
#ifdef WST_MEM_USE_TAIL
	sint16 tailSmall;		
#endif /* WST_MEM_USE_TAIL */

 
	uint16 smallCounter;
 

#endif /* WST_INITIAL_SMALL_BUFFERS > 0 */
	
	
	
#if WST_INITIAL_MEDIUM_BUFFERS > 0
	sint16 startMedium;
	WST_MEM_MEDIUM_POOL_DEFINITION
#ifdef WST_MEM_USE_TAIL
	sint16 tailMedium;		
#endif /* WST_MEM_USE_TAIL */

 
	uint16 mediumCounter;
 

#endif /* WST_INITIAL_MEDIUM_BUFFERS > 0 */



#if WST_INITIAL_LARGE_BUFFERS > 0
	sint16 startLarge;
	WST_MEM_LARGE_POOL_DEFINITION	
#ifdef WST_MEM_USE_TAIL
	sint16 tailLarge;		
#endif /* WST_MEM_USE_TAIL */

 
	uint16 largeCounter;
 

#endif /* WST_INITIAL_LARGE_BUFFERS > 0 */



#if WST_INITIAL_HUGE_BUFFERS > 0
	sint16 startHuge;
	WST_MEM_HUGE_POOL_DEFINITION	
#ifdef WST_MEM_USE_TAIL
	sint16 tailHuge;		
#endif /* WST_MEM_USE_TAIL */

 
	uint16 hugeCounter;
 

#endif /* WST_INITIAL_HUGE_BUFFERS > 0 */


#ifdef  WST_MEM_STATISTICS
	#if     WST_INITIAL_HUGE_BUFFERS > 0
		#define WST_MEM_STATISTICS_MAX_ELEMENTS  (((WST_HUGE_BUFFER_SIZE   + 3) / 4) + 2)
	#elif   WST_INITIAL_LARGE_BUFFERS > 0
		#define WST_MEM_STATISTICS_MAX_ELEMENTS  (((WST_LARGE_BUFFER_SIZE  + 3) / 4) + 2)
	#elif   WST_INITIAL_MEDIUM_BUFFERS > 0
		#define WST_MEM_STATISTICS_MAX_ELEMENTS  (((WST_MEDIUM_BUFFER_SIZE + 3) / 4) + 2)
	#elif   WST_INITIAL_SMALL_BUFFERS > 0
		#define WST_MEM_STATISTICS_MAX_ELEMENTS  (((WST_SMALL_BUFFER_SIZE  + 3) / 4) + 2)
	#elif   WST_INITIAL_TINY_BUFFERS > 0
		#define WST_MEM_STATISTICS_MAX_ELEMENTS  (((WST_TINY_BUFFER_SIZE   + 3) / 4) + 2)
	#else
		#define WST_MEM_STATISTICS_MAX_ELEMENTS    (2)
	#endif

	uint32  requestedSizeStatistics [WST_MEM_STATISTICS_MAX_ELEMENTS] = {0};
#endif  /* WST_MEM_STATISTICS */




WST_MEM::WST_MEM() { 
	myInstance = this;
	
	
#if WST_INITIAL_TINY_BUFFERS > 0
	for( int i = 0; i < WST_INITIAL_TINY_BUFFERS; i++ )
	{
		( (WST_MEM_Block*)tinyBuffers[i])->nextFreeBlock = i + 1;

#ifdef WST_MEM_DEBUG
		( (WST_MEM_Block*)tinyBuffers[i])->status = WST_MEM_STATUS_FREE;
#endif /* WST_MEM_DEBUG */ 
		
	}
	( (WST_MEM_Block*)tinyBuffers[WST_INITIAL_TINY_BUFFERS - 1])->nextFreeBlock = WST_MEM_LIST_TERMINATION;
	startTiny = 0;
	
	
#ifdef WST_MEM_USE_TAIL
	tailTiny = WST_INITIAL_TINY_BUFFERS -1;		
#endif /* WST_MEM_USE_TAIL */
	
 
	tinyCounter = 0;
 
	
#endif /* WST_INITIAL_TINY_BUFFERS > 0 */

	
	
#if WST_INITIAL_SMALL_BUFFERS > 0
	for( int i = 0; i < WST_INITIAL_SMALL_BUFFERS; i++ )
	{
		( (WST_MEM_Block*)smallBuffers[i])->nextFreeBlock = i + 1;
		
#ifdef WST_MEM_DEBUG
		( (WST_MEM_Block*)smallBuffers[i])->status = WST_MEM_STATUS_FREE;
#endif /* WST_MEM_DEBUG */ 
		
	}
	( (WST_MEM_Block*)smallBuffers[WST_INITIAL_SMALL_BUFFERS - 1])->nextFreeBlock = WST_MEM_LIST_TERMINATION;
	startSmall = 0;
	
	
#ifdef WST_MEM_USE_TAIL
	tailSmall = WST_INITIAL_SMALL_BUFFERS -1;		
#endif /* WST_MEM_USE_TAIL */
	
 
	smallCounter = 0;
 
	
#endif /* WST_INITIAL_SMALL_BUFFERS > 0 */


	
#if WST_INITIAL_MEDIUM_BUFFERS > 0
	for( int i = 0; i < WST_INITIAL_MEDIUM_BUFFERS; i++ )
	{
		( (WST_MEM_Block*)mediumBuffers[i])->nextFreeBlock = i + 1;
		
#ifdef WST_MEM_DEBUG
		( (WST_MEM_Block*)mediumBuffers[i])->status = WST_MEM_STATUS_FREE;
#endif /* WST_MEM_DEBUG */ 
		
	}
	( (WST_MEM_Block*)mediumBuffers[WST_INITIAL_MEDIUM_BUFFERS - 1])->nextFreeBlock = WST_MEM_LIST_TERMINATION;	
	startMedium = 0;

	
#ifdef WST_MEM_USE_TAIL
	tailMedium = WST_INITIAL_MEDIUM_BUFFERS -1;		
#endif /* WST_MEM_USE_TAIL */
	
 
	mediumCounter = 0;
 
	
#endif /* WST_INITIAL_MEDIUM_BUFFERS > 0 */

	
	
#if WST_INITIAL_LARGE_BUFFERS > 0
	for( int i = 0; i < WST_INITIAL_LARGE_BUFFERS; i++ )
	{
		( (WST_MEM_Block*)largeBuffers[i])->nextFreeBlock = i + 1;
		
#ifdef WST_MEM_DEBUG
		( (WST_MEM_Block*)largeBuffers[i])->status = WST_MEM_STATUS_FREE;
#endif /* WST_MEM_DEBUG */ 
		
	}
	( (WST_MEM_Block*)largeBuffers[WST_INITIAL_LARGE_BUFFERS - 1])->nextFreeBlock = WST_MEM_LIST_TERMINATION;	
	startLarge = 0;
	
	
#ifdef WST_MEM_USE_TAIL
	tailLarge = WST_INITIAL_LARGE_BUFFERS -1;		
#endif /* WST_MEM_USE_TAIL */
	
 
	largeCounter = 0;
 
	
#endif /* WST_INITIAL_LARGE_BUFFERS > 0 */


	
#if WST_INITIAL_HUGE_BUFFERS > 0
	for( int i = 0; i < WST_INITIAL_HUGE_BUFFERS; i++ )
	{
		( (WST_MEM_Block*)hugeBuffers[i])->nextFreeBlock = i + 1;
		
#ifdef WST_MEM_DEBUG
		( (WST_MEM_Block*)hugeBuffers[i])->status = WST_MEM_STATUS_FREE;
#endif /* WST_MEM_DEBUG */ 
		
	}
	( (WST_MEM_Block*)hugeBuffers[WST_INITIAL_HUGE_BUFFERS - 1])->nextFreeBlock = WST_MEM_LIST_TERMINATION;	
	startHuge = 0;

	
#ifdef WST_MEM_USE_TAIL
	tailHuge = WST_INITIAL_HUGE_BUFFERS -1;		
#endif /* WST_MEM_USE_TAIL */
	
 
	hugeCounter = 0;
 
	
#endif /* WST_INITIAL_HUGE_BUFFERS > 0 */
	
	
}

//#]




void * WST_MEM::getMemory(const uint32 requestedSize) {
	//#[ operation getMemory(uint32)
	static WST_MEM instance;
	void* retValue = NULL;
	WST_MEM_Block *tmp = NULL; 
	
	
	do
	{
#ifdef  WST_MEM_STATISTICS
		uint16  idx = (requestedSize + 3) / 4;
		if (idx > WST_MEM_STATISTICS_MAX_ELEMENTS - 1)
		{
			idx = WST_MEM_STATISTICS_MAX_ELEMENTS - 1;
		}
		requestedSizeStatistics[idx]++;
#endif  /* WST_MEM_STATISTICS */


#if WST_INITIAL_TINY_BUFFERS > 0
		if( requestedSize <= WST_TINY_BUFFER_SIZE  )
		{
			WST_MEM_MUTEX_ENTER
			// if it is NULL List is empty
			if( startTiny != WST_MEM_LIST_TERMINATION )
			{
				// get first block of the list
				tmp = (WST_MEM_Block*)tinyBuffers[startTiny];

				// remove the block from the list
				startTiny = tmp->nextFreeBlock;

#ifdef  WST_MEM_USE_TAIL
				if( startTiny == WST_MEM_LIST_TERMINATION )
				{
					tailTiny = WST_MEM_LIST_TERMINATION;
				}
#endif  /* WST_MEM_USE_TAIL */
				
				WST_MEM_MUTEX_EXIT

#ifdef  WST_MEM_DEBUG
				if( tmp->status == WST_MEM_STATUS_FREE )
				{
					tmp->status = WST_MEM_STATUS_USED;
				}
				else
				{
					WST_ERR::error( WST_ERR::WST_ERR_MEM_GET_CORRUPT, 0u );
				}
#endif  /* WST_MEM_DEBUG */

 
				tinyCounter++;
				if( tinyCounter > WST_CFG_Highwater::tinyBuffersMax )
				{
					WST_CFG_Highwater::tinyBuffersMax++;
				}
 

				break;
			}
			else
			{
				WST_MEM_MUTEX_EXIT

 
				WST_CFG_Highwater::bufferOverflow++;
 

#ifndef WST_MEM_REQUEST_ALL_POOLS
				break;
#endif  /* WST_MEM_REQUEST_ALL_POOLS */

			}
		}

#endif  /* WST_INITIAL_TINY_BUFFERS > 0 */



#if WST_INITIAL_SMALL_BUFFERS > 0
		if( requestedSize <= WST_SMALL_BUFFER_SIZE  )
		{
			WST_MEM_MUTEX_ENTER
			// if it is NULL List is empty
			if( startSmall != WST_MEM_LIST_TERMINATION )
			{
				// get first block of the list
				tmp = (WST_MEM_Block*)smallBuffers[startSmall];

				// remove the block from the list
				startSmall = tmp->nextFreeBlock;

#ifdef  WST_MEM_USE_TAIL
				if( startSmall == WST_MEM_LIST_TERMINATION )
				{
					tailSmall = WST_MEM_LIST_TERMINATION;
				}
#endif  /* WST_MEM_USE_TAIL */

				WST_MEM_MUTEX_EXIT

#ifdef  WST_MEM_DEBUG
				if( tmp->status == WST_MEM_STATUS_FREE )
				{
					tmp->status = WST_MEM_STATUS_USED;
				}
				else
				{
					WST_ERR::error( WST_ERR::WST_ERR_MEM_GET_CORRUPT, 0u );
				}
#endif  /* WST_MEM_DEBUG */

 
				smallCounter++;
				if( smallCounter > WST_CFG_Highwater::smallBuffersMax )
				{
					WST_CFG_Highwater::smallBuffersMax++;
				}
 

				break;
			}
			else
			{
				WST_MEM_MUTEX_EXIT

 
				WST_CFG_Highwater::bufferOverflow++;
 

#ifndef WST_MEM_REQUEST_ALL_POOLS
				break;
#endif  /* WST_MEM_REQUEST_ALL_POOLS */

			}
		}

#endif  /* WST_INITIAL_SMALL_BUFFERS > 0 */



#if WST_INITIAL_MEDIUM_BUFFERS > 0
		if( requestedSize <= WST_MEDIUM_BUFFER_SIZE  )
		{
			WST_MEM_MUTEX_ENTER
			// if it is NULL List is empty
			if( startMedium != WST_MEM_LIST_TERMINATION )
			{
				// get first block of the list
				tmp = (WST_MEM_Block*)mediumBuffers[startMedium];

				// remove the block from the list
				startMedium = tmp->nextFreeBlock;

#ifdef  WST_MEM_USE_TAIL
				if( startMedium == WST_MEM_LIST_TERMINATION )
				{
					tailMedium = WST_MEM_LIST_TERMINATION;
				}
#endif  /* WST_MEM_USE_TAIL */

				WST_MEM_MUTEX_EXIT

#ifdef  WST_MEM_DEBUG
				if( tmp->status == WST_MEM_STATUS_FREE )
				{
					tmp->status = WST_MEM_STATUS_USED;
				}
				else
				{
					WST_ERR::error( WST_ERR::WST_ERR_MEM_GET_CORRUPT, 0u );
				}
#endif  /* WST_MEM_DEBUG */

 
				mediumCounter++;
				if( mediumCounter > WST_CFG_Highwater::mediumBuffersMax )
				{
					WST_CFG_Highwater::mediumBuffersMax++;
				}
 

				break;
			}
			else
			{
				WST_MEM_MUTEX_EXIT

 
				WST_CFG_Highwater::bufferOverflow++;
 

#ifndef WST_MEM_REQUEST_ALL_POOLS
				break;
#endif  /* WST_MEM_REQUEST_ALL_POOLS */

			}
		}

#endif  /* WST_INITIAL_MEDIUM_BUFFERS > 0 */



#if WST_INITIAL_LARGE_BUFFERS > 0
		if( requestedSize <= WST_LARGE_BUFFER_SIZE  )
		{
			WST_MEM_MUTEX_ENTER
			// if it is NULL List is empty
			if( startLarge != WST_MEM_LIST_TERMINATION )
			{
				// get first block of the list
				tmp = (WST_MEM_Block*)largeBuffers[startLarge];

				// remove the block from the list
				startLarge = tmp->nextFreeBlock;

#ifdef  WST_MEM_USE_TAIL
				if( startLarge == WST_MEM_LIST_TERMINATION )
				{
					tailLarge = WST_MEM_LIST_TERMINATION;
				}
#endif  /* WST_MEM_USE_TAIL */

				WST_MEM_MUTEX_EXIT

#ifdef  WST_MEM_DEBUG
				if( tmp->status == WST_MEM_STATUS_FREE )
				{
					tmp->status = WST_MEM_STATUS_USED;
				}
				else
				{
					WST_ERR::error( WST_ERR::WST_ERR_MEM_GET_CORRUPT, 0u );
				}
#endif  /* WST_MEM_DEBUG */

 
				largeCounter++;
				if( largeCounter > WST_CFG_Highwater::largeBuffersMax )
				{
					WST_CFG_Highwater::largeBuffersMax++;
				}
 

				break;
			}
			else
			{
				WST_MEM_MUTEX_EXIT

 
				WST_CFG_Highwater::bufferOverflow++;
 

#ifndef WST_MEM_REQUEST_ALL_POOLS
				break;
#endif  /* WST_MEM_REQUEST_ALL_POOLS */

			}
		}

#endif  /* WST_INITIAL_LARGE_BUFFERS > 0 */



#if WST_INITIAL_HUGE_BUFFERS > 0
		if( requestedSize <= WST_HUGE_BUFFER_SIZE  )
		{
			WST_MEM_MUTEX_ENTER
			// if it is NULL List is empty
			if( startHuge != WST_MEM_LIST_TERMINATION )
			{
				// get first block of the list
				tmp = (WST_MEM_Block*)hugeBuffers[startHuge];

				// remove the block from the list
				startHuge = tmp->nextFreeBlock;

#ifdef  WST_MEM_USE_TAIL
				if( startHuge == WST_MEM_LIST_TERMINATION )
				{
					tailHuge = WST_MEM_LIST_TERMINATION;
				}
#endif  /* WST_MEM_USE_TAIL */

				WST_MEM_MUTEX_EXIT

#ifdef  WST_MEM_DEBUG
				if( tmp->status == WST_MEM_STATUS_FREE )
				{
					tmp->status = WST_MEM_STATUS_USED;
				}
				else
				{
					WST_ERR::error( WST_ERR::WST_ERR_MEM_GET_CORRUPT, 0u );
				}
#endif  /* WST_MEM_DEBUG */

 
				hugeCounter++;
				if( hugeCounter > WST_CFG_Highwater::hugeBuffersMax )
				{
					WST_CFG_Highwater::hugeBuffersMax++;
				}
 

				break;
			}
			else
			{
				WST_MEM_MUTEX_EXIT

 
				WST_CFG_Highwater::bufferOverflow++;
 

#ifndef WST_MEM_REQUEST_ALL_POOLS
				break;
#endif  /* WST_MEM_REQUEST_ALL_POOLS */

			}
		}

#endif  /* WST_INITIAL_HUGE_BUFFERS > 0 */

	}
	while ( WSTFALSE );

	if( tmp == NULL)
	{
#ifdef  NO_MALLOC
		/* If NO_MALLOC is defined, the error handler is being called. */
		WST_ERR::error( WST_ERR::WST_ERR_ALLOC_FAILED, 0u );
#else   /* NO_MALLOC */
		/* If NO_MALLOC is undefined, the OS malloc is being called. */

		retValue = new char[requestedSize];

#endif	/* NO_MALLOC */
	}
	else
	{
		retValue = tmp + 1;
	}
	return retValue;
	//#]
}

void * WST_MEM::reallocMemory(const uint32 currentSize, const uint32 newSize, void * contents) {
	//#[ operation reallocMemory(uint32,uint32,void *)
	void * retValue = NULL;
	/* If the given pointer is NULL, just allocate and return memory of the new size */
	if( contents == NULL )
	{
		retValue = getMemory( newSize );
	}
	/* If the new size is zero, return NULL and give back 'old' memory */
	else
	{
		if( newSize == 0u )
		{
			returnMemory( contents );
		}
		else
		{
			void* temp;
			
			/* Allocate memory of the new size from the best fitting block size */
			temp = getMemory( newSize );
			
			if( temp != NULL )
			{
				/* If the memory size should increase, perform a memory copy operation of the CURRENT size */
				if( newSize > currentSize )
				{
					memcpy( temp, contents, currentSize );
				}
				/* If the memory size should decrease, perform a memory copy operation of the NEW size */
				else
				{
					memcpy( temp, contents, newSize );
				}
				
				/* return 'old' memory block */
				returnMemory( contents );
			}
			retValue = temp;
		}
	}

	return retValue;
	//#]
}

void WST_MEM::returnMemory(void * returnedBlock) {
	//#[ operation returnMemory(void *)
#if WST_INITIAL_TINY_BUFFERS > 0
	if( returnedBlock >= tinyBuffers && returnedBlock < &tinyBuffers[ WST_INITIAL_TINY_BUFFERS ][ 0 ] )
	{
		WST_MEM_Block *tmp = (WST_MEM_Block*)returnedBlock - 1;
		uint16 nr = (uint16)(( (uint32)returnedBlock - (uint32)tinyBuffers ) / sizeof( tinyBuffers[0] ));

#ifdef WST_MEM_DEBUG
		if( tmp->status == WST_MEM_STATUS_USED )
		{
			tmp->status = WST_MEM_STATUS_FREE;
		}
		else
		{
			WST_ERR::error( WST_ERR::WST_ERR_MEM_RETURN_CORRUPT, 0u );
		}
#endif /* WST_MEM_DEBUG */

#ifdef WST_MEM_USE_TAIL
		tmp->nextFreeBlock = WST_MEM_LIST_TERMINATION;

		WST_MEM_MUTEX_ENTER
		/* is list empty set start = tail */
		if( tailTiny == WST_MEM_LIST_TERMINATION )
		{
			startTiny = nr;
		}
		else
		{
			/* add returnd block to end of list */
			( (WST_MEM_Block*)tinyBuffers[ tailTiny ])->nextFreeBlock = nr;
		}
		/* set tail */
		tailTiny = nr;

#else /* WST_MEM_USE_TAIL */
		WST_MEM_MUTEX_ENTER
		/* get first block of the list */
		tmp->nextFreeBlock = startTiny;

		/* add Block to Head of List */
		startTiny = nr;	

#endif /* WST_MEM_USE_TAIL */

 
		tinyCounter--;
 

		WST_MEM_MUTEX_EXIT
	}
	else
#endif /* WST_INITIAL_TINY_BUFFERS > 0 */



#if WST_INITIAL_SMALL_BUFFERS > 0
	if( returnedBlock >= smallBuffers && returnedBlock < &smallBuffers[ WST_INITIAL_SMALL_BUFFERS ][ 0 ] ){
		WST_MEM_Block *tmp = (WST_MEM_Block*)returnedBlock - 1;
		uint16 nr = (uint16)(( (uint32)returnedBlock - (uint32)smallBuffers ) / sizeof( smallBuffers[0] ));
		
#ifdef WST_MEM_DEBUG
		if( tmp->status == WST_MEM_STATUS_USED )
		{
			tmp->status = WST_MEM_STATUS_FREE;
		}
		else
		{
			WST_ERR::error( WST_ERR::WST_ERR_MEM_RETURN_CORRUPT, 0u );
		}
#endif /* WST_MEM_DEBUG */

#ifdef WST_MEM_USE_TAIL		
		tmp->nextFreeBlock = WST_MEM_LIST_TERMINATION;
		
		WST_MEM_MUTEX_ENTER
		/* is list empty set start = tail */
		if( tailSmall == WST_MEM_LIST_TERMINATION )
		{
			startSmall = nr;
		}
		else
		{
			/* add returnd block to end of list */
			( (WST_MEM_Block*)smallBuffers[ tailSmall ])->nextFreeBlock = nr;	
		}
		/* set tail */
		tailSmall = nr;

#else /* WST_MEM_USE_TAIL */
		WST_MEM_MUTEX_ENTER		
		/* get first block of the list */
		tmp->nextFreeBlock = startSmall;
			
		/* add Block to Head of List */
		startSmall = nr;	
		
#endif /* WST_MEM_USE_TAIL */
		
 
		smallCounter--;
 
		
		WST_MEM_MUTEX_EXIT	
	}
	else
#endif /* WST_INITIAL_SMALL_BUFFERS > 0 */
	
	
	
#if WST_INITIAL_MEDIUM_BUFFERS > 0
	if( returnedBlock >= mediumBuffers && returnedBlock < &mediumBuffers[ WST_INITIAL_MEDIUM_BUFFERS  ][ 0 ] ){
		WST_MEM_Block *tmp = (WST_MEM_Block*)returnedBlock - 1;
		uint16 nr = (uint16)(( (uint32)returnedBlock - (uint32)mediumBuffers ) / sizeof( mediumBuffers[0] ));
		
#ifdef WST_MEM_DEBUG
		if( tmp->status == WST_MEM_STATUS_USED )
		{
			tmp->status = WST_MEM_STATUS_FREE;
		}
		else
		{
			WST_ERR::error( WST_ERR::WST_ERR_MEM_RETURN_CORRUPT, 0u );
		}
#endif /* WST_MEM_DEBUG */
		
#ifdef WST_MEM_USE_TAIL		
		tmp->nextFreeBlock = WST_MEM_LIST_TERMINATION;
		
		WST_MEM_MUTEX_ENTER
		/* is list empty set start = tail */
		if( tailMedium == WST_MEM_LIST_TERMINATION )
		{
			startMedium = nr;
		}
		else
		{
			/* add returnd block to end of list */
			( (WST_MEM_Block*)mediumBuffers[ tailMedium ])->nextFreeBlock = nr;	
		}
		/* set tail */
		tailMedium = nr;

#else /* WST_MEM_USE_TAIL */
		WST_MEM_MUTEX_ENTER		
		/* get first block of the list */
		tmp->nextFreeBlock = startMedium;
			
		/* add Block to Head of List */
		startMedium = nr;	
		
#endif /* WST_MEM_USE_TAIL */
		
 
		mediumCounter--;
 
		
		WST_MEM_MUTEX_EXIT	
	}
	else
#endif /* WST_INITIAL_MEDIUM_BUFFERS > 0 */
	
	

#if WST_INITIAL_LARGE_BUFFERS > 0
	if( returnedBlock >= largeBuffers && returnedBlock < &largeBuffers[ WST_INITIAL_LARGE_BUFFERS ][ 0 ] ){
		WST_MEM_Block *tmp = (WST_MEM_Block*)returnedBlock - 1;
		uint16 nr = (uint16)(( (uint32)returnedBlock - (uint32)largeBuffers ) / sizeof( largeBuffers[0] ));
		
#ifdef WST_MEM_DEBUG
		if( tmp->status == WST_MEM_STATUS_USED )
		{
			tmp->status = WST_MEM_STATUS_FREE;
		}
		else
		{
			WST_ERR::error( WST_ERR::WST_ERR_MEM_RETURN_CORRUPT, 0u );
		}
#endif /* WST_MEM_DEBUG */
		
#ifdef WST_MEM_USE_TAIL		
		tmp->nextFreeBlock = WST_MEM_LIST_TERMINATION;
		
		WST_MEM_MUTEX_ENTER
		/* is list empty set start = tail */
		if( tailLarge == WST_MEM_LIST_TERMINATION )
		{
			startLarge = nr;
		}
		else
		{
			/* add returnd block to end of list */
			( (WST_MEM_Block*)largeBuffers[ tailLarge ])->nextFreeBlock = nr;	
		}
		/* set tail */
		tailLarge = nr;

#else /* WST_MEM_USE_TAIL */
		WST_MEM_MUTEX_ENTER		
		/* get first block of the list */
		tmp->nextFreeBlock = startLarge;
			
		/* add Block to Head of List */
		startLarge = nr;	
		
#endif /* WST_MEM_USE_TAIL */
		
 
		largeCounter--;
 
		
		WST_MEM_MUTEX_EXIT	
	}
	else
#endif /* WST_INITIAL_LARGE_BUFFERS > 0 */
	
	
	
#if WST_INITIAL_HUGE_BUFFERS > 0
	if( returnedBlock >= hugeBuffers && returnedBlock < &hugeBuffers[ WST_INITIAL_HUGE_BUFFERS ][ 0 ] ){
		WST_MEM_Block *tmp = (WST_MEM_Block*)returnedBlock - 1;
		uint16 nr = (uint16)(( (uint32)returnedBlock - (uint32)hugeBuffers ) / sizeof( hugeBuffers[0] ));
		
#ifdef WST_MEM_DEBUG
		if( tmp->status == WST_MEM_STATUS_USED )
		{
			tmp->status = WST_MEM_STATUS_FREE;
		}
		else
		{
			WST_ERR::error( WST_ERR::WST_ERR_MEM_RETURN_CORRUPT, 0u );
		}
#endif /* WST_MEM_DEBUG */
		
#ifdef WST_MEM_USE_TAIL		
		tmp->nextFreeBlock = WST_MEM_LIST_TERMINATION;
		
		WST_MEM_MUTEX_ENTER
		/* is list empty set start = tail */
		if( tailHuge == WST_MEM_LIST_TERMINATION )
		{
			startHuge = nr;
		}
		else
		{
			/* add returnd block to end of list */
			( (WST_MEM_Block*)hugeBuffers[ tailHuge ])->nextFreeBlock = nr;	
		}
		/* set tail */
		tailHuge = nr;

#else /* WST_MEM_USE_TAIL */
		WST_MEM_MUTEX_ENTER		
		/* get first block of the list */
		tmp->nextFreeBlock = startHuge;
			
		/* add Block to Head of List */
		startHuge = nr;	
		
#endif /* WST_MEM_USE_TAIL */
		
 
		hugeCounter--;
 
		
		WST_MEM_MUTEX_EXIT	
	}
	else
#endif /* WST_INITIAL_HUGE_BUFFERS > 0 */   
	{
		delete returnedBlock;
	}
	
	//#]
}


/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM.cpp
*********************************************************************/
