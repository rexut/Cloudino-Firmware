/*
  CloudinoWeb/addtrinp.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String addtrinp(String prop, String type, String name, String value, int min, int max)
{
  return addtr(prop, String() + F("<input type=\"") + type + F("\" name=\"") + name + F("\" minlength=\"") + min + F("\" maxlength=\"") + max + F("\" value=\"") + value + F("\">"));
}
