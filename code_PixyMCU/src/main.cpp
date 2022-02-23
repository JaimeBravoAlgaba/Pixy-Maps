#include <ESP8266WiFi.h>
#include <Secret.h>
#include <WiFiUdp.h>
#include <VisionService.h>

// Variables de gestión de red:
WiFiUDP Udp;
char incomingPacket[255];  // buffer for incoming packets
char  replyPacket[] = "Hi there! Got the message :-)";  // a reply string to send back

// Variables de gestión de cámara Pixy:
Pixy pixy;

void setup()
{
  // Inicialización de comunicación Serial:
  Serial.begin(9600);

  // Incialización de Punto de Acceso:
  Serial.print("Configurando modo Soft-AP... ");
  Serial.println(WiFi.softAPConfig(LOCAL_IP, GATEWAY, SUBNET) ? "Listo" : "Falló!");

  Serial.print("Estableciendo modo Soft-AP... ");
  Serial.println(WiFi.softAP(SSID, PASSWORD) ? "Listo" : "Falló!");

  Serial.print("Dirección IP Soft-AP = ");
  Serial.println(WiFi.softAPIP());

  // Inicialización de comunicación UDP:
  Udp.begin(LOCAL_UDP_PORT);
  Serial.print("Puerto UDP = ");
  Serial.println(Udp.localPort());

  // Inicialización de la cámara Pixy:
  pixy.init();
  Serial.println("Cámara Pixy iniciada");
  Serial.println("____________________________________________________________");
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];
  String payload;
  
  // Lectura del mapa:
  blocks = pixy.getBlocks();
  point traj[blocks-1];
  point car;
  
  // Si hay bloques, se procesa la información:
  if (blocks)
  {
    i++;

    if (i%50==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);

      int k = 0;
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();

        uint16_t sig = pixy.blocks[j].signature;

        // Si es un punto de trayectoria:
        if(sig == SIG_TRAJ)
        {
          traj[k].x = pixy.blocks[j].x;
          traj[k].y = pixy.blocks[j].y;
          k++;
        }
        // Si es la posición del coche:
        else if(sig == SIG_CAR)
        {
          car.x = pixy.blocks[j].x;
          car.y = pixy.blocks[j].y;
        }
      }
    }
  }  
  
  // Envío de datos:
  Udp.beginPacket(IPAddress(LOCAL_IP), LOCAL_UDP_PORT);
  payload = "{CurrentPos:[" + String(car.x) + "," + String(car.y) + "];Trajectory:[";
  for(int i=0; i<blocks-2; i++)
  {
    payload = payload + "[" + String(traj[i].x) + "," + String(traj[i].y) + "],";
  }
  payload = payload + "[" + String(traj[i].x) + "," + String(traj[i].y) + "]]}";

  Udp.write(payload.c_str());
  Udp.endPacket();
  delay(50);
}