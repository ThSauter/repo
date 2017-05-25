/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetReceiver
//!	Generated Date	: Tue, 9, May 2017  
	File Path	: MCB1700\Debug\EthernetReceiver.h
*********************************************************************/

#ifndef EthernetReceiver_H
#define EthernetReceiver_H

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
//## class EthernetReceiver
#include "EthernetController.h"
//## link itsLed
class Led;

//## link itsLedBar
class LedBar;

//## package ExamplePkg

//## class EthernetReceiver
class EthernetReceiver : public WST_TSK, public WST_FSM, public EthernetController {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetReceiver()
    EthernetReceiver(WST_TSK* myTask = 0);
    
    //## operation ~EthernetReceiver()
    virtual ~EthernetReceiver();
    
    ////    Operations    ////
    
    //## operation receiveData()
    void receiveData();
    
    ////    Additional operations    ////
    
    //## auto_generated
    Led* getItsLed() const;
    
    //## auto_generated
    void setItsLed(Led* p_Led);
    
    //## auto_generated
    LedBar* getItsLedBar() const;
    
    //## auto_generated
    void setItsLedBar(LedBar* p_LedBar);
    
    //## auto_generated
    virtual bool startBehavior();

protected :

    //## auto_generated
    void initStatechart();
    
    //## auto_generated
    void cleanUpRelations();
    
    //## auto_generated
    void cancelTimeouts();
    
    //## auto_generated
    virtual bool cancelTimeout(const IOxfTimeout* arg);

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

public :

    static uint16 ClassWSTMonitor_getTypeSize1();
    
    static uint16 ClassWSTMonitor_getTypeSize2();
    
    ////    Attributes    ////

protected :

    SOCKADDR_IN addr;		//## attribute addr
    
    char dbuf[4];		//## attribute dbuf
    
    static int dstPort;		//## attribute dstPort
    
    int sock;		//## attribute sock
    
    ////    Relations and components    ////
    
    Led* itsLed;		//## link itsLed
    
    LedBar* itsLedBar;		//## link itsLedBar
    
    ////    Framework operations    ////

public :

    // rootState:
    //## statechart_method
    inline bool rootState_IN() const;
    
    //## statechart_method
    virtual void rootState_entDef();
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent();
    
    // Receive:
    //## statechart_method
    inline bool Receive_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum EthernetReceiver_Enum {
        OMNonState = 0,
        Receive = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

uint16 WSTMonitor_getTypeSize1();

uint16 WSTMonitor_getTypeSize2();

inline bool EthernetReceiver::rootState_IN() const {
    return true;
}

inline bool EthernetReceiver::Receive_IN() const {
    return rootState_subState == Receive;
}

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\EthernetReceiver.h
*********************************************************************/
