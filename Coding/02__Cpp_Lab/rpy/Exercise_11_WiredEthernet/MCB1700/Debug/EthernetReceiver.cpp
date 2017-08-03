/********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetReceiver
//!	Generated Date	: Tue, 1, Aug 2017  
	File Path	: MCB1700/Debug/EthernetReceiver.cpp
*********************************************************************/

//## auto_generated
#include "EthernetReceiver.h"
//## link itsDisplay
#include "Display.h"
//## link itsLed
#include "Led.h"
//## link itsLedBar
#include "LedBar.h"
//## package DefaultPkg

//## class EthernetReceiver
EthernetReceiver::EthernetReceiver(IOxfActive* theActiveContext) {
    setActiveContext(this, true);
    itsDisplay = NULL;
    itsLed = NULL;
    itsLedBar = NULL;
    initStatechart();
    //#[ operation EthernetReceiver()
    // Setup udp properties
    unsigned char buf[8];
    
    // Create socket
    sock = socket (AF_INET, SOCK_DGRAM, 0);
    
    // Open destination port
    addr.sin_port      = htons(dstPort);
    addr.sin_family    = PF_INET;  
    
    // Set Ip adress  
    netIP_aton (remoteIpAddr, NET_ADDR_IP4, buf);
    
    addr.sin_addr.s_b1 = buf[0];
    addr.sin_addr.s_b2 = buf[1];
    addr.sin_addr.s_b3 = buf[2];
    addr.sin_addr.s_b4 = buf[3];
    
    // Bind to socket 
    bind (sock, (SOCKADDR *)&addr, sizeof(addr));
    //#]
}

EthernetReceiver::~EthernetReceiver() {
    cleanUpRelations();
    cancelTimeouts();
}

void EthernetReceiver::receiveData() {
    //#[ operation receiveData()
    extern int recv (int sock, char *buf, int len, int flags);
    int res;
    res = recv (sock, dbuf, sizeof (dbuf), 0);
        
    if (res <= 0)
    { 
    	// only for debugging purposes
    	;
    }    
      
    if (dbuf[0] == 0x01) { 
    
    	// Valid identifier, received Data
    	FIRE(this->itsLed, evBlink()); 
    	FIRE(this->itsLedBar, evReceivedData((char)dbuf[1]));    
    	FIRE(this->itsDisplay, evReceivedData((char)dbuf[1]));
    }
    //#]
}

Display* EthernetReceiver::getItsDisplay() const {
    return itsDisplay;
}

void EthernetReceiver::setItsDisplay(Display* p_Display) {
    if(p_Display != NULL)
        {
            p_Display->_setItsEthernetReceiver(this);
        }
    _setItsDisplay(p_Display);
}

Led* EthernetReceiver::getItsLed() const {
    return itsLed;
}

void EthernetReceiver::setItsLed(Led* p_Led) {
    itsLed = p_Led;
}

LedBar* EthernetReceiver::getItsLedBar() const {
    return itsLedBar;
}

void EthernetReceiver::setItsLedBar(LedBar* p_LedBar) {
    itsLedBar = p_LedBar;
}

bool EthernetReceiver::startBehavior() {
    bool done = false;
    done = OMReactive::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void EthernetReceiver::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void EthernetReceiver::cleanUpRelations() {
    if(itsDisplay != NULL)
        {
            EthernetReceiver* p_EthernetReceiver = itsDisplay->getItsEthernetReceiver();
            if(p_EthernetReceiver != NULL)
                {
                    itsDisplay->__setItsEthernetReceiver(NULL);
                }
            itsDisplay = NULL;
        }
    if(itsLed != NULL)
        {
            itsLed = NULL;
        }
    if(itsLedBar != NULL)
        {
            itsLedBar = NULL;
        }
}

void EthernetReceiver::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool EthernetReceiver::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

void EthernetReceiver::__setItsDisplay(Display* p_Display) {
    itsDisplay = p_Display;
}

void EthernetReceiver::_setItsDisplay(Display* p_Display) {
    if(itsDisplay != NULL)
        {
            itsDisplay->__setItsEthernetReceiver(NULL);
        }
    __setItsDisplay(p_Display);
}

void EthernetReceiver::_clearItsDisplay() {
    itsDisplay = NULL;
}

void EthernetReceiver::rootState_entDef() {
    {
        rootState_subState = Receive;
        rootState_active = Receive;
        rootState_timeout = scheduleTimeout(100, NULL);
    }
}

IOxfReactive::TakeEventStatus EthernetReceiver::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Receive
    // Description: Calls the middleware layer function receive data. Blocks for 20sec until a data received.
    // To avoid this initial block, the receiveData is processed on exit of the state.
    if(rootState_active == Receive)
        {
            if(IS_EVENT_TYPE_OF(OMTimeoutEventId))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            //#[ state Receive.(Exit) 
                            receiveData();
                            //#]
                            rootState_subState = Receive;
                            rootState_active = Receive;
                            rootState_timeout = scheduleTimeout(100, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
    return res;
}

/*********************************************************************
	File Path	: MCB1700/Debug/EthernetReceiver.cpp
*********************************************************************/
