/********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: ExamplePkg
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\ExamplePkg.cpp
*********************************************************************/

//## auto_generated
#include "ExamplePkg.h"
//## auto_generated
#include "ActiveController.h"
//## auto_generated
#include "EthernetController.h"
//## auto_generated
#include "LED.h"
//## auto_generated
#include "SequentialController.h"
//## auto_generated
#include "TestBuilder.h"
//## package ExamplePkg


//## operation receive_data(int,char*)
void receive_data(int sock, char* buf) {
    //#[ operation receive_data(int,char*)
    char dbuf[4];
    int res;
    res = recv (sock, dbuf, sizeof (dbuf), 0);
    if (res <= 0) {
    	;
    }
    
    buf[0] = dbuf[0];   
    buf[1] = dbuf[1];  
    
    //#]
}

//## operation send_data(int,char)
void send_data(int sock, const char * buf) {
    //#[ operation send_data(int,char)
    int res = 0; 
    char dbuf[4];
    
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
    //#]
}

//## event evToggle()
evToggle::evToggle() {
    setId(evToggle_ExamplePkg_id);
    this->size = sizeof( evToggle ) - sizeof( WST_EVT );
}

bool evToggle::isTypeOf(WST_EVT_ID_t id) const {
    return (evToggle_ExamplePkg_id==id);
}

//## event evOn()
evOn::evOn() {
    setId(evOn_ExamplePkg_id);
    this->size = sizeof( evOn ) - sizeof( WST_EVT );
}

bool evOn::isTypeOf(WST_EVT_ID_t id) const {
    return (evOn_ExamplePkg_id==id);
}

//## event evOff()
evOff::evOff() {
    setId(evOff_ExamplePkg_id);
    this->size = sizeof( evOff ) - sizeof( WST_EVT );
}

bool evOff::isTypeOf(WST_EVT_ID_t id) const {
    return (evOff_ExamplePkg_id==id);
}

//## event evReceivedData()
evReceivedData::evReceivedData() {
    setId(evReceivedData_ExamplePkg_id);
    this->size = sizeof( evReceivedData ) - sizeof( WST_EVT );
}

bool evReceivedData::isTypeOf(WST_EVT_ID_t id) const {
    return (evReceivedData_ExamplePkg_id==id);
}

/*********************************************************************
	File Path	: TargetComponent\Debug\ExamplePkg.cpp
*********************************************************************/
