/*
  CloudinoWeb.h - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef CloudinoWeb_h
#define CloudinoWeb_h

#include "CloudinoConf.h"

extern "C" {
//#include "c_types.h"
//#include "ets_sys.h"
//#include "os_type.h"
//#include "osapi.h"
//#include "mem.h"
#include "user_interface.h"
//#include "upgrade.h"
//#include "espconn.h"
//#include "smartconfig.h"
//#include "lwip/opt.h"
//#include "lwip/err.h"
//#include "lwip/dns.h"
//#include "ssl/ssl_crypto.h"
}

#include <ESP8266WebServer.h>
extern ESP8266WebServer webserver;

#include <ESP8266mDNS.h>
extern MDNSResponder mdns;

#ifdef CAPTIVE_PORTAL
#include <DNSServer.h>
extern DNSServer dnsServer;
#endif

#ifdef HTTP_UPDATE
#include <WiFiUdp.h>
extern WiFiUDP udp; // WiFiUDP udp;
#endif

extern bool wifiConnected;
extern bool resetConnector;

void initWebServer();
void loopWebServer();

void initEEPROMConfig();
void resetEEPROM();
void resetWIFI();
void setConnectorActive(String con, bool value);

#ifdef HTTP_UPDATE
String chk_upd();
String update(String url);
#endif

String toStringID(unsigned long x);
String getAddress(IPAddress ip);

String alert(String msg);
String addtr(String prop, String value);
String addtrrad(String prop, String name, bool value);
String addtrinp(String prop, String type, String name, String value, int min=0, int max=50);
String addbutton(String value, String onclick);

std::function<void(void)> secureHandler(std::function<void(void)> handleFunc);

void handleRoot();
void handleMenu();
void handleSegStatus();
void handleSegAP();
void handleSegWifi();
void handleSegMDNS();

#ifdef JS_SUPPORT
void handleSegJScript();
void handleSegJSTerm();
#endif

#ifdef CDINO_CONNECTOR
void handleSegCloudino();
#endif

#ifdef OCB_CONNECTOR
void handleSegOCB();
#endif

#ifdef MQTT_CONNECTOR
void handleSegMQTT();
#endif

#ifdef BLYNK_CONNECTOR
void handleSegBlynk();
#endif

void handleSegSys();
void handlePost();
void handleConnect();

#ifdef JS_SUPPORT
void handleJSInit();
void handleJS();
#endif

void handleNotFound();

#endif  // CloudinoWeb_h
