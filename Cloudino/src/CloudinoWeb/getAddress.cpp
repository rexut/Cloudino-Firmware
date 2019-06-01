/*
  CloudinoWeb/getAddress.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

String getAddress(IPAddress ip)
{
  return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
}
