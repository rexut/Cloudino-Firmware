/*
  CloudinoWeb/handleSegJScript.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../EEPROMAnything.h"
#include "../CloudinoWeb.h"

#ifdef JS_SUPPORT
void handleSegJScript()
{
  String ret;  

  ret += "<header>\n";
  ret += F("<h1>Initial Script</h1>\n");
  ret += F("<p>With this option, you can define a JavaScript code to be excecuted on startup</p>\n");
  ret += "</header>\n";
  ret += "<section>\n";
  ret += F("<textarea id=\"js_script\" style=\"font-family: monospace; width: 100%; height:250px;\" autofocus>");
  ret += fileRead(ARDUINO_SCRIPT_PATH);
  ret += "</textarea>\n";
  ret += F("<span><input type=\"button\" onclick=\"cdino.getHtml('jsinit',null,'POST','['+ encodeURIComponent(js_script.value));\" value=\"Save\"></span>\n");
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
#endif
