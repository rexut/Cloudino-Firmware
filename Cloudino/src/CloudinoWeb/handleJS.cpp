/*
  CloudinoWeb/handleJS.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#include "../../TinyJS.h"
extern CTinyJS *js;

#ifdef JS_SUPPORT
void handleJS()
{
  String script = webserver.arg("plain");  //webserver._plain;

  if (script.length() > 0 && script.charAt(0) == '[') {
    script = script.substring(1);
  }

  String ret = js->evaluate(script);

  webserver.send(200, "text/html; charset=utf-8", ret);
}
#endif