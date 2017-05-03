/*********************************************************************
	Rhapsody	: 8.1.4 
	Login		: Hochschule Ulm
	Component	: TargetComponent 
	Configuration 	: Debug
	Model Element	: ExamplePkg
//!	Generated Date	: Wed, 3, May 2017  
	File Path	: TargetComponent\Debug\ExamplePkg.h
*********************************************************************/

#ifndef ExamplePkg_H
#define ExamplePkg_H

//## auto_generated
#include "WSTModelHeadersBase.h"
//## auto_generated
#include "rl_net.h"
//## auto_generated
class ActiveController;

//## auto_generated
class EthernetController;

//## auto_generated
class LED;

//## auto_generated
class SequentialController;

//## auto_generated
class TestBuilder;

//#[ ignore
#define evToggle_ExamplePkg_id 16401

#define evOn_ExamplePkg_id 16402

#define evOff_ExamplePkg_id 16403

#define evReceivedData_ExamplePkg_id 16404
//#]

//## package ExamplePkg


//## operation receive_data(int,char*)
void receive_data(int sock, char* buf);

//## operation send_data(int,char)
void send_data(int sock, const char * buf);

//## event evToggle()
class evToggle : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evToggle();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evOn()
class evOn : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evOn();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evOff()
class evOff : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evOff();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

//## event evReceivedData()
class evReceivedData : public WST_EVT {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evReceivedData();
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(WST_EVT_ID_t id) const;
};

#endif
/*********************************************************************
	File Path	: TargetComponent\Debug\ExamplePkg.h
*********************************************************************/
