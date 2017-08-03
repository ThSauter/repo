#include <ESP8266WiFi.h> // Used for the soft AP
#include <WiFiUdp.h> // used for UDP comms.

WiFiUDP Udp;

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
 
 int packetSize = Udp.parsePacket();
 if (packetSize)
   {
   // receive incoming UDP packets
   Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
   int len = Udp.read(incomingPacket, 255);
   if (len > 0)
   {
    incomingPacket[len] = 0;
   }
   Serial.printf("UDP packet contents: %s\n", incomingPacket);
  
   // send back a reply, to the IP address and port we got the packet from
   Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
   Udp.write(replyPacket);
   Udp.endPacket();
 }
 else
   {
   // send back a reply, to the IP address and port we got the packet from
    Serial.println("Ping");
    Serial.println(Udp.beginPacket(APlocal_IP, 4210) ? "B OK" : "B Failed!");
    Serial.println(Udp.write(initialPacket) ? "W OK" : "W Failed!");   
   Serial.println(Udp.endPacket() ? "E OK" : "E Failed!");
   delay(1000);
   }
}
