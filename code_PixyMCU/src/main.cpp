#include <ESP8266WiFi.h>
#include <Secret.h>
#include <WiFiUdp.h>

const char* ssid = SSID;
const char* password = PASSWORD;

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back


void setup()
{
  Serial.begin(9600);
  Serial.println();

  Serial.print("Configurando modo Soft-AP... ");
  Serial.println(WiFi.softAPConfig(IPAddress(LOCAL_IP), IPAddress(GATEWAY), IPAddress(SUBNET)) ? "Listo" : "Falló!");

  Serial.print("Estableciendo modo Soft-AP... ");
  Serial.println(WiFi.softAP(SSID, PASSWORD) ? "Listo" : "Falló!");

  Serial.print("Dirección IP Soft-AP = ");
  Serial.println(WiFi.softAPIP());

  Udp.begin(localUdpPort);
}


void loop()
{
    Udp.beginPacket(IPAddress(LOCAL_IP), localUdpPort);
    Udp.write("Hola majo");
    Udp.endPacket();
    delay(50);
}