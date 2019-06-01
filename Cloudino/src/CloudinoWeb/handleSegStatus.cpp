/*
  CloudinoWeb/handleSegStatus.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

void handleSegStatus()
{
  char temp[10];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  snprintf (temp, 10, "%02d:%02d:%02d", hr, min % 60, sec % 60);

  const char* modes[] = {"NULL", "STA", "AP", "STA+AP"};

  String ret;
    
  ret += "<header>\n";
  ret += F("<h1>Cloudino Status</h1>\n");
  ret += F("<p>The status of the Cloudino Router</p>\n");
  ret += "</header>\n";
  ret += "<section>\n";
  ret += "<table class=\"table\">\n";

  ret += addtr(F("Cloudino Version"), CDINO_VERSION);
  ret += addtr(F("Uptime"), temp);
  ret += addtr(F("Mode"), modes[wifi_get_opmode()]);
  ret += addtr(F("Free Heap"), String(ESP.getFreeHeap()));
  ret += addtr(F("ChipId"), toStringID(ESP.getChipId()));
  ret += addtr(F("Flash ChipId"), toStringID(ESP.getFlashChipId()));
  ret += addtr(F("Flash ChipSize"), String(ESP.getFlashChipSize()));
  ret += addtr(F("Flash Real Size"), String(ESP.getFlashChipRealSize()));
  ret += addtr(F("Flash Chip Speed"), String(ESP.getFlashChipSpeed()));

  FlashMode_t ideMode = ESP.getFlashChipMode();
  ret += addtr(F("Flash ide mode"), (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));

  //addtr("Vcc", String(ESP.getVcc()));

  ret += "</table>\n";
  ret += addbutton(F("Reload"), F("cdino.seg('status');"));
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
