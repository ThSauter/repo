/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetReceiver
//!	Generated Date	: Tue, 9, May 2017  
	File Path	: MCB1700\Debug\EthernetReceiver.cpp
*********************************************************************/

//## auto_generated
#include "EthernetReceiver.h"
//## link itsLed
#include "Led.h"
//## link itsLedBar
#include "LedBar.h"
//## package ExamplePkg

//## class EthernetReceiver
int EthernetReceiver::dstPort = 1001;

EthernetReceiver::EthernetReceiver(WST_TSK* myTask) {
    setTask( this, true );
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
    //netIF_SetOption (NET_IF_CLASS_ETH | 0, netIF_OptionIP4_Address, buf, NET_ADDR_IP4_LEN);
    
    addr.sin_addr.s_b1 = buf[0];
    addr.sin_addr.s_b2 = buf[1];
    addr.sin_addr.s_b3 = buf[2];
    addr.sin_addr.s_b4 = buf[3];
    
    // Bind to socket 
    bind (sock, (SOCKADDR *)&addr, sizeof(addr));
    
    // Connect socket
    connect (sock, (SOCKADDR *)&addr, sizeof (addr));
    this->setOwner( this );
    WSTMonitor_sendInit( this, 102, (void*)&addr);
    
    //#]
}

EthernetReceiver::~EthernetReceiver() {
    //#[ operation ~EthernetReceiver()
    closesocket (sock);
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
    //#]
    cleanUpRelations();
    cancelTimeouts();
}

void EthernetReceiver::receiveData() {
    //#[ operation receiveData()
    receive_data(sock, dbuf);
      
    if (dbuf[0] == 0x01) {
    	FIRE(this->itsLed, evBlink()); 
    	FIRE(this->itsLedBar, evReceivedData((char)dbuf[1]));
    }
    //#]
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
    done = WST_FSM::startBehavior();
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

SOCKADDR_IN EthernetReceiver::getAddr() const {
    return addr;
}

void EthernetReceiver::setAddr(SOCKADDR_IN p_addr) {
    addr = p_addr;
}

char EthernetReceiver::getDbuf(int i1) const {
    return dbuf[i1];
}

void EthernetReceiver::setDbuf(int i1, char p_dbuf) {
    dbuf[i1] = p_dbuf;
}

int EthernetReceiver::getDstPort() {
    return dstPort;
}

void EthernetReceiver::setDstPort(int p_dstPort) {
    dstPort = p_dstPort;
}

int EthernetReceiver::getSock() const {
    return sock;
}

void EthernetReceiver::setSock(int p_sock) {
    sock = p_sock;
}

uint16 EthernetReceiver::ClassWSTMonitor_getTypeSize1() {
    return sizeof( SOCKADDR_IN );
}

uint16 EthernetReceiver::ClassWSTMonitor_getTypeSize2() {
    return sizeof( int );
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
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
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
    this->activeState[ 0 ] = rootState_active;
    return res;
}

uint16 WSTMonitor_getTypeSize1() {
    return EthernetReceiver::ClassWSTMonitor_getTypeSize1( );
}

uint16 WSTMonitor_getTypeSize2() {
    return EthernetReceiver::ClassWSTMonitor_getTypeSize2( );
}

/*********************************************************************
	File Path	: MCB1700\Debug\EthernetReceiver.cpp
*********************************************************************/
