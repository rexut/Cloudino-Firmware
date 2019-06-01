/*
  CloudinoWeb/toStringID.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String toStringID(unsigned long x)
{
  String id = String(x,16);
  id.toUpperCase();

  return id;
}
