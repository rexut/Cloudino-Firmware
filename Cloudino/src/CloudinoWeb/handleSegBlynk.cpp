/*
  CloudinoWeb/handleSegBlynk.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include "../../CloudConnector.h"
extern CloudConnector *connect;

#ifdef BLYNK_CONNECTOR
void handleSegBlynk()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>Blynk Configuration</h1>\n");
  ret += "</header>\n";

  if (webserver.hasArg("blynk_active")) {

    strcpy(configuration.blynk_dns, webserver.arg("blynk_dns").c_str());
    strcpy(configuration.blynk_auth, webserver.arg("blynk_auth").c_str());
    configuration.blynk_port = (int)webserver.arg("blynk_port").toInt();
    setConnectorActive("blynk", (bool)webserver.arg("blynk_active").toInt());

    EEPROM_write(0,configuration);

    msg = "Changes Applied";
  }

  ret += "<section>\n";
  ret += F("<p>This is the Blynk Configuration page, you can use any Blynk Server.</p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";

  bool st = false;
  if (connect && connect->getName() == "BLYNK" && connect->isConnected()) {
    st = true;
  }

  if (st) {
    ret += addtr(F("Status"), F("<span style=\"color:#5FB404\">Online</span>"));
  } else {
    ret += addtr("Status", "Offline");
  }

  ret += addtrrad(F("Active"), "blynk_active", configuration.blynk_active);
  ret += addtrinp(F("DNS"), "text", "blynk_dns", configuration.blynk_dns, 0, 50);
  ret += addtrinp(F("Port"), "number", "blynk_port", String(configuration.blynk_port), 0, 15);
  ret += addtrinp(F("Auth"), "text", "blynk_auth", configuration.blynk_auth, 0, 50);
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('srv_blynk'+cdino.getForm());"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
#endif
