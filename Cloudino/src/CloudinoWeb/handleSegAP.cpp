/*
  CloudinoWeb/handleSegAP.cpp - WebInterface for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, softjei@gmail.com, July 8, 2015
  Released into the public domain.
*/

#include <Arduino.h>  // for type definitions

#include <ESP8266WiFi.h>

#include "../CloudinoWeb.h"

void handleSegAP()
{
  String msg;
  String ret;

  ret += "<header>\n";
  ret += F("<h1>Access Point Configuration</h1>\n");
  ret += F("<p>The Access Point configuration</p>\n");
  ret += "</header>\n";
  ret += "<section>\n";
  ret += "<form>\n";
  ret += "<table class=\"table\">\n";

  if (webserver.hasArg("m")) {
    String m = webserver.arg("m");

    ETS_UART_INTR_DISABLE();
    wifi_set_opmode((uint8)m.toInt());
    ETS_UART_INTR_ENABLE();

    msg = "Changes Applied";
  }

  if (webserver.hasArg("ssid")) {
    String ssid = webserver.arg("ssid");
    String pwd = webserver.arg("pwd");
    String channel = webserver.arg("channel");
    String hidden = webserver.arg("hidden");

    //WiFi.softAP(ssid.c_str(), pwd.c_str());
    WiFi.softAP(ssid.c_str(), pwd.c_str(), (int)channel.toInt(), (int)hidden.toInt()); //Next Version
    //WiFi.softAP(ssid.c_str(), pwd.c_str(), (int)channel.toInt());

    msg = "Changes Applied";
  }

  struct softap_config conf;
  wifi_softap_get_config(&conf);
  const char* authmode[] = {"AUTH_OPEN", "AUTH_WEP", "AUTH_WPA_PSK", "AUTH_WPA2_PSK", "AUTH_WPA_WPA2_PSK"};
  const char* modes[] = {"OFF", "OFF", "ON", "ON"};

  ret += addtr(F("Status"), modes[wifi_get_opmode()]);
  ret += addtrinp(F("SSID"), "text", "ssid", reinterpret_cast<char*>(conf.ssid));
  ret += addtrinp(F("Password"), "text", "pwd", reinterpret_cast<char*>(conf.password));
  ret += addtrinp(F("Channel"), "number", "channel", String(conf.channel));
  ret += addtrrad(F("SSID Hidden"), "hidden", conf.ssid_hidden);
  ret += addtr(F("Authmode"), authmode[conf.authmode]);
  ret += addtr(F("IP"), getAddress(WiFi.softAPIP()));
  ret += addtr(F("MAC"), WiFi.softAPmacAddress());
  ret += addtr(F("Mask"), "255.255.255.0");
  ret += addtr(F("Gateway"), getAddress(WiFi.softAPIP()));
  ret += "</table>\n";
  ret += addbutton(F("Save"), F("cdino.seg('ap'+cdino.getForm());"));
  ret += addbutton(F("Start AP"), F("cdino.seg('ap?m=3');"));
  ret += addbutton(F("Stop AP"), F("cdino.seg('ap?m=1');"));
  ret += "</form>\n";
  ret += alert(msg);
  ret += "</section>\n";

  webserver.send(200, "text/html; charset=utf-8", ret);
}
