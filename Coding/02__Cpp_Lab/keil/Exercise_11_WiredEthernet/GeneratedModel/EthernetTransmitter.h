/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetTransmitter
//!	Generated Date	: Tue, 9, May 2017  
	File Path	: MCB1700\Debug\EthernetTransmitter.h
*********************************************************************/

#ifndef EthernetTransmitter_H
#define EthernetTransmitter_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "ExamplePkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## class EthernetTransmitter
#include "EthernetController.h"
//## link itsLed
class Led;

//## package ExamplePkg

//## class EthernetTransmitter
class EthernetTransmitter : public WST_TSK, public WST_FSM, public EthernetController {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetTransmitter()
    EthernetTransmitter(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~EthernetTransmitter();
    
    ////    Operations    ////
    
    //## operation transmitData()
    void transmitData();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Led* getItsLed() const;
    
    //## auto_generated
    void setItsLed(Led* p_Led);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();

private :

    //## auto_generated
    SOCKADDR_IN getAddr() const;
    
    //## auto_generated
    void setAddr(SOCKADDR_IN p_addr);
    
    //## auto_generated
    char getDbuf(int i1) const;
    
    //## auto_generated
    void setDbuf(int i1, char p_dbuf);
    
    //## auto_generated
    static int getDstPort();
    
    //## auto_generated
    static void setDstPort(int p_dstPort);
    
    //## auto_generated
    int getSock() const;
    
    //## auto_generated
    void setSock(int p_sock);
    
    ////    Attributes    ////

protected :

    SOCKADDR_IN addr;		//## attribute addr
    
    char dbuf[4];		//## attribute dbuf
    
    static int dstPort;		//## attribute dstPort
    
    int sock;		//## attribute sock
    
    ////    Relations and components    ////
    
    Led* itsLed;		//## link itsLed
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // state_0:
    //## statechart_method
    inline bool state_0_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum EthernetTransmitter_Enum {
        OMNonState = 0,
        state_0 = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
//#]
};

inline bool EthernetTransmitter::rootState_IN() const {
    return true;
}

inline bool EthernetTransmitter::state_0_IN() const {
    return rootState_subState == state_0;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\EthernetTransmitter.h
*********************************************************************/
