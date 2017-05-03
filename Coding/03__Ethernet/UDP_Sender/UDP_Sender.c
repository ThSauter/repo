/*------------------------------------------------------------------------------
 * Name:    UDP_Sender.c
 * Purpose: LED UDP Sender example
 *----------------------------------------------------------------------------*/

#include "cmsis_os.h"                   /* CMSIS RTOS definitions             */
#include "rl_net.h"                     /* Network definitions                */

#include "Board_GLCD.h"
#include "GLCD_Config.h"

#include "Board_LED.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

#define PORT_NUM 1001
#define BLINKLED 0x01                   /* Command for blink the leds         */

int32_t udp_soc;
uint16_t bindex;
bool wait_ack;

/// Initialize display
static void init_display  () {
  GLCD_Initialize         ();
  GLCD_SetBackgroundColor (GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor (GLCD_COLOR_WHITE);
  GLCD_ClearScreen        ();
  GLCD_SetFont            (&GLCD_Font_16x24);
  GLCD_DrawString         (0, 3*24, "      ");
  GLCD_DrawString         (0, 4*24, "      ");
	GLCD_DrawString         (0, 5*24, "  to 192.168.0.101  ");
}

/*
uint16_t udp_callback (uint8_t socket, uint8_t *remip, uint16_t port, uint8_t *buf, uint16_t len) {
// This function is called when UDP data has been received.
	if (len == 2) {
		wait_ack = false;
		LED_On(1);
	}
	LED_On(2);
	return (0);
}
*/

uint32_t udp_callback (int32_t socket, const uint8_t *ip_addr, uint16_t port, const uint8_t *buf, uint32_t len) {
// This function is called when UDP data has been received.
	if (len == 2) {
		wait_ack = false;
	}
	return (0);
}

void send_data (void) {
	static const uint8_t rem_IP[4] = {192,168,0,101};
	uint8_t *sendbuf;
	
	if (wait_ack == true) {
		return;
	}

		sendbuf = udp_get_buf (2);
		sendbuf[0] = 0x01;
		sendbuf[1] = 0xAA;
		udp_send (udp_soc, rem_IP, 1000, sendbuf, 2);
}


/*----------------------------------------------------------------------------
  Main Thread 'main': Run Network
 *---------------------------------------------------------------------------*/
int main (void) {
	
	int a = 0;
  LED_Initialize ();
  init_display ();
  net_initialize ();
	
	 udp_soc = udp_get_socket (0, UDP_OPT_SEND_CHECKSUM | UDP_OPT_VERIFY_CHECKSUM, udp_callback);
	 udp_open (udp_soc, 1000);
	 bindex = 0;
	 wait_ack = false;


  while(1) {
		net_main ();

		// Only for LED purposes
		if (a == 500000)
		{
			LED_On(0);
			send_data ();
		}
		else if (a == 1000000)
		{
			LED_Off(0);
			a = 0;
		}

		a++;
  }
}
