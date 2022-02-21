#ifndef __WEB_SERVICE__
    #define __WEB_SERVICE__

    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <Secret.h>

    #define PORT 80

    void handleRoot();
    void sendCurrPos();

#endif