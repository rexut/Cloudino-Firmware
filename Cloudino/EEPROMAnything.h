/*
  EEPROMAnything.h - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#ifndef EEPROMAnything_h
#define EEPROMAnything_h

#include <Arduino.h>  // for type definitions

template <class T> int EEPROM_clean(int ee, const T& value);
template <class T> int EEPROM_write(int ee, const T& value, int ext = 0);
template <class T> int EEPROM_read(int ee, T& value);

String fileWrite(String name, String content);
String fileRead(String name);

#include "EEPROMAnythingImpl.h"

#endif  // EEPROMAnything_h