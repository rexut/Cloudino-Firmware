/*
  CloudinoWeb/loopWebServer.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include "../../TinyJS.h"
extern CTinyJS *js;

#include "../../SMessageProc.h"
extern SMessageProc proc;

MDNSResponder mdns;

bool wifiConnected = false;
bool resetConnector = false;
static bool jsInited = false;

static unsigned long _time = millis();
static unsigned long _time2 = _time;
static byte _timeCounter = 0;

void loopWebServer()
{
#ifdef CAPTIVE_PORTAL
  dnsServer.processNextRequest();
#endif

  webserver.handleClient();

  // wait for connection
  unsigned long m = millis();

  if (m - _time >= 5000) {

    _time = m;

    //Reset Wifi after 5 seconds pressing GPIO0
    if (!digitalRead(0)) {
        resetWIFI();
    }

    if (WiFi.status() != WL_CONNECTED) {
      // Serial.println("Wifi Disconnected...");
      wifiConnected = false;
    }

  }

  if (m - _time2 >= 1000) {

    _time2 = m;

    // don't init JS Init Script if pressing GPIO0
    if (jsInited == false && !digitalRead(0)) {
        jsInited = true;
    }

#ifdef JS_SUPPORT
    if (!jsInited && (wifiConnected || _timeCounter == 10)) {

        // Serial.println("JavaScript Code Initialized...");
        jsInited = true;

        String code = fileRead(ARDUINO_SCRIPT_PATH);
        js->execute(code);
    }
#endif

    if (_timeCounter < 10) {
      _timeCounter++;
    }

    if (!wifiConnected) {

      if (WiFi.status() == WL_CONNECTED) {

        wifiConnected = true;
        resetConnector = true;

        if (strlen(configuration.mdns_dns) > 0) {

          mdns.begin(configuration.mdns_dns);
          mdns.enableArduino(9494, false);

          // mdns.addService("http", "tcp", 80);
          // mdns.addService("_arduino._tcp.local.", "tcp", 9494);
          // mdns.addService("arduino", "tcp", 9494);
          // mdns.addService("_arduino", "_tcp", 9494);
          // mdns.addService("avrisp", "tcp", 9494);

        }
      }
    }
  }

  if (jsInited) {
    if (udp.parsePacket()) {
      proc.handleLocalMessages(udp);
    }
  }
}
