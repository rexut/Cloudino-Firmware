/*
  CloudinoWeb/handleNotFound.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"

void handleNotFound()
{
  webserver.send(404, "text/html; charset=utf-8", String() + F("<html><head><title>Cloudino</title></head><body>URI: ") + webserver.uri() + F(" Not Found</body></html>"));
}
