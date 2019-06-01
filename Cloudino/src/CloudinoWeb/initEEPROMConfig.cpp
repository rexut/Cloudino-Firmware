/*
  CloudinoWeb/initEEPROMConfig.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

void initEEPROMConfig()
{
  pinMode(0, INPUT_PULLUP);              //RESET WIFI

  EEPROM_read(0, configuration);

  if( strcmp(configuration.ini, "ini") != 0) {

    resetEEPROM();
    resetWIFI();

  }
}
