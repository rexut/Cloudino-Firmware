/*
  EEPROMAnything/EEPROM_read.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef EEPROMAnything_EEPROM_read_h
#define EEPROMAnything_EEPROM_read_h

#include <EEPROM.h>

#include "../EEPROMAnything.h"

template <class T>
int EEPROM_read(int ee, T& value)
{
  EEPROM.begin(sizeof(value) + ee);
  byte* p = (byte*)(void*)&value;

  unsigned int i;
  for (i = 0; i < sizeof(value); i++) {
    *p++ = EEPROM.read(ee++);
  }

  EEPROM.end();

  return i;
}

#endif  // EEPROMAnything_EEPROM_read_h
