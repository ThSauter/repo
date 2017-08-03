/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: UartController
//!	Generated Date	: Thu, 3, Aug 2017  
	File Path	: MCB1700\Debug\UartController.h
*********************************************************************/

#ifndef UartController_H
#define UartController_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## package DefaultPkg

//## class UartController
class UartController {
public :

//#[ ignore
    #define  util_BitClear(x,bit)          ((x) &= ~util_GetBitMask(bit))
    #define  util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)
    #define  util_GetBitMask(bit)          ((uint32_t)1<<(bit))
//#]

    ////    Constructors and destructors    ////
    
    //## operation UartController()
    UartController();
    
    //## auto_generated
    virtual ~UartController();
    
    ////    Operations    ////
    
    //## operation rxChar()
    char rxChar();
    
    //## operation txChar(char)
    void txChar(char ch);
    
    ////    Additional operations    ////
    
    //## auto_generated
    int getDbuf() const;
    
    //## auto_generated
    void setDbuf(int p_dbuf);
    
    //## auto_generated
    static bool getIsInitialized();
    
    //## auto_generated
    static void setIsInitialized(bool p_isInitialized);
    
    ////    Attributes    ////

protected :

    int dbuf;		//## attribute dbuf
    
    static bool isInitialized;		//## attribute isInitialized
};

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\UartController.h
*********************************************************************/
