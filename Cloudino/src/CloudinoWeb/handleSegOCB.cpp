/*
  CloudinoWeb/handleSegOCB.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#ifdef OCB_CONNECTOR
void handleSegOCB()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>Orion Context Broker Configuration</h1>\n");
  ret += "</header>\n";

  if (webserver.hasArg("ocb_active")) {

    strcpy(configuration.ocb_dns, webserver.arg("ocb_dns").c_str());
    strcpy(configuration.ocb_auth, webserver.arg("ocb_auth").c_str());
    strcpy(configuration.ocb_user, webserver.arg("ocb_user").c_str());
    strcpy(configuration.ocb_pwd, webserver.arg("ocb_pwd").c_str());
    strcpy(configuration.ocb_devid, webserver.arg("ocb_devid").c_str());
    configuration.ocb_port = (int)webserver.arg("ocb_port").toInt();
    setConnectorActive("ocb", (bool)webserver.arg("ocb_active").toInt());

    EEPROM_write(0, configuration);

    fileWrite("/ocb_create.json", webserver.arg("ocb_create"));

    msg = "Changes Applied";
  }

  ret += "<section>\n";
  ret += F("<p>This is the Orion Context Broker Configuration page, to get these information you need to register in <a href=\"http://www.fiware.org/\">www.fiware.org</a></p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";
  ret += addtrrad(F("Active"),"ocb_active", configuration.ocb_active);
  ret += addtrinp(F("DNS"),"text","ocb_dns", configuration.ocb_dns, 0, 50);
  ret += addtrinp(F("Port"),"number","ocb_port", String(configuration.ocb_port), 0, 15);
  ret += addtrinp(F("Auth URL"),"text","ocb_auth", configuration.ocb_auth, 0, 50);
  ret += addtrinp(F("User"),"text","ocb_user", configuration.ocb_user, 0, 40);
  ret += addtrinp(F("Password"),"password","ocb_pwd", configuration.ocb_pwd, 0, 19);
  ret += addtrinp(F("Entity ID"),"text","ocb_devid", configuration.ocb_devid, 0, 40);
  ret += F("<tr><td>Entity Definition:</td><td><textarea id=\"ocb_create\" style=\"font-family: monospace; width: 100%; height:200px;\" autofocus>");

  ret += fileRead("/ocb_create.json");

  ret += F("</textarea></td></tr>");
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('srv_ocb'+cdino.getForm()+'&ocb_create='+encodeURIComponent(ocb_create.value));"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
#endif
