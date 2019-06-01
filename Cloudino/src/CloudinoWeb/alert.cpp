/*
  CloudinoWeb/alert.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String alert(String msg)
{
  if (msg.length() > 0)
    return String() + F("<div class=\"alert\">") + msg + F("</div>");

  else return String("");
}
