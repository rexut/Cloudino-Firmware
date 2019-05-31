/*
  EEPROMAnything/EEPROM_write.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef EEPROMAnything_EEPROM_write_h
#define EEPROMAnything_EEPROM_write_h

#include <EEPROM.h>

#include "../EEPROMAnything.h"

template <class T>
int EEPROM_write(int ee, const T& value, int ext)
{
  EEPROM.begin(sizeof(value) + ee + ext);
  const byte* p = (const byte*)(const void*)&value;

  // Serial.print("ee:" + String(ee) + " " + String(sizeof(value)));

  unsigned int i;
  for (i = 0; i < sizeof(value); i++) {
    EEPROM.write(ee++, *p++);
  }

  EEPROM.commit();
  EEPROM.end();

  return i;
}

#endif  // EEPROMAnything_EEPROM_write_h
