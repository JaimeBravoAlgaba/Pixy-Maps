#include <VisionService.h>
#include <WebService.h>

extern ESP8266WebServer server;
extern Block car;
extern Block *traj;

void handleRoot(){
    server.send(200, "text/html", "<h1>Estas conectado a Pixy-Maps!</h1>");
}

void sendCurrPos(){
    String text = "{CurrenPosition:[" + String(car.x) + "," + String(car.y) + "]}";
    server.send(200, "text/plain", text);
}