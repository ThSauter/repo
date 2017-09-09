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
unsigned int localUdpPort = 4210;

//*** Station variables ***
IPAddress STAlocal_IP(192, 168, 0, 101);

//***General Variables***
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
  
  Serial.begin(115200); // Fire up the serial port
  swSer.begin(115200);
  WiFi.mode(WIFI_AP);
  
  // Configure the Soft Access Point. Somewhat verbosely... (for completeness sake)
  Serial.print("Soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(APlocal_IP, APgateway, APsubnet) ? "OK" : "Failed!"); // Configure network
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(APssid, APpassword) ? "OK" : "Failed!");                    // Setup the Access Point
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());                                                       // Confirm AP IP address
  
  Serial.print("Station connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("Signal Strength: %d dBm\n", WiFi.RSSI());
  
  // Setup the UDP port
  Serial.println("begin UDP port");
  Udp.begin(localUdpPort);
  Serial.print("local UDP port: ");
  Serial.println(localUdpPort );
}

void loop() {
  int serReadValue = 0;
  //Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum()); // Print number os stations connected to AP

  // Check for incoming UDP packets
  checkForWiFiData();

  // Check for incoming Serial packets
  checkForSerialData();

  if (WiFi.softAPgetStationNum() > 0)
  {
    digitalWrite(LEDGREEN, true);    
  }
  else
  {
    digitalWrite(LEDGREEN, false);     
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
    Serial.printf("[WiFi] Send %d byte(s) to %s, port %d\n", serLength, STAlocal_IP.toString().c_str(), 4209);

    Udp.beginPacket(STAlocal_IP, 4209);
    Udp.write(serIncomingPacket);
    Udp.endPacket();    
  }
}

