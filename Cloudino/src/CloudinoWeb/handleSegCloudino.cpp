/*
  CloudinoWeb/handleSegCloudino.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include "../../CloudConnector.h"
extern CloudConnector *connect;

#ifdef CDINO_CONNECTOR
void handleSegCloudino()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>Cloudino Cloud Configuration</h1>\n");
  ret += "</header>\n";

  if (webserver.hasArg("cdino_active")) {

    strcpy(configuration.cdino_dns, webserver.arg("cdino_dns").c_str());
    strcpy(configuration.cdino_authtoken, webserver.arg("cdino_authtoken").c_str());
    configuration.cdino_port = (int)webserver.arg("cdino_port").toInt();
    setConnectorActive("cdino", (bool)webserver.arg("cdino_active").toInt());

    EEPROM_write(0, configuration);

    msg = "Changes Applied";
  }

  ret += "<section>\n";
  ret += F("<p>This is the Cloudino Cloud Configuration page, to get these information you need to register in <a href=\"http://cloudino.cc\">cloudino.cc</a></p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";

  bool st = false;
  if (connect && connect->getName() == "CDINO" && connect->isConnected()) {
    st = true;
  }

  if (st) {
    ret += addtr(F("Status"), F("<span style=\"color:#5FB404\">Online</span>"));
  } else {
    ret += addtr("Status", "Offline");
  }

  ret += addtrrad(F("Active"), "cdino_active", configuration.cdino_active);
  ret += addtrinp(F("DNS"), "text", "cdino_dns", configuration.cdino_dns, 0, 50);
  ret += addtrinp(F("Port"), "number", "cdino_port", String(configuration.cdino_port), 0, 50);
  ret += addtrinp(F("Auth Token"), "text", "cdino_authtoken", configuration.cdino_authtoken, 0, 50);
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('srv_cloudino'+cdino.getForm());"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  webserver.send( 200, "text/html; charset=utf-8", ret);
}
#endif
