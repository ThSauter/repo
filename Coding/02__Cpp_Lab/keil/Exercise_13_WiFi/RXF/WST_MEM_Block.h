#ifdef WST_CORRECT_HEADER_ORDER 
/*********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MEM_Block
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM_Block.h
*********************************************************************/

#ifndef WST_MEM_Block_H
#define WST_MEM_Block_H


#define WST_MEM_STATUS_FREE 0xAFFA
#define WST_MEM_STATUS_USED 0xA00A

//## class WST_MEM_Block
class WST_MEM_Block {
    ////    Constructors and destructors    ////
    
public :

    //## operation WST_MEM_Block()
    WST_MEM_Block( void );
    
    //## auto_generated
    ~WST_MEM_Block( void );

	uint16 status;
	sint16 nextFreeBlock;

};

#endif
/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MEM_Block.h
*********************************************************************/
#endif /* WST_CORRECT_HEADER_ORDER */ 
