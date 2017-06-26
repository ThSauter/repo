/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetTransmitter
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\EthernetTransmitter.cpp
*********************************************************************/

//## auto_generated
#include "EthernetTransmitter.h"
//## link itsLed
#include "Led.h"
//## package DefaultPkg

//## class EthernetTransmitter
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
    
    addr.sin_addr.s_b1 = buf[0];
    addr.sin_addr.s_b2 = buf[1];
    addr.sin_addr.s_b3 = buf[2];
    addr.sin_addr.s_b4 = buf[3];
    
    // Connect socket
    connect (sock, (SOCKADDR *)&addr, sizeof (addr));
    
    
    
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 106, (void*)&itsLed);
    
    //#]
}

EthernetTransmitter::~EthernetTransmitter() {
    cleanUpRelations();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

void EthernetTransmitter::transmitData() {
    //#[ operation transmitData()
    extern int send (int sock, const char *buf, int len, int flags);
    int res = 0; 
    dbuf[0] = 0x01;  
    
    if (dbuf[1] == 0x00)
    {   
    	// In case of any invalid joystick position
    	dbuf[1] = 0xFF;
    }
    
    if (res <= 0) {
    	// Send the data to Led Server.
    	res = send (sock, (char *)&dbuf, 2, 0);
    	if (res < 0) {
    		;
    	}
    }
    
    //send_data(sock, (char *)&dbuf);
    
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
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: MCB1700\Debug\EthernetTransmitter.cpp
*********************************************************************/
