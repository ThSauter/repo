/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: EthernetController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\EthernetController.cpp
*********************************************************************/

//## auto_generated
#include "EthernetController.h"
//## link itsLED
#include "LED.h"
//## package ExamplePkg

//## class EthernetController
int EthernetController::dstPort = 1001;

unsigned char EthernetController::remoteIpAddr[4] = {192, 168, 0, 100};

EthernetController::EthernetController(WST_TSK* myTask) {
    setTask( this, true );
    itsLED = NULL;
    initStatechart();
    //#[ operation EthernetController()
    //UDP stuff
    
    
    sock = socket (AF_INET, SOCK_DGRAM, 0);
    
    addr.sin_port      = htons(dstPort);
    addr.sin_family    = PF_INET;
    addr.sin_addr.s_b1 = remoteIpAddr[0];
    addr.sin_addr.s_b2 = remoteIpAddr[1];
    addr.sin_addr.s_b3 = remoteIpAddr[2];
    addr.sin_addr.s_b4 = remoteIpAddr[3];
    bind (sock, (SOCKADDR *)&addr, sizeof(addr));
    
    connect (sock, (SOCKADDR *)&addr, sizeof (addr));
    //UDP stuff
    
    
    
    this->setOwner( this );
    WSTMonitor_sendInit( this, 105, (void*)&addr);
    
    //#]
}

EthernetController::~EthernetController() {
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
}

LED* EthernetController::getItsLED() const {
    return itsLED;
}

void EthernetController::setItsLED(LED* p_LED) {
    itsLED = p_LED;
}

bool EthernetController::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void EthernetController::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void EthernetController::cleanUpRelations() {
    if(itsLED != NULL)
        {
            itsLED = NULL;
        }
}

void EthernetController::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool EthernetController::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

SOCKADDR_IN EthernetController::getAddr() const {
    return addr;
}

void EthernetController::setAddr(SOCKADDR_IN p_addr) {
    addr = p_addr;
}

char EthernetController::getDbuf(int i1) const {
    return dbuf[i1];
}

void EthernetController::setDbuf(int i1, char p_dbuf) {
    dbuf[i1] = p_dbuf;
}

int EthernetController::getDstPort() {
    return dstPort;
}

void EthernetController::setDstPort(int p_dstPort) {
    dstPort = p_dstPort;
}

unsigned char EthernetController::getRemoteIpAddr(int i1) {
    return remoteIpAddr[i1];
}

void EthernetController::setRemoteIpAddr(int i1, unsigned char p_remoteIpAddr) {
    remoteIpAddr[i1] = p_remoteIpAddr;
}

int EthernetController::getSock() const {
    return sock;
}

void EthernetController::setSock(int p_sock) {
    sock = p_sock;
}

void EthernetController::rootState_entDef() {
    {
        rootState_subState = state_0;
        rootState_active = state_0;
        //#[ state state_0.(Entry) 
        send_data(sock, (char *)&dbuf); 
        //#]
        rootState_timeout = scheduleTimeout(1000, NULL);
    }
}

IOxfReactive::TakeEventStatus EthernetController::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State state_0
    if(rootState_active == state_0)
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            //#[ transition 1 
                            FIRE(this->itsLED, evToggle());
                            //#]
                            rootState_subState = state_0;
                            rootState_active = state_0;
                            //#[ state state_0.(Entry) 
                            send_data(sock, (char *)&dbuf); 
                            //#]
                            rootState_timeout = scheduleTimeout(1000, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

/*********************************************************************
	File Path	: TargetComponent\Debug\EthernetController.cpp
*********************************************************************/
