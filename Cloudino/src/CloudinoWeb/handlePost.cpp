/*
  CloudinoWeb/handlePost.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include "../CloudinoWeb.h"
#include "../SMessageProc.h"

void handlePost()
{
  String ret;

  if (webserver.hasArg("topic")) {

    String topic = webserver.arg("topic");
    String msg = "";

    if (webserver.hasArg("msg")) {
      msg = webserver.arg("msg");
    }

    proc.post(topic, msg);
    ret = "{\"topic\":\"" + topic + "\",\"msg\":\"" + msg + "\"}";
  }

  webserver.send(200, "text/html; charset=utf-8", ret);
}
