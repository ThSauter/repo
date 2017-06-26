#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MEM
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM.h
*********************************************************************/

#ifndef WST_MEM_H
#define WST_MEM_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


#ifdef WST_MEM_USE_MUTEX
#define WST_MEM_MUTEX_ENTER memMutex->WST_MTX_enterCriticalRegion();
#define WST_MEM_MUTEX_EXIT memMutex->WST_MTX_exitCriticalRegion();
#else
#define WST_MEM_MUTEX_ENTER WSTTarget_enterCriticalRegion();
#define WST_MEM_MUTEX_EXIT WSTTarget_exitCriticalRegion();
#endif

#define WST_MEM_LIST_TERMINATION -1


//## class WST_MEM
class WST_MEM {
//#[ ignore
    public:
    	
    	WST_MEM();
//#]

    ////    Operations    ////
    
public :

    //## operation getMemory(uint32)
    static void * getMemory(const uint32 requestedSize);
    
    //## operation reallocMemory(uint32,uint32,void *)
    static void * reallocMemory(const uint32 currentSize, const uint32 newSize, void * contents);
    
    //## operation returnMemory(void *)
    static void returnMemory(void * returnedBlock);

#ifdef WST_MEM_USE_MUTEX
	//## operation initMutex()
    static void initMutex();
#endif
   
    

};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
