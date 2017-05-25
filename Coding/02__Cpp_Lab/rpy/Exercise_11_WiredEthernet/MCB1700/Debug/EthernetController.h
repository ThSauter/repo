/*********************************************************************
	Rhapsody	: 8.2 
	Login		: sauter
	Component	: MCB1700 
	Configuration 	: Debug
	Model Element	: EthernetController
//!	Generated Date	: Sat, 20, May 2017  
	File Path	: MCB1700/Debug/EthernetController.h
*********************************************************************/

#ifndef EthernetController_H
#define EthernetController_H

//## auto_generated
#include <oxf/oxf.h>
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
    char* getHostIpAddress();
    
    //## operation getTargetIpAddress()
    char* getTargetIpAddress();
    
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
    
    ////    Attributes    ////

protected :

    SOCKADDR_IN addr;		//## attribute addr
    
    char dbuf[2];		//## attribute dbuf
    
    static int dstPort;		//## attribute dstPort
    
    static const char* hostIpAddr;		//## attribute hostIpAddr
    
    static const char* remoteIpAddr;		//## attribute remoteIpAddr
    
    int sock;		//## attribute sock
    
    static netStatus status;		//## attribute status
};

#endif
/*********************************************************************
	File Path	: MCB1700/Debug/EthernetController.h
*********************************************************************/
