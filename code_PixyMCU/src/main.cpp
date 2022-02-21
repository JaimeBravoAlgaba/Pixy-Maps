#include <Arduino.h>

#include <VisionService.h>
#include <WebService.h>

// Configuración de red:
const char* ssid = SSID;
const char* password = PASSWORD;
IPAddress local_IP(LOCAL_IP);
IPAddress gateway(GATEWAY);
IPAddress subnet(SUBNET);

// Servidor:
ESP8266WebServer server(PORT);

// Pixy:
Pixy pixy;

// Circuito
Block car;
Block traj[TRAJ_POINTS];

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

void setup()
{
  // Comunicación serial:
  Serial.begin(9600);

  // Inicialización de pines:
  pinMode(LED_BUILTIN, OUTPUT);

  // Iniciando Punto de Acceso:
  Serial.print("Configurando modo Soft-AP... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed");

  Serial.print("Iniciando modo Soft-AP... ");
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed");

  Serial.print("Dirección IP Soft-AP: ");
  Serial.println(WiFi.softAPIP());
  delay(500);
  blink(250, 3);

  // Iniciando Servidor:
  server.on("/", handleRoot);
  server.on("/currPos", sendCurrPos);
  server.begin();

  // Iniciando Pixy:
  pixy.init();
  //pixy.pixyBlink(RGB_GREEN, 250, 3);
}

void loop()
{ 
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32]; 
  
  blocks = pixy.getBlocks();
  
  // If there are detect blocks, print them!
  if (blocks)
  {
    i++;
    
    if (i%50==0)
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);

      int n = 0;
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();

        // Procesamiento del mapa:
        if(pixy.blocks[j].signature == SIG_TRAJ)
        {
          traj[n] = pixy.blocks[j];
          ++n;
        }
        else if(pixy.blocks[j].signature == SIG_CAR)
        {
          car = pixy.blocks[j];
        }
      }
    }
  }

  server.handleClient();
}