/*
  CloudinoWeb/setConnectorActive.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include <FS.h>

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

void setConnectorActive(String con, bool value)
{
#ifdef CDINO_CONNECTOR
  configuration.cdino_active = false;
#endif

#ifdef OCB_CONNECTOR
  configuration.ocb_active = false;
#endif

#ifdef MQTT_CONNECTOR
  configuration.mqtt_active = false;
#endif

#ifdef BLYNK_CONNECTOR
  configuration.blynk_active = false;
#endif

  if (false) {

#ifdef CDINO_CONNECTOR
  } else if (con == "cdino") {
    configuration.cdino_active = value;
#endif

#ifdef OCB_CONNECTOR
  } else if (con == "ocb") {
    configuration.ocb_active = value;
#endif

#ifdef MQTT_CONNECTOR
  } else if (con == "mqtt") {
    configuration.mqtt_active = value;
#endif

#ifdef BLYNK_CONNECTOR
  } else if (con == "blynk") {
    configuration.blynk_active = value;
#endif

  }

  resetConnector = true;
}
