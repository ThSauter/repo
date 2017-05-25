/********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetTransmitter
//!	Generated Date	: Sat, 20, May 2017  
	File Path	: MCB1700/Debug/EthernetTransmitter.cpp
*********************************************************************/

//## auto_generated
#include "EthernetTransmitter.h"
//## link itsLed
#include "Led.h"
//## package DefaultPkg

//## class EthernetTransmitter
EthernetTransmitter::EthernetTransmitter(IOxfActive* theActiveContext) {
    setActiveContext(this, true);
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
    
    addr.sin_addr.s_b1 = buf[0];
    addr.sin_addr.s_b2 = buf[1];
    addr.sin_addr.s_b3 = buf[2];
    addr.sin_addr.s_b4 = buf[3];
    
    // Bind to socket 
    bind (sock, (SOCKADDR *)&addr, sizeof(addr));
    
    // Connect socket
    connect (sock, (SOCKADDR *)&addr, sizeof (addr));
    
    
    
    
    //#]
}

EthernetTransmitter::~EthernetTransmitter() {
    cleanUpRelations();
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
    done = OMReactive::startBehavior();
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
            if(IS_EVENT_TYPE_OF(evNewJoystickPosition_DefaultPkg_id))
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
    return res;
}

/*********************************************************************
	File Path	: MCB1700/Debug/EthernetTransmitter.cpp
*********************************************************************/
