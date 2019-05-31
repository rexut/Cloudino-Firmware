/*
  EEPROMAnything/EEPROM_clean.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef EEPROMAnything_EEPROM_clean_h
#define EEPROMAnything_EEPROM_clean_h

#include <EEPROM.h>

#include "../EEPROMAnything.h"

template <class T>
int EEPROM_clean(int ee, const T& value)
{
  EEPROM.begin(sizeof(value) + ee);

  unsigned int i;
  for (i = 0; i < sizeof(value); i++) {
    EEPROM.write(ee++, 0);
  }

  EEPROM.commit();
  EEPROM.end();

  return i;
}

#endif  // EEPROMAnything_EEPROM_clean_h
