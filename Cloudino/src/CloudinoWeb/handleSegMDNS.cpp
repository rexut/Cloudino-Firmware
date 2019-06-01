/*
  CloudinoWeb/handleSegMDNS.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

void handleSegMDNS()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>Multicast DNS Service Discovery</h1>\n");
  ret += F("<p>With this option, you can configure Multicast DNS Service Discovery inside your Wifi network that respond to [mDNS].local</p>\n");
  ret += "</header>\n";

  if (configuration.mdns_ttl == 0) {
    configuration.mdns_ttl = 3600;
  }

  if (webserver.hasArg("s")) {
    wifiConnected = false;
  }

  if (webserver.hasArg(F("mdns_dns"))) {

    strcpy(configuration.mdns_dns, webserver.arg(F("mdns_dns")).c_str());
    configuration.mdns_ttl = (int)webserver.arg(F("mdns_ttl")).toInt();

    EEPROM_write(0, configuration);
    wifiConnected = false;

    msg = "Changes Applied";
  }
    
  ret += "<section>\n";
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";    
  ret += addtrinp(F("mDNS"), "text", F("mdns_dns"), configuration.mdns_dns, 0, 15);
  ret += addtrinp(F("TTL"), "number", F("mdns_ttl"), String(configuration.mdns_ttl));
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('mdns'+cdino.getForm());"));
  ret += addbutton(F("Start"), F("cdino.seg('mdns'?s=1);"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  ret += F("<section>\n\
<p>Install host software:<br>\n\
- For Linux, install Avahi (http://avahi.org/).<br>\n\
- For Windows, install Bonjour (http://www.apple.com/support/bonjour/).<br>\n\
- For Mac OSX and iOS support is built in through Bonjour already.\n\
</p></section>");

  webserver.send(200, "text/html; charset=utf-8", ret);
}
