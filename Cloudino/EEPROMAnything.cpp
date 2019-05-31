/*
  EEPROMAnything.cpp - EEPROM Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <FS.h>

#include "EEPROMAnything.h"

String fileWrite(String name, String content)
{
  File file = SPIFFS.open(name, "w");

  if (file) {

    file.print(content);
    file.close();

  }
}

String fileRead(String name)
{
  // read file from SPIFFS and store it as a String variable
  File file = SPIFFS.open(name.c_str(), "r");

  if (file) {

    int fileSize = file.size();
    char buf[fileSize + 1];

    file.read((uint8_t *)buf, fileSize);
    file.close();

    buf[fileSize] = 0;

    return String(buf);

  } else {
    return String("");
  }
}