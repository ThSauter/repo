/********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetController
//!	Generated Date	: Sat, 20, May 2017  
	File Path	: MCB1700/Debug/EthernetController.cpp
*********************************************************************/

//## auto_generated
#include "EthernetController.h"
//## package DefaultPkg

//## class EthernetController
int EthernetController::dstPort = 1001;

const char* EthernetController::hostIpAddr = {"192.168.0.100"};

const char* EthernetController::remoteIpAddr = {"192.168.0.101"};

netStatus EthernetController::status = (netStatus)-1;

EthernetController::EthernetController() {
    //#[ operation EthernetController()
    unsigned char buf[8];
    
    if (status != netOK)   
    {	
        // Initialize the network component only once
    	status = netInitialize ();
    	
    	// Set the host ip address once
    	netIP_aton (hostIpAddr, NET_ADDR_IP4, buf);
        netIF_SetOption (NET_IF_CLASS_ETH | 0, netIF_OptionIP4_Address, buf, NET_ADDR_IP4_LEN);
    }
    //#]
}

EthernetController::~EthernetController() {
    //#[ operation ~EthernetController()
    closesocket (sock);
    //#]
}

char* EthernetController::getHostIpAddress() {
    //#[ operation getHostIpAddress()
    char* temp;   
    // hostIpAddr is a const char*
    strcpy(temp, hostIpAddr); 
    
    return temp;
    //#]
}

char* EthernetController::getTargetIpAddress() {
    //#[ operation getTargetIpAddress()
    char* temp;   
    // hostIpAddr is a const char*
    strcpy(temp, hostIpAddr); 
    
    return temp;
    //#]
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

const char* EthernetController::getHostIpAddr() {
    return hostIpAddr;
}

const char* EthernetController::getRemoteIpAddr() {
    return remoteIpAddr;
}

int EthernetController::getSock() const {
    return sock;
}

void EthernetController::setSock(int p_sock) {
    sock = p_sock;
}

netStatus EthernetController::getStatus() {
    return status;
}

void EthernetController::setStatus(netStatus p_status) {
    status = p_status;
}

/*********************************************************************
	File Path	: MCB1700/Debug/EthernetController.cpp
*********************************************************************/
