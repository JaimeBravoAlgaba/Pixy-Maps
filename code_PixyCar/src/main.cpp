#include <Arduino.h>
#include <PixyMaps.h>
#include <MotorService.h>
#include <WebService.h>

WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "OK";  // a reply string to send back

/**
 * @brief Parpadea el LED de la placa NodeMCU.
 * 
 * @param period En milisegundos.
 * @param iters Número de parpadeos.
 */
void blink(int period, int iters){
  for(int i=0; i<iters; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(period/2);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(period/2);
  }
}

void setup() {
  Serial.begin(9600);

  // Motors setup:
  setupMotors();

  // WiFi setup:
  Serial.println("Connecting to " + String(SSID) + "...");
  WiFi.config(IPAddress(LOCAL_IP), IPAddress(GATEWAY), IPAddress(SUBNET));
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    blink(10, 1);
  }
  Serial.println(" Connected!");
  blink(150, 2);

  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  String payload;
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    payload = String(incomingPacket);
    Serial.println("Payload: " + payload);

    // send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
  }
}