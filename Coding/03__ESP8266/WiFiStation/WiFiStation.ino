#include <ESP8266WiFi.h>  // Used for the soft AP
#include <WiFiUdp.h>      // Used for UDP communication
#include <SoftwareSerial.h>
#include <Ticker.h>

WiFiUDP Udp;
//D7 == GPIO 13 == RXD2
//D8 == GPIO 15 == TXD2
SoftwareSerial swSer(13, 15, false, 256);
Ticker LedRed;  

//*** Soft Ap variables ***
const char *APssid = "ESP8266-12E";
const char *APpassword = "";                // No password for the AP
IPAddress APlocal_IP(192, 168, 0, 100);
IPAddress APgateway(192, 168, 0, 254);
IPAddress APsubnet(255, 255, 255, 0);

//***STAtion variables ***
IPAddress STAlocal_IP(192, 168, 0, 101);
IPAddress STAgateway(192, 168, 0, 254);
IPAddress STAsubnet(255, 255, 255, 0);

//***General Variables***
unsigned int localUdpPort = 4209;
char serIncomingPacket[255];
char incomingPacket[255];

#define LEDRED D1
#define LEDGREEN D2

void setup() {
  
  // Red LED
  pinMode(LEDRED, OUTPUT);  
  LedRed.attach(0.5, blinkLedRed); 
  
  // Green LED
  pinMode(LEDGREEN, OUTPUT);  
  digitalWrite(LEDGREEN, false);  

  // Start serial port via USB
  Serial.begin(115200); 
  // Start serial port via RXD2/TXD2
  swSer.begin(115200);
  
  Serial.printf("\nConnecting to %s ", APssid);
  WiFi.begin(APssid, APpassword);
  WiFi.config(STAlocal_IP, STAgateway, STAsubnet);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LEDGREEN, true);
  Serial.println(" connected");
  
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {

  // Check for incoming UDP packets 
  checkForWiFiData();

  // Check for incoming serial packets
  checkForSerialData();

  // Check if WiFi connection is alive
  if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(LEDGREEN, false);
  }
  else
  {
    digitalWrite(LEDGREEN, true);
  }
}

void blinkLedRed()
{
  int state = digitalRead(LEDRED);
  digitalWrite(LEDRED, !state);
}

void checkForWiFiData()
{
  int i = 0;
  int wifiLength = 0;
  
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.printf("-------------------------------------------\n");
    Serial.printf("[WiFi] Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    wifiLength = Udp.read(incomingPacket, 255);

    // Forward received WiFi message via Serial to the EvalBoard
    Serial.printf("[WiFi] UDP packet contents: 0x%02X", incomingPacket[0]);
    swSer.write(incomingPacket[0]);  
  
    for (i = 1; i< wifiLength; i++)
    {
      Serial.printf(", 0x%02X", incomingPacket[i]);   
      swSer.write(incomingPacket[i]);    
    }

    Serial.printf("\n");
    Serial.printf("[Serial] Send %d byte(s)\n", wifiLength);
  }
}

void checkForSerialData()
{ 
  int i = 0;
  int serLength = 0;

  while (swSer.available() > 0) {
    serIncomingPacket[i] = swSer.read();
    i++;
    delay(10);
  }

  if (i > 0)
  {
    serLength = i;
    Serial.printf("-------------------------------------------\n");
    Serial.printf("[Serial] Received %d byte(s)\n", serLength);  
    Serial.printf("[Serial] Packet contents: 0x%02X", serIncomingPacket[0]);
    for(i = 1; i < serLength; i++)
    {
      Serial.printf(", 0x%02X", serIncomingPacket[i]);     
    }
    
    Serial.printf("\n");
    Serial.printf("[WiFi] Send %d byte(s) to %s, port %d\n", serLength, APlocal_IP.toString().c_str(), 4210);
    
    Udp.beginPacket(APlocal_IP, 4210);
    Udp.write(serIncomingPacket);
    Udp.endPacket();    
  }
}

