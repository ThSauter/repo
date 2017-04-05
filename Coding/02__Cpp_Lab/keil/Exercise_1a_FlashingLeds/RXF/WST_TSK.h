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

#define WST_CHECK_TIMEOUTS_MAX 25

//## class WST_TSK
// Owner: MS
class WST_TSK {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_TSK()
    WST_TSK( void );
    
    //## auto_generated
    ~WST_TSK( void );
    
    ////    Operations    ////
    
    //## operation execute()
    void execute( void );
    
    //## operation executeOnce()
    void executeOnce( void );
    
    
    ////    Additional operations    ////
    
    //## auto_generated
    WST_INLINE_OP WST_MSQ* getMessageQueue( void ) { return &messageQueue; }
    

protected :

    //## auto_generated
    void cleanUpRelations( void );
   
    
    ////    Relations and components    ////
    
    WST_MSQ messageQueue;		//## link messageQueue
};

extern WST_TSK theMainTask;


#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_TSK.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
