/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: EthernetController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\EthernetController.h
*********************************************************************/

#ifndef EthernetController_H
#define EthernetController_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
#include "ExamplePkg.h"
//## auto_generated
#include "WSTModelHeadersTSK.h"
//## link itsLED
class LED;

//## package ExamplePkg

//## class EthernetController
class EthernetController : public WST_TSK, public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetController()
    EthernetController(WST_TSK* myTask = 0);
    
    //## auto_generated
    virtual ~EthernetController();
    
    ////    Additional operations    ////
    
    //## auto_generated
    LED* getItsLED() const;
    
    //## auto_generated
    void setItsLED(LED* p_LED);
    
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
    static unsigned char getRemoteIpAddr(int i1);
    
    //## auto_generated
    static void setRemoteIpAddr(int i1, unsigned char p_remoteIpAddr);
    
    //## auto_generated
    int getSock() const;
    
    //## auto_generated
    void setSock(int p_sock);
    
    ////    Attributes    ////

protected :

    SOCKADDR_IN addr;		//## attribute addr
    
    char dbuf[4];		//## attribute dbuf
    
    static int dstPort;		//## attribute dstPort
    
    static unsigned char remoteIpAddr[4];		//## attribute remoteIpAddr
    
    int sock;		//## attribute sock
    
    ////    Relations and components    ////
    
    LED* itsLED;		//## link itsLED
    
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
    enum EthernetController_Enum {
        OMNonState = 0,
        state_0 = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

inline bool EthernetController::rootState_IN() const {
    return true;
}

inline bool EthernetController::state_0_IN() const {
    return rootState_subState == state_0;
}

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\EthernetController.h
*********************************************************************/
