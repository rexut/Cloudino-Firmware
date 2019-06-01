/*
  CloudinoWeb/resetEEPROM.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include <FS.h>

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

void resetEEPROM()
{
  EEPROM_clean(0, configuration);
  EEPROM_read(0, configuration);
  strcpy(configuration.ini, "ini");

#ifdef CDINO_CONNECTOR
  strcpy(configuration.cdino_dns, "cloudino.cc");
  configuration.cdino_port = 9494;
#endif

#ifdef CDINO_ARDUINO
  configuration.arduino_active = false;
  configuration.arduino_gpio = 5;
#endif

#ifdef BLYNK_CONNECTOR
  strcpy(configuration.blynk_dns, "blynk-cloud.com");
  configuration.blynk_port = 8442;
#endif

#ifdef OCB_CONNECTOR
  strcpy(configuration.ocb_dns, "orion.lab.fiware.org");
  configuration.ocb_port = 1026;
  strcpy(configuration.ocb_auth, "https://orion.lab.fiware.org/token");
#endif

  EEPROM_write(0, configuration);
  SPIFFS.format();
}
