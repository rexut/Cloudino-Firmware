/*
  CloudinoWeb/addtr.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String addtr(String prop, String value)
{
  return String() + F("<tr><td>") + prop + F(":</td><td>") + value + F("</td></tr>\n");
}
