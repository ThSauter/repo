/* Auto generated file by WST RXF Simplifier. Please do not change the content. */

#include "WST.h"

extern void WSTMonitor_sendDataStruct( void *dataStr, uint16 length );
extern uint16 WSTMonitor_getTypeSize0();
extern uint16 WSTMonitor_getTypeSize1();
extern uint16 WSTMonitor_getTypeSize2();
extern uint16 WSTMonitor_getTypeSize3();
extern uint16 WSTMonitor_getTypeSize4();
extern uint16 WSTMonitor_getTypeSize5();
extern uint16 WSTMonitor_getTypeSize6();
extern uint16 WSTMonitor_getTypeSize7();
extern uint16 WSTMonitor_getTypeSize8();
extern uint16 WSTMonitor_getTypeSize9();

void WSTMonitor_sendTypeSize()
{
	uint8 command[ 2 ];
	uint16 types[ 11 ];
	types[ 0 ] = sizeof(void*);
	types[ 1 ] = WSTMonitor_getTypeSize0();
	types[ 2 ] = WSTMonitor_getTypeSize1();
	types[ 3 ] = WSTMonitor_getTypeSize2();
	types[ 4 ] = WSTMonitor_getTypeSize3();
	types[ 5 ] = WSTMonitor_getTypeSize4();
	types[ 6 ] = WSTMonitor_getTypeSize5();
	types[ 7 ] = WSTMonitor_getTypeSize6();
	types[ 8 ] = WSTMonitor_getTypeSize7();
	types[ 9 ] = WSTMonitor_getTypeSize8();
	types[ 10 ] = WSTMonitor_getTypeSize9();

	command[ 0 ] = 22;

	command[ 1 ] = WST_MONITOR_COMMAND_SEND_TYPES;

	WSTMonitor_sendDataStruct( command, 2u );
	WSTMonitor_sendDataStruct( types, 22 );
}
