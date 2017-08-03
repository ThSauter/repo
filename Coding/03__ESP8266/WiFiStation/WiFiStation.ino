#include <ESP8266WiFi.h> // Used for the soft AP
#include <WiFiUdp.h> // used for UDP comms.
#include <SoftwareSerial.h>

WiFiUDP Udp;
//D7 == GPIO 13 == RXD2
//D8 == GPIO 15 == TXD2
SoftwareSerial swSer(13, 15, true, 256);  

//*** Soft Ap variables ***
const char *APssid = "ESP8266-12E";
const char *APpassword = ""; // No password for the AP
IPAddress APlocal_IP(192, 168, 0, 100);
IPAddress APgateway(192, 168, 0, 254);
IPAddress APsubnet(255, 255, 255, 0);

//***STAtion variables ***
const char *STAssid = "ESP8266-12E"; // Network to be joined as a station SSID
const char *STApassword = ""; // Network to be joined as a station password
IPAddress STAlocal_IP(192, 168, 0, 101);
IPAddress STAgateway(192, 168, 0, 254);
IPAddress STAsubnet(255, 255, 255, 0);

//***UDP Variables***
unsigned int localUdpPort = 4209;
char incomingPacket[255];
char replyPacket[] = "Hi there! Got the message :-)";
char initialPacket[] = "Hi world!";

//***General Variables***
const int LEDpin = 2;

void setup() {
 Serial.begin(115200); //fire up the serial port
 swSer.begin(115200);
 //pinMode(LEDpin,OUTPUT);
 //digitalWrite(LEDpin,HIGH);
 
 //WiFi.mode(WIFI_AP);
 
 Serial.printf("Connecting to %s ", STAssid);
 WiFi.begin(STAssid, STApassword);
 WiFi.config(STAlocal_IP, STAgateway, STAsubnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
 Serial.println(" connected");
 
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  int serReadValue = 0;
 int packetSize = Udp.parsePacket();
 if (packetSize)
 {
   // receive incoming UDP packets
   Serial.printf("[WiFi] Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
   int len = Udp.read(incomingPacket, 255);
   if (len > 0)
   {
    incomingPacket[len] = 0;
   }
   Serial.printf("[WiFi] UDP packet contents: %s\n", incomingPacket);
  
   // send back a reply, to the IP address and port we got the packet from
   //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
   //Udp.write(replyPacket);
   //Udp.endPacket();
   //Udp.beginPacket(APlocal_IP, 4210);
   //Serial.println(Udp.write(incomingPacket[0]) ? "W OK" : "W Failed!");   
   //Udp.endPacket();

    /* Forward received WiFi message via Serial to the EvalBoard */
    Serial.printf("[Serial] Write: 0x%02X\n", incomingPacket[0]);
    char helper = ~incomingPacket[0] << 1u;
    Serial.printf("[Serial] Write: 0x%02X\n", helper);
    swSer.write(helper);
 }

  // Check for incoming Serial packets
  while (swSer.available() > 0) {
    Serial.printf("[Serial] Received byte\n");
    serReadValue = swSer.read();
    Serial.printf("[WiFi] Send one byte to %s, port %d\n", APlocal_IP.toString().c_str(), 4210);
    Udp.beginPacket(APlocal_IP, 4210);
    Udp.write(serReadValue);
    Udp.endPacket();
  }
}
