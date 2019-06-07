/*
  TinyJS_HTTPBinding.cpp - TinyJS Library add-on for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include "../CloudinoConf.h"

#include "TinyJS_HTTPBinding.h"

#include <Arduino.h>  // for type definitions
#include <ESP8266HTTPClient.h>

#ifdef HTTPS_SUPPORT
void scHTTPSSend(CScriptVar *c, void *) {
  String host = c->getParameter("host")->getString();
  int port = c->getParameter("port")->getInt();
  String content = c->getParameter("content")->getString();

  WiFiClientSecure client;
  if(client.connect(host.c_str(), port))
  {
    client.print(content);

    int timeout = 5 * 10; // 5 seconds
    while (!client.available() && (timeout-- > 0)) {
      delay(100);
    }

    String result;
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      result += client.readStringUntil('\n');
    }
    c->getReturnVar()->setString(result);
  }
}
#endif

void scHTTPSend(CScriptVar *c, void *) {
  String host = c->getParameter("host")->getString();
  int port = c->getParameter("port")->getInt();
  String content = c->getParameter("content")->getString();

  WiFiClient client;
  if(client.connect(host.c_str(), port))
  {
    client.print(content);

    int timeout = 5 * 10; // 5 seconds
    while (!client.available() && (timeout-- > 0)) {
      delay(100);
    }

    String result;
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      result += client.readStringUntil('\n');
    }
    c->getReturnVar()->setString(result);
  }
}

void scHTTPGet(CScriptVar *c, void *)
{
    String url = c->getParameter("url")->getString();

    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();

    if(httpCode > 0)
    {
        if(httpCode == HTTP_CODE_OK) {
            c->getReturnVar()->setString(http.getString());
        }
    }
    http.end();
}

// ----------------------------------------------- Register Functions
void registerHTTPBinding(CTinyJS *tinyJS) {
#ifdef HTTPS_SUPPORT
    tinyJS->addNative(F("function HTTP.sendSSL(host,port,content)"), scHTTPSSend, tinyJS); // Send https content
#endif
    tinyJS->addNative(F("function HTTP.send(host,port,content)"), scHTTPSend, tinyJS); // Send http content
    tinyJS->addNative(F("function HTTP.get(url)"), scHTTPGet, tinyJS); // Get http content
}
