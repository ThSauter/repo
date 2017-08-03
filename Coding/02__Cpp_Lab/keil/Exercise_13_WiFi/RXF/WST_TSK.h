#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_TSK
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TSK.h
*********************************************************************/

#ifndef WST_TSK_H
#define WST_TSK_H

//#[ ignore
#ifdef _MSC_VER
// disable Microsoft compiler warning (debug information truncated)
#pragma warning(disable: 4786)
#endif
//#]


//## package RXF::RXF_BehaviorPkg

//## class WST_TSK
// Owner: MS
class WST_TSK {
    ////    Constructors and destructors    ////
    
public :
    
    //## operation WST_TSK(char*,uint8,uint16,uint8)
    WST_TSK(char* taskName = NULL, const uint8 taskPriority = WST_TSK_DEFAULT_PRIORITY, const uint16 taskStackSize = WST_TSK_DEFAULT_STACK_SIZE , const uint16 taskMessageQueueSize = WST_TSK_DEFAULT_MESSAGE_QUEUE_SIZE, WSTBoolean dynamicMessageQueue = WSTFALSE );

	//## operation WST_TSK(char*,void*,uint8,uint16,uint8)
	WST_TSK(uint8 *osw_stk, void* osw_msq, const uint8 taskPriority,const uint16 taskStackSize, const uint16 taskMessageQueueSize, WSTBoolean dynamicMessageQueue);
    
    //## auto_generated
    virtual ~WST_TSK( void );
    
    ////    Operations    ////
    
    //## operation execute()
    void execute( void );
    
    //## operation executeOnce()
    void executeOnce( void );
    
    //## operation endDispatching()
    void endDispatching();

    //## operation task_start(void *)
    static void task_start(void * myTask);
    
    ////    Additional operations    ////
    
    //## operation startDispatching()
    void startDispatching( void );
    
    //## auto_generated
    WST_INLINE_OP uint8 getPriority( void ) { return priority; };
    
    //## auto_generated
    WST_INLINE_OP void setPriority(uint8 p_priority) { priority = p_priority; }
    
    //## auto_generated
    WST_INLINE_OP WST_RTOS_TSK_t *getRtosTask( void ) { return &rtosTask; }
    
    //## auto_generated
    WST_INLINE_OP void setRtosTask(WST_RTOS_TSK_t p_rtosTask) { rtosTask = p_rtosTask; }
    
    //## auto_generated
    WST_INLINE_OP void * getStackMemory( void ) { return stackMemory; }
    
    //## auto_generated
    WST_INLINE_OP void setStackMemory(void * p_stackMemory) { stackMemory = p_stackMemory; }
    
    //## auto_generated
    void suspend();

    //## auto_generated
    void resume();
    
    //## auto_generated
    WST_INLINE_OP uint16 getStackSize( void ) { return stackSize; }
    
    //## auto_generated
    WST_INLINE_OP void setStackSize(uint16 p_stackSize) { stackSize = p_stackSize; }
    
    //## auto_generated
    WST_INLINE_OP const char * getTaskName( void ) { return taskName; }
    
    //## auto_generated
    WST_INLINE_OP void setTaskName(const char * p_taskName) { taskName = p_taskName; }
    
    //## auto_generated
    WST_INLINE_OP WST_MSQ* getMessageQueue( void ) { return &messageQueue; }
	
	//## auto_generated
    void startTaskAfterOSStart();
	
	//## auto_generated
    WST_INLINE_OP static WSTBoolean getOS_Started( void ) { return OS_Started; }
    
    //## auto_generated
    WST_INLINE_OP static void setOS_Started(WSTBoolean p_OS_Started) { OS_Started = p_OS_Started; }
	
	static WST_TSK *initList;
	
	WST_INLINE_OP WST_TSK *getNext() { return next; }
	

private :

    //## auto_generated
    void cleanUpRelations( void );
    
    ////    Attributes    ////
    
    uint8 priority;		//## attribute priority
    
    WST_RTOS_TSK_t rtosTask;		//## attribute rtosTask
    
    void * stackMemory;		//## attribute stackMemory
    
    uint16 stackSize;		//## attribute stackSize
    
    const char * taskName;		//## attribute taskName
    
    ////    Relations and components    ////
    
    WST_MSQ messageQueue;		//## its messageQueue
	
	WST_TSK* next;		//## attribute next
	
	static WSTBoolean OS_Started; //## attribute OS_Started
};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TSK.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
