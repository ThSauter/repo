/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: ActiveController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\ActiveController.cpp
*********************************************************************/

//## auto_generated
#include "ActiveController.h"
//## link itsLED
#include "LED.h"
//## package ExamplePkg

//## class ActiveController
int ActiveController::dstPort = 1001;

unsigned char ActiveController::remoteIpAddr[4] = {192, 168, 0, 100};

ActiveController::ActiveController(WST_TSK* myTask) {
    setTask( this, true );
    itsLED = NULL;
    initStatechart();
    //#[ operation ActiveController()
    //UDP stuff
    netInitialize ();
    
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
    WSTMonitor_sendInit( this, 101, (void*)&addr);
    
    //#]
}

ActiveController::~ActiveController() {
    //#[ operation ~ActiveController()
    closesocket (sock);
    
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
    //#]
    cleanUpRelations();
    cancelTimeouts();
}

LED* ActiveController::getItsLED() const {
    return itsLED;
}

void ActiveController::setItsLED(LED* p_LED) {
    itsLED = p_LED;
}

bool ActiveController::startBehavior() {
    bool done = false;
    done = WST_FSM::startBehavior();
    if(done)
        {
            startDispatching();
        }
    return done;
}

void ActiveController::initStatechart() {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
    rootState_timeout = NULL;
}

void ActiveController::cleanUpRelations() {
    if(itsLED != NULL)
        {
            itsLED = NULL;
        }
}

void ActiveController::cancelTimeouts() {
    cancel(rootState_timeout);
}

bool ActiveController::cancelTimeout(const IOxfTimeout* arg) {
    bool res = false;
    if(rootState_timeout == arg)
        {
            rootState_timeout = NULL;
            res = true;
        }
    return res;
}

SOCKADDR_IN ActiveController::getAddr() const {
    return addr;
}

void ActiveController::setAddr(SOCKADDR_IN p_addr) {
    addr = p_addr;
}

char ActiveController::getDbuf(int i1) const {
    return dbuf[i1];
}

void ActiveController::setDbuf(int i1, char p_dbuf) {
    dbuf[i1] = p_dbuf;
}

int ActiveController::getDstPort() {
    return dstPort;
}

void ActiveController::setDstPort(int p_dstPort) {
    dstPort = p_dstPort;
}

unsigned char ActiveController::getRemoteIpAddr(int i1) {
    return remoteIpAddr[i1];
}

void ActiveController::setRemoteIpAddr(int i1, unsigned char p_remoteIpAddr) {
    remoteIpAddr[i1] = p_remoteIpAddr;
}

int ActiveController::getSock() const {
    return sock;
}

void ActiveController::setSock(int p_sock) {
    sock = p_sock;
}

uint16 ActiveController::ClassWSTMonitor_getTypeSize0() {
    return sizeof( SOCKADDR_IN );
}

uint16 ActiveController::ClassWSTMonitor_getTypeSize1() {
    return sizeof( char );
}

uint16 ActiveController::ClassWSTMonitor_getTypeSize2() {
    return sizeof( int );
}

void ActiveController::rootState_entDef() {
    {
        rootState_subState = Receive;
        rootState_active = Receive;
        //#[ state Receive.(Entry) 
        receive_data(sock, dbuf);  
        if (dbuf[0] == 0x01) {
        	FIRE(this->itsLED, evToggle());
        }
        //#]
        rootState_timeout = scheduleTimeout(100, NULL);
    }
}

IOxfReactive::TakeEventStatus ActiveController::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Receive
    if(rootState_active == Receive)
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            rootState_subState = Receive;
                            rootState_active = Receive;
                            //#[ state Receive.(Entry) 
                            receive_data(sock, dbuf);  
                            if (dbuf[0] == 0x01) {
                            	FIRE(this->itsLED, evToggle());
                            }
                            //#]
                            rootState_timeout = scheduleTimeout(100, NULL);
                            res = eventConsumed;
                        }
                }
            
        }
    this->activeState[ 0 ] = rootState_active;
    return res;
}

uint16 WSTMonitor_getTypeSize0() {
    return ActiveController::ClassWSTMonitor_getTypeSize0( );
}

uint16 WSTMonitor_getTypeSize1() {
    return ActiveController::ClassWSTMonitor_getTypeSize1( );
}

uint16 WSTMonitor_getTypeSize2() {
    return ActiveController::ClassWSTMonitor_getTypeSize2( );
}

/*********************************************************************
	File Path	: TargetComponent\Debug\ActiveController.cpp
*********************************************************************/
