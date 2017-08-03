#include <ESP8266WiFi.h> // Used for the soft AP
#include <WiFiUdp.h> 
#include <SoftwareSerial.h>
#include <Ticker.h>

WiFiUDP Udp;
//D7 == GPIO 13 == RXD2
//D8 == GPIO 15 == TXD2
SoftwareSerial swSer(13, 15, true, 256);  
Ticker LedRed;

//*** Soft Ap variables ***
const char *APssid = "ESP8266-12E";
const char *APpassword = ""; // No password for the AP
IPAddress APlocal_IP(192, 168, 0, 100);
IPAddress APgateway(192, 168, 0, 254);
IPAddress APsubnet(255, 255, 255, 0);
unsigned int localUdpPort = 4210;

//*** Station variables ***
IPAddress STAlocal_IP(192, 168, 0, 101);

char incomingPacket[255];
char replyPacketWiFi[] = "[WiFi] Got message\n";

#define LEDRED D1

void setup() {
  
  /* Red LED */
  pinMode(LEDRED, OUTPUT);  
  LedRed.attach(0.5, blinkLedRed); 
  
  Serial.begin(115200); //fire up the serial port
  swSer.begin(115200);
  WiFi.mode(WIFI_AP);
  
  // Configure the Soft Access Point. Somewhat verbosely... (for completeness sake)
  Serial.print("Soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(APlocal_IP, APgateway, APsubnet) ? "OK" : "Failed!"); // configure network
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(APssid, APpassword) ? "OK" : "Failed!"); // Setup the Access Point
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP()); // Confirm AP IP address
  
  Serial.print("Station connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("Signal Strength: %d dBm\n", WiFi.RSSI());
  
  // Setup the UDP port
  Serial.println("begin UDP port");
  Udp.begin(localUdpPort);
  Serial.print("local UDP port: ");
  Serial.println(localUdpPort );
  
  //Serial.println("\nSoftware serial test started");
  
  //for (char ch = ' '; ch <= 'z'; ch++) {
  //  swSer.write(~ch);
  //}
  //swSer.println("");
}

void loop() {
  int serReadValue = 0;
  //Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum()); // Print number os stations connected to AP

  // Check for incoming UDP packets
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
    //Udp.write(replyPacketWiFi);
    //Udp.endPacket();
    
    // send back a reply, to the IP address and port we got the packet from
    //digitalWrite(LEDRED, HIGH);   // turn the LED on (HIGH is the voltage level)  
    //Udp.beginPacket(STAlocal_IP, 4209);
    //Udp.write(initialPacket);
    //Udp.endPacket();
    //delay(1000);
    //digitalWrite(LEDRED, LOW);    // turn the LED off by making the voltage LOW  
    //delay(1000);
    
    /* Forward received WiFi message via Serial to the EvalBoard */
    char helper = ~incomingPacket[0] << 1u;
    Serial.printf("[Serial] Write: 0x%02X\n", helper);
    swSer.write(helper);
  }

  // Check for incoming Serial packets
  while (swSer.available() > 0) {
    Serial.printf("[Serial] Received byte\n");
    serReadValue = swSer.read();
    Serial.printf("[WiFi] Send one byte to %s, port %d\n", STAlocal_IP.toString().c_str(), 4209);
    Udp.beginPacket(STAlocal_IP, 4209);
    Udp.write(serReadValue);
    Udp.endPacket();
  }
}

void blinkLedRed()
{
  int state = digitalRead(LEDRED);
  digitalWrite(LEDRED, !state);
}



