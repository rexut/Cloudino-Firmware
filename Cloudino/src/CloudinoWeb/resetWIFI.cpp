/*
  CloudinoWeb/resetWIFI.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include <ESP8266WiFi.h>

void resetWIFI()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);

  String ssid = toStringID(ESP.getChipId());
  ssid = String() + F("Cloudino_") + ssid;

  WiFi.softAP(ssid.c_str());
  WiFi.disconnect();

  configuration.auth_user[0] = 0;
  configuration.auth_passwd[0] = 0;

  EEPROM_write(0,configuration);
}
