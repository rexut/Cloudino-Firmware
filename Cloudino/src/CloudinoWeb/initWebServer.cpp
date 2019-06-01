/*
  CloudinoWeb/initWebServer.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoWeb.h"

ESP8266WebServer webserver(80);
WiFiUDP udp;

#ifdef CAPTIVE_PORTAL
DNSServer dnsServer;
IPAddress apIP(192, 168, 4, 1);
#endif

void initWebServer()
{
#ifdef CAPTIVE_PORTAL
  dnsServer.start(53, "*", apIP);
#endif

  webserver.on("/", handleRoot);
  webserver.on("/seg/menu", handleMenu);
  webserver.on("/seg/status", secureHandler(handleSegStatus));
  webserver.on("/seg/ap", secureHandler(handleSegAP));
  webserver.on("/seg/wifi", secureHandler(handleSegWifi));
  webserver.on("/seg/mdns", secureHandler(handleSegMDNS));

#ifdef JS_SUPPORT
  webserver.on("/seg/jscript", secureHandler(handleSegJScript));
  webserver.on("/seg/jsterm", secureHandler(handleSegJSTerm));
#endif

#ifdef CDINO_CONNECTOR
  webserver.on("/seg/srv_cloudino", secureHandler(handleSegCloudino));
#endif

#ifdef OCB_CONNECTOR
  webserver.on("/seg/srv_ocb", secureHandler(handleSegOCB));
#endif

#ifdef MQTT_CONNECTOR
  webserver.on("/seg/srv_mqtt", secureHandler(handleSegMQTT));
#endif

#ifdef BLYNK_CONNECTOR
  webserver.on("/seg/srv_blynk", secureHandler(handleSegBlynk));
#endif

  webserver.on("/seg/sys", secureHandler(handleSegSys));
  webserver.on("/post", secureHandler(handlePost));
  webserver.on("/connect", secureHandler(handleConnect));

#ifdef JS_SUPPORT
  webserver.on("/jsinit", secureHandler(handleJSInit));
  webserver.on("/js", secureHandler(handleJS));
#endif

#ifdef CAPTIVE_PORTAL
  webserver.on("/fwlink/", handleRoot);
  webserver.on("/hotspot-detect.html", handleRoot);
#endif

  webserver.onNotFound (handleNotFound);
  // webserver.onNotFound (handleAny);
  // webserver.onNotFound (handleRoot);
  webserver.begin();

  udp.begin(UDP_PORT);
}
