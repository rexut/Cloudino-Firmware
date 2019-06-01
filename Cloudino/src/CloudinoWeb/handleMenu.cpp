/*
  CloudinoWeb/handleMenu.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

void handleMenu()
{
  String ret;

  ret += F("<h2>Configuration</h2>\n");
  ret += F("<ul class=\"sidebar-nav\">\n");
  ret += F("<li><a href=\"javascript:cdino.seg('status');\">Cloudino Status</a></li>\n");
  ret += F("<li><a href=\"javascript:cdino.seg('ap');\">Access Point Configuration</a></li>\n");
  ret += F("<li><a href=\"javascript:cdino.seg('wifi');\">Wifi Configuration</a></li>\n");
  ret += F("<li><a href=\"javascript:cdino.seg('mdns');\">mDNS Service Discovery</a></li>\n");

#ifdef JS_SUPPORT
  ret += F("<li><a href=\"#\" onclick=\"jscript.style.display=((jscript.style.display=='none')?'':'none');\">JavaScript Configuration</a></li>\n");
  ret += F("<ul id=\"jscript\" style=\"display:none\">\n");
  ret += F("<li><a href=\"javascript:cdino.seg('jscript');\">Initial Script</a></li>\n");
  ret += F("<li><a href=\"javascript:cdino.seg('jsterm');\">JavaScript Terminal</a></li>\n");
  ret += F("</ul>\n");
#endif

  ret += F("<li><a href=\"#\" onclick=\"server.style.display=((server.style.display=='none')?'':'none');\">Server Configuration</a></li>\n");
  ret += F("<ul id=\"server\" style=\"display:none\">\n");

#ifdef CDINO_CONNECTOR
  ret += F("<li><a href=\"javascript:cdino.seg('srv_cloudino');\">Cloudino Server</a></li>\n");
#endif

#ifdef OCB_CONNECTOR
  ret += F("<li><a href=\"javascript:cdino.seg('srv_ocb');\">Orion Context Broker</a></li>\n");
#endif

#ifdef MQTT_CONNECTOR
  ret += F("<li><a href=\"javascript:cdino.seg('srv_mqtt');\">MQTT Server</a></li>\n");
#endif

#ifdef COAP_CONNECTOR
  ret += F("<li><a href=\"javascript:cdino.seg('srv_coap');\">COAP Server</a></li>\n");
#endif

#ifdef BLYNK_CONNECTOR
  ret += F("<li><a href=\"javascript:cdino.seg('srv_blynk');\">Blynk Server</a></li>\n");
#endif

  ret += F("</ul>\n");
  ret += F("<li><a href=\"javascript:cdino.seg('sys');\">System Tools</a></li>\n");
  ret += F("</ul>\n");

  webserver.send(200, "text/html; charset=utf-8", ret);
}
