/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetController
//!	Generated Date	: Tue, 23, May 2017  
	File Path	: MCB1700\Debug\EthernetController.h
*********************************************************************/

#ifndef EthernetController_H
#define EthernetController_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include <stdio.h>
//## auto_generated
#include "DefaultPkg.h"
//## dependency rl_net
#include <rl_net.h>
//## package DefaultPkg

//## class EthernetController
class EthernetController {
    ////    Constructors and destructors    ////
    
public :

    //## operation EthernetController()
    EthernetController();
    
    //## operation ~EthernetController()
    ~EthernetController();
    
    ////    Operations    ////
    
    //## operation getHostIpAddress()
    const char* getHostIpAddress();
    
    //## operation getRemoteIpAddress()
    const char* getRemoteIpAddress();
    
    ////    Additional operations    ////

protected :

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
    static const char* getHostIpAddr();
    
    //## auto_generated
    static const char* getRemoteIpAddr();
    
    //## auto_generated
    int getSock() const;
    
    //## auto_generated
    void setSock(int p_sock);

private :

    //## auto_generated
    static netStatus getStatus();
    
    //## auto_generated
    static void setStatus(netStatus p_status);

public :

    static uint16 ClassWSTMonitor_getTypeSize1();
    
    static uint16 ClassWSTMonitor_getTypeSize2();
    
    ////    Attributes    ////

protected :

    SOCKADDR_IN addr;		//## attribute addr
    
    char dbuf[4];		//## attribute dbuf
    
    static int dstPort;		//## attribute dstPort
    
    static const char* hostIpAddr;		//## attribute hostIpAddr
    
    static const char* remoteIpAddr;		//## attribute remoteIpAddr
    
    int sock;		//## attribute sock
    
    static netStatus status;		//## attribute status
    
    ////    Framework operations    ////
};

uint16 WSTMonitor_getTypeSize1();

uint16 WSTMonitor_getTypeSize2();

#endif
/*********************************************************************
	File Path	: MCB1700\Debug\EthernetController.h
*********************************************************************/
