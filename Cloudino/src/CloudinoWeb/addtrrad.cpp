/*
  CloudinoWeb/addtrrad.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String addtrrad(String prop, String name, bool value)
{
  String t;
  String f = "checked";

  if (value) {
    f = "";
    t = "checked";      
  }

  return addtr(prop, String() + F("<input type=\"radio\" name=\"") + name + F("\" value=\"0\" ") + f + F("> False <input type=\"radio\" name=\"") + name + F("\" value=\"1\" ") + t + F("> True"));
}
