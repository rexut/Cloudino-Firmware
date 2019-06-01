/*
  CloudinoWeb/addbutton.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String addbutton(String value, String onclick)
{
  return String() + F("<input onclick=\"") + onclick + F("\" type=\"button\" value=\"") + value + F("\">\n");
}
