/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetTransmitter
//!	Generated Date	: Tue, 9, May 2017  
	File Path	: MCB1700\Debug\EthernetTransmitter.cpp
*********************************************************************/

//## auto_generated
#include "EthernetTransmitter.h"
//## link itsLed
#include "Led.h"
//## package ExamplePkg

//## class EthernetTransmitter
int EthernetTransmitter::dstPort = 1001;

EthernetTransmitter::EthernetTransmitter(WST_TSK* myTask) {
    setTask( this, true );
    itsLed = NULL;
    initStatechart();
    //#[ operation EthernetTransmitter()
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
    WSTMonitor_sendInit( this, 106, (void*)&addr);
    
    //#]
}

EthernetTransmitter::~EthernetTransmitter() {
    cleanUpRelations();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void EthernetTransmitter::transmitData() {
    //#[ operation transmitData()
    dbuf[0] = 0x01;  
    
    if (dbuf[0] == 0x00)
    {   
    	// In case of any invalid joystick position
    	dbuf[1] = 0xFF;
    }
    
    send_data(sock, (char *)&dbuf);
    
    // The led toggles when data is sent   
    FIRE(this->itsLed, evBlink());
    //#]
}

Led* EthernetTransmitter::getItsLed() const {
    return itsLed;
}

void EthernetTransmitter::setItsLed(Led* p_Led) {
    itsLed = p_Led;
}

bool EthernetTransmitter::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void EthernetTransmitter::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void EthernetTransmitter::cleanUpRelations() {
    if(itsLed != NULL)
        {
            itsLed = NULL;
        }
}

SOCKADDR_IN EthernetTransmitter::getAddr() const {
    return addr;
}

void EthernetTransmitter::setAddr(SOCKADDR_IN p_addr) {
    addr = p_addr;
}

char EthernetTransmitter::getDbuf(int i1) const {
    return dbuf[i1];
}

void EthernetTransmitter::setDbuf(int i1, char p_dbuf) {
    dbuf[i1] = p_dbuf;
}

int EthernetTransmitter::getDstPort() {
    return dstPort;
}

void EthernetTransmitter::setDstPort(int p_dstPort) {
    dstPort = p_dstPort;
}

int EthernetTransmitter::getSock() const {
    return sock;
}

void EthernetTransmitter::setSock(int p_sock) {
    sock = p_sock;
}

void EthernetTransmitter::rootState_entDef() {
    {
        rootState_subState = state_0;
        rootState_active = state_0;
        //#[ state state_0.(Entry) 
        transmitData();
        //#]
    }
}

IOxfReactive::TakeEventStatus EthernetTransmitter::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_0
    if(rootState_active == state_0)
        {
            if(IS_EVENT_TYPE_OF(evNewJoystickPosition_ExamplePkg_id))
                {
                    OMSETPARAMS(evNewJoystickPosition);
                    //#[ transition 1 
                    dbuf[1] = params->joystickPosition;
                    //#]
                    rootState_subState = state_0;
                    rootState_active = state_0;
                    //#[ state state_0.(Entry) 
                    transmitData();
                    //#]
                    res = eventConsumed;
                }
            
        }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\EthernetTransmitter.cpp
*********************************************************************/
