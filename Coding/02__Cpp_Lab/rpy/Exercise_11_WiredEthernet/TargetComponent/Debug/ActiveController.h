/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: ActiveController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\ActiveController.h
*********************************************************************/

#ifndef ActiveController_H
#define ActiveController_H

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

//## class ActiveController
class ActiveController : public WST_TSK, public WST_FSM {
    ////    Constructors and destructors    ////
    
public :

    //## operation ActiveController()
    ActiveController(WST_TSK* myTask = 0);
    
    //## operation ~ActiveController()
    virtual ~ActiveController();
    
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

public :

    static uint16 ClassWSTMonitor_getTypeSize0();
    
    static uint16 ClassWSTMonitor_getTypeSize1();
    
    static uint16 ClassWSTMonitor_getTypeSize2();
    
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
    
    // Receive:
    //## statechart_method
    inline bool Receive_IN() const;
    
    ////    Framework    ////

protected :

//#[ ignore
    enum ActiveController_Enum {
        OMNonState = 0,
        Receive = 1
    };
    
    int rootState_subState;
    
    int rootState_active;
    
    IOxfTimeout* rootState_timeout;
//#]
};

uint16 WSTMonitor_getTypeSize0();

uint16 WSTMonitor_getTypeSize1();

uint16 WSTMonitor_getTypeSize2();

inline bool ActiveController::rootState_IN() const {
    return true;
}

inline bool ActiveController::Receive_IN() const {
    return rootState_subState == Receive;
}

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\ActiveController.h
*********************************************************************/
