/*
  EEPROMAnything/fileWrite.cpp - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <FS.h>

#include "../EEPROMAnything.h"

String fileWrite(String name, String content)
{
  File file = SPIFFS.open(name, "w");

  if (file) {

    file.print(content);
    file.close();

  }

  return fileRead(name);
}
