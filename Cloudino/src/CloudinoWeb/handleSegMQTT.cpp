/*
  CloudinoWeb/handleSegMQTT.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include "../../CloudConnector.h"
extern CloudConnector *connect;

#ifdef MQTT_CONNECTOR
void handleSegMQTT()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>MQTT Broker Configuration</h1>\n");
  ret += "</header>\n";

  if (webserver.hasArg("mqtt_active")) {

    strcpy(configuration.mqtt_dns, webserver.arg("mqtt_dns").c_str());
    strcpy(configuration.mqtt_user, webserver.arg("mqtt_user").c_str());
    strcpy(configuration.mqtt_passwd, webserver.arg("mqtt_passwd").c_str());
    strcpy(configuration.mqtt_pub_path, webserver.arg("mqtt_pub_path").c_str());
    strcpy(configuration.mqtt_sub_path, webserver.arg("mqtt_sub_path").c_str());
    configuration.mqtt_port = (int)webserver.arg("mqtt_port").toInt();
    setConnectorActive("mqtt", (bool)webserver.arg("mqtt_active").toInt());

    EEPROM_write(0,configuration);

    msg = "Changes Applied";
  }

  ret += "<section>\n";
  ret += F("<p>This is the MQTT Broker Configuration page, you can use any MQTT Server.</p>\n");
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";

  bool st = false;
  if (connect && connect->getName() == "MQTT" && connect->isConnected()) {
    st = true;
  }

  if (st) {
    ret += addtr(F("Status"), F("<span style=\"color:#5FB404\">Online</span>"));
  } else {
    ret += addtr(F("Status"), F("Offline"));
  }

  ret += addtrrad(F("Active"), "mqtt_active", configuration.mqtt_active);
  ret += addtrinp(F("DNS"), "text", "mqtt_dns", configuration.mqtt_dns, 0, 50);
  ret += addtrinp(F("Port"), "number", "mqtt_port", String(configuration.mqtt_port), 0, 15);
  ret += addtrinp(F("User"), "text", "mqtt_user", configuration.mqtt_user, 0, 20);
  ret += addtrinp(F("Password"), "text", "mqtt_passwd", configuration.mqtt_passwd, 0, 20);
  ret += addtrinp(F("Publish base path"), "text", "mqtt_pub_path", configuration.mqtt_pub_path, 0, 100);
  ret += addtrinp(F("Subscribe path"), "text", "mqtt_sub_path", configuration.mqtt_sub_path, 0, 100);

  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('srv_mqtt'+cdino.getForm());"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
#endif
