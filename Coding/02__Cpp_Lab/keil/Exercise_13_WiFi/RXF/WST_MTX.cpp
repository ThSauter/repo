/********************************************************************
	Rhapsody	: 8.0 
	Login		: Administrator
	Component	: RXFGen 
	Configuration 	: TestCfg
	Model Element	: WST_MTX
//!	Generated Date	: Wed, 3, Apr 2013  
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MTX.cpp
*********************************************************************/

//## auto_generated
#include "WST_MTX.h"
//## auto_generated
#include "WST.h"
//## package RXF::RXF_BehaviorPkg

//## class WST_MTX
WST_MTX::WST_MTX( void ) {
    //#[ operation WST_MTX()
    this->mtx = NULL;
    WST_OSW_MTX_init( this );
    //#]
}
          
WST_MTX::WST_MTX( const WST_MTX* mtx ) {
    //#[ operation WST_MTX()
    this->mtx = (WST_MTX*)mtx;
    WST_OSW_MTX_enterCriticalRegion( (WST_MTX*) mtx );
    //#]
}

WST_MTX::~WST_MTX( void ) {
    //#[ operation ~WST_MTX()
    if( this->mtx != NULL )
    {
      WST_OSW_MTX_exitCriticalRegion( this->mtx );
    }
    else
    {
      WST_OSW_MTX_cleanup( this );
    }
    //#]
}

WST_RTOS_MTX_t *WST_MTX::WST_MTX_getRtosMutex( void )
{
  return &(this->rtosMutex);
}

void WST_MTX::WST_MTX_enterCriticalRegion( void ) {
    //#[ operation WST_MTX_enterCriticalRegion()
    WST_OSW_MTX_enterCriticalRegion( this );
    //#]
}

void WST_MTX::WST_MTX_exitCriticalRegion( void ) {
    //#[ operation WST_MTX_exitCriticalRegion()
    WST_OSW_MTX_exitCriticalRegion( this );
    //#]
}


//## operation WST_MTX()
WST_MTX_inUse::WST_MTX_inUse( const WST_MTX* mtx ){
	myMutex = mtx;
	myMutex.WST_MTX_enterCriticalRegion();
}

//## operation ~WST_MTX()
WST_MTX_inUse::~WST_MTX_inUse( void ){
	myMutex.WST_MTX_exitCriticalRegion();
}

/*********************************************************************
	File Path	: C:\V6\Component\Shared\Source\CPP\WST_MTX.cpp
*********************************************************************/
