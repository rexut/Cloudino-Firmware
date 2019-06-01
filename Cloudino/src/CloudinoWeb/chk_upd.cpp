/*
  CloudinoWeb/chk_upd.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

#include <ESP8266HTTPClient.h>

#ifdef HTTP_UPDATE
String chk_upd()
{
  String version;
  HTTPClient http;

  http.begin(CDINO_VERSIONURL);

  int httpCode = http.GET();
  if (httpCode > 0) {

    if(httpCode == HTTP_CODE_OK) {

      version = http.getString();

    } else {
      return String() + F("Error: Bad response code:") + String(httpCode);
    }
  }

  http.end();

  if (version == CDINO_VERSION) {
    return F("There isn't new version of Cloudino Firmware");
  } else {
    return String() + F("New version (") + version + F(") of Cloudino Firmware is available");
  }
}
#endif
