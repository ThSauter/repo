/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: ActiveController
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\ActiveController.cpp
*********************************************************************/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

//   <h>Remote IP Address
//   ====================
//
//     <o>IP1: Address byte 1 <0-255>
//     <i> Default: 192
#define IP1            192

//     <o>IP2: Address byte 2 <0-255>
//     <i> Default: 168
#define IP2            168

//     <o>IP3: Address byte 3 <0-255>
//     <i> Default: 0
#define IP3            0

//     <o>IP4: Address byte 4 <0-255>
//     <i> Default: 100
#define IP4            100

//   </h>

//   <o>Remote Port <1-65535>
//   <i> Do not set number of port too small,
//   <i> maybe it is already used.
//   <i> Default: 1001
#define PORT_NUM       1001



//## auto_generated
#include "ActiveController.h"
//## link itsLED
#include "LED.h"

#include "rl_net.h"                     /* Network definitions                */
//## package ExamplePkg

int sock;
SOCKADDR_IN addr;
char dbuf[4];
	
//## class ActiveController
ActiveController::ActiveController(WST_TSK* myTask) {
    setTask( this, true );
	
		//UDP stuff
	  netInitialize ();
	
		sock = socket (AF_INET, SOCK_DGRAM, 0);

		addr.sin_port      = htons(PORT_NUM);
		addr.sin_family    = PF_INET;
		addr.sin_addr.s_b1 = IP1;
		addr.sin_addr.s_b2 = IP2;
		addr.sin_addr.s_b3 = IP3;
		addr.sin_addr.s_b4 = IP4;
		bind (sock, (SOCKADDR *)&addr, sizeof(addr));

		connect (sock, (SOCKADDR *)&addr, sizeof (addr));
		//UDP stuff
	
    itsLED = NULL;
    initStatechart();
    this->setOwner( this );
    WSTMonitor_sendInit( this, 101, (void*)&itsLED);
    
}

ActiveController::~ActiveController() {
		closesocket (sock);
    cleanUpRelations();
    cancelTimeouts();
    WSTMonitor_sendDestroy( (WST_FSM*)this );
    
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

uint16 ActiveController::ClassWSTMonitor_getTypeSize0() {
    return sizeof( int );
}

void ActiveController::rootState_entDef() {
    {
        rootState_subState = Blinking;
        rootState_active = Blinking;
        rootState_timeout = scheduleTimeout(400, NULL);
    }
}

IOxfReactive::TakeEventStatus ActiveController::rootState_processEvent() {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State Blinking
    if(rootState_active == Blinking)
        {
            if(IS_EVENT_TYPE_OF(WST_TMR_id))
                {
                    if(getCurrentEvent() == rootState_timeout)
                        {
                            cancel(rootState_timeout);
                            //#[ transition 1 
                            
                            FIRE(this->itsLED, evToggle());
														send_udp_data();
														
                            //#]
                            rootState_subState = Blinking;
                            rootState_active = Blinking;
                            rootState_timeout = scheduleTimeout(400, NULL);
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

void send_udp_data()
{
  int res = 0;



	dbuf[0] = 0x01;
	dbuf[1] = 0x20;
	// Try to receive data from LED Server.
	//res = recv (sock, dbuf, sizeof (dbuf), 0);
	if (res <= 0) {
		// Send the data to LED Server.
		res = send (sock, (char *)&dbuf, 2, 0);
		if (res < 0) {
			;
		}
	}

}

/*********************************************************************
	File Path	: TargetComponent\Debug\ActiveController.cpp
*********************************************************************/
