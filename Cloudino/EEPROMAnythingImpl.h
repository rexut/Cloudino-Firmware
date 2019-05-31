/*
  EEPROMAnythingImpl.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef EEPROMAnythingImpl_h
#define EEPROMAnythingImpl_h

#include <EEPROM.h>

#include "EEPROMAnything.h"

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

#endif  // EEPROMAnything_h