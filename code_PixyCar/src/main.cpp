#include <Arduino.h>
#include <PixyMaps.h>
#include <MotorService.h>
#include <WiFiService.h>

int status = WL_IDLE_STATUS;
IPAddress server(IP_ADDRESS);
WiFiClient client;

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
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(SSID);

  status = WiFi.begin(SSID, PASSWORD);
  
  if(status != WL_CONNECTED){
    Serial.println("WiFi Connected!");
    Serial.println("Connecting to server...");
  
    while(!client.connect(server, 80)) {
      Serial.print("...");
    }
    Serial.println("\nConnected to server!");
    blink(250, 3);
  }
  else{
    Serial.println("Unable to connect");
    digitalWrite(LED_BUILTIN, HIGH);    
  }
}

void loop() {
  client.println("GET /currPos HTTP/1.0");
  delay(10);
  
  if(!client.connected()){
    Serial.print("Reconnecting to server...");
    while(!client.connect(server, 80)) {
      Serial.print("...");
    }
  }

  Serial.println("\nRespond:");
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}