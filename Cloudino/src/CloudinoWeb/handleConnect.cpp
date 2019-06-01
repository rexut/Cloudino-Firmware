/*
  CloudinoWeb/handleConnect.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include <ESP8266WiFi.h>

#include "../CloudinoWeb.h"

void handleConnect()
{
  if (webserver.hasArg("ssid")) {

    String ssid = webserver.arg("ssid");

    if (webserver.hasArg("pwd")) {

      String pwd = webserver.arg("pwd");
      WiFi.begin(ssid.c_str(), pwd.c_str());

    } else {
      WiFi.begin(ssid.c_str());
    }
  }

  webserver.send(200, "text/html; charset=utf-8", "OK");
}
